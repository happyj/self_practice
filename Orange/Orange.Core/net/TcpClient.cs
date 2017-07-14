using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using log4net;
using System;

namespace Orange.Core.net
{
    class CTcpClient
    {
        ILog _log;

        TcpClient _cli;
        eTcpClientState _state;
        CTcpClientCloseArgs _closeTag;

        byte[] _pkgLen;

        SocketAsyncEventArgs _sendArgs;

        bool _recving;
        byte[] _recv;
        CBuffer _recvBuf;
        SocketAsyncEventArgs _recvArgs;
        Queue<ArraySegment<byte>> _recvsBefore;
        Queue<ArraySegment<byte>> _recvs;
        Queue<ArraySegment<byte>> _recvsAfter;

        eTcpClientState State
        {
            get
            {
                return _state;
            }
        }

        public CTcpClient(ILog log)
        {
            Init(log);
        }

        void Init(ILog log)
        {
            _log = log;

            _cli = null;
            _state = eTcpClientState.DisConnected;
            _closeTag = new CTcpClientCloseArgs()
            {
                Reason = eTcpClientCloseReason.None,
                Error = eTcpError.Success,
                SockError = SocketError.Success,
            };

            _pkgLen = new byte[4];

            _sendArgs = new SocketAsyncEventArgs();

            _recving = false;
            _recvBuf = new CBuffer(1024);
            _recv = new byte[1024];
            _recvArgs = new SocketAsyncEventArgs();
            _recvArgs.SetBuffer(_recv, 0, _recv.Length);
            _recvArgs.Completed += (sender, e) =>
            {
                EndRecv(_recvArgs);
            };
        }

        #region

        void Connect()
        {

        }

        public eTcpError Connect(TcpClient cli)
        {
            if (cli == null)
                return eTcpError.ArgumentNullRange;

            switch (_state)
            {
            case eTcpClientState.DisConnected:
                _cli = cli;
                _state = eTcpClientState.Connecting;
                Connect();
                _state = eTcpClientState.Connected;

                var e = new CTcpClientConnectArgs()
                {
                    Result = eTcpClientConnectResult.Success,
                    Error = eTcpError.Success,
                    SockError = SocketError.Success,
                };

                try
                {
                    OnConnected(e);
                }
                catch (Exception exception)
                {
                    _log.Error(string.Format("[TcpClient] OnConnected exception, addr: \"{0},{1}\", connectArgs: \"{1}, {2}, {3}\"", cli.Client.LocalEndPoint, cli.Client.RemoteEndPoint, e.Result, e.Error, e.SockError), exception);
                }

                _recving = true;
                BeginRecv();
                break;
            case eTcpClientState.DisConnecting:
            case eTcpClientState.Connecting:
            case eTcpClientState.Connected:
            default:
                return eTcpError.WrongState;
            }

            return eTcpError.Success;
        }

        public event EventHandler<CDataEventArgs<CTcpClientConnectArgs>> Connected;
        void RaiseConnected(CDataEventArgs<CTcpClientConnectArgs> e)
        {
            if (Connected != null)
            {
                Connected(this, e);
            }
        }
        void OnConnected(CTcpClientConnectArgs args)
        {
            RaiseConnected(CDataEventArgs.Create(args));
        }

        public event EventHandler<CDataEventArgs<CTcpClientCloseArgs>> Closed;
        void RaiseClosed(CDataEventArgs<CTcpClientCloseArgs> e)
        {
            if (Closed != null)
            {
                Closed(this, e);
            }
        }
        void OnClosed(CTcpClientCloseArgs args)
        {
            RaiseClosed(CDataEventArgs.Create(args));
        }

        #endregion

        #region

        void BeginRecv()
        {
            var safe = false;

            try
            {
                if (_cli.Client.ReceiveAsync(_recvArgs))
                    return;
                safe = true;
            }
            catch (SocketException exception)
            {
                lock (_closeTag)
                {
                    if (_closeTag.Reason == eTcpClientCloseReason.None)
                    {
                        _closeTag.Reason = eTcpClientCloseReason.Exception;
                        _closeTag.Error = eTcpError.SocketError;
                        _closeTag.SockError = exception.SocketErrorCode;
                    }
                }
            }
            catch
            {
                lock (_closeTag)
                {
                    if (_closeTag.Reason == eTcpClientCloseReason.None)
                    {
                        _closeTag.Reason = eTcpClientCloseReason.Exception;
                        _closeTag.Error = eTcpError.Exception;
                        _closeTag.SockError = SocketError.Success;
                    }
                }
            }

            if (safe)
            {
                EndRecv(_recvArgs);
            }
            else
            {
                _recving = false;
            }
        }

        void EndRecv(SocketAsyncEventArgs e)
        {
            switch (_state)
            {
            case eTcpClientState.Connected:
                switch (e.SocketError)
                {
                case SocketError.Success:
                    if (e.BytesTransferred > 0)
                    {
                        if (Unpack(e))
                        {
                            lock (_recvs)
                            {
                                while (_recvsBefore.Count > 0)
                                {
                                    _recvs.Enqueue(_recvsBefore.Dequeue());
                                }
                            }

                            BeginRecv();
                        }
                        else
                        {
                            lock (_closeTag)
                            {
                                if (_closeTag.Reason == eTcpClientCloseReason.None)
                                {
                                    _closeTag.Reason = eTcpClientCloseReason.User;
                                    _closeTag.Error = eTcpError.Success;
                                    _closeTag.SockError = SocketError.Success;
                                }
                            }

                            _recving = false;
                        }
                    }
                    else
                    {
                        lock (_closeTag)
                        {
                            if (_closeTag.Reason == eTcpClientCloseReason.None)
                            {
                                _closeTag.Reason = eTcpClientCloseReason.Inactive;
                                _closeTag.Error = eTcpError.Success;
                                _closeTag.SockError = SocketError.Success;
                            }
                        }

                        _recving = false;
                    }
                    break;
                default:
                    lock (_closeTag)
                    {
                        if (_closeTag.Reason == eTcpClientCloseReason.None)
                        {
                            _closeTag.Reason = eTcpClientCloseReason.Exception;
                            _closeTag.Error = eTcpError.SocketError;
                            _closeTag.SockError = e.SocketError;
                        }
                    }

                    _recving = false;
                    break;
                }
                break;
            case eTcpClientState.Connecting:
            case eTcpClientState.DisConnected:
            case eTcpClientState.DisConnecting:
            default:
                _recving = false;
                break;
            }
        }

        bool Unpack(SocketAsyncEventArgs e)
        {
            if (!_recvBuf.Write(_recv, e.BytesTransferred))
            {
                _log.Error(string.Format("[TcpClient] failed to write buf to ring buffer, buf len: {0}", e.BytesTransferred));
                return false;
            }

            while (_recvBuf.UsedCapacity > _pkgLen.Length)
            {
                _recvBuf.Peek(_pkgLen, _pkgLen.Length);

                var pkgLen = BitConverter.ToInt32(_pkgLen, 0);

                if (_recvBuf.UsedCapacity < _pkgLen.Length + pkgLen)
                    break;

                _recvBuf.Read(_pkgLen, _pkgLen.Length);
                byte[] pkg = new byte[1024];
                _recvBuf.Read(pkg, pkgLen);

                _recvsBefore.Enqueue(new ArraySegment<byte>(pkg, 0, pkgLen));
            }

            return true;
        }

        #endregion


        public void Exec()
        {

        }




    }
}
