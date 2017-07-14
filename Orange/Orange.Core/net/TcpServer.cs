using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using log4net;

namespace Orange.Core.net
{




    class CTcpServer
    {
        ILog _log;

        TcpListener _listener;
        bool _listenning;
        eTcpServerState _state;
        CTcpServerCloseArgs _closeTag;

        int _nextCliId;
        Dictionary<int, CTcpClient> _clis;
        Queue<TcpClient> _cliPre;
        Queue<TcpClient> _cliPost;
        Queue<CTcpClient> _clisPool;


        public CTcpServer(ILog log)
        {
            Init(log);
        }

        public void Init(ILog log)
        {
            _log = log;

            _listener = null;
            _listenning = false;
            _state = eTcpServerState.Closed;
            _closeTag = new CTcpServerCloseArgs()
            {
                Reason = eTcpServerCloseReason.None,
                Error = eTcpError.Success,
                SockError = SocketError.Success,
            };

            _nextCliId = 0;
            _clis = new Dictionary<int, CTcpClient>();
            _cliPre = new Queue<TcpClient>();
            _cliPost = new Queue<TcpClient>();
            _clisPool = new Queue<CTcpClient>();
        }

        public void Destroy()
        {

        }

        public void Bind(IPEndPoint ep)
        {
            _listener = new TcpListener(ep);
        }

        public CTcpServerOpenArgs Start()
        {
            switch (_state)
            {
            case eTcpServerState.Closed:
                var e = new CTcpServerOpenArgs()
                {
                    Result = eTcpServerOpenResult.Success,
                    Error = eTcpError.Success,
                    SockError = SocketError.Success,
                };

                _state = eTcpServerState.Opening;

                try
                {
                    _listener.Start();
                }
                catch (SocketException exception)
                {
                    e.Result = eTcpServerOpenResult.Failure;
                    e.Error = eTcpError.SocketError;
                    e.SockError = exception.SocketErrorCode;
                }
                catch
                {
                    e.Result = eTcpServerOpenResult.Failure;
                    e.Error = eTcpError.Exception;
                    e.SockError = SocketError.Success;
                }

                switch (e.Result)
                {
                case eTcpServerOpenResult.Success:
                    _state = eTcpServerState.Opened;
                    _listenning = true;
                    HandleConnection();
                    break;
                case eTcpServerOpenResult.Failure:
                    break;
                }

                return e;
            case eTcpServerState.Closing:
            case eTcpServerState.ClosingWait:
            case eTcpServerState.Opened:
            case eTcpServerState.Opening:
            default:
                return new CTcpServerOpenArgs()
                {
                    Result = eTcpServerOpenResult.Failure,
                    Error = eTcpError.WrongState,
                    SockError = SocketError.Success,
                };
            }
        }

        public void Stop()
        {
            switch (_state)
            {
                case eTcpServerState.Opened:
                    _state = eTcpServerState.Closing;
                    lock(_closeTag)
                    {
                        if (_closeTag.Reason == eTcpServerCloseReason.None)
                        {
                            _closeTag.Reason = eTcpServerCloseReason.Active;
                            _closeTag.Error = eTcpError.Success;
                            _closeTag.SockError = SocketError.Success;
                        }
                    }
                    break;
                case eTcpServerState.Closed:
                    break;
                case eTcpServerState.Closing:
                    break;
                case eTcpServerState.ClosingWait:
                    break;
                case eTcpServerState.Opening:
                    break;
            }
        }

        public event EventHandler<CDataEventArgs<CTcpServerCloseArgs>> Closed;

        void RaiseClosed(CDataEventArgs<CTcpServerCloseArgs> e)
        {
            if (Closed != null)
            {
                Closed(this, e);
            }
        }
        void OnClosed(CTcpServerCloseArgs args)
        {
            RaiseClosed(CDataEventArgs.Create(args));
        }


        public event EventHandler<CDataEventArgs<int>> CliConnected;

        void RaiseCliConnected(CDataEventArgs<int> e)
        {
            if (CliConnected != null)
            {
                CliConnected(this, e);
            }
        }

        void OnCliConnected(int cli)
        {
            RaiseCliConnected(CDataEventArgs.Create(cli));
        }

        public event EventHandler<CDataEventArgs<int, CTcpClientCloseArgs>> CliClosed;

        void RaiseCliClosed(CDataEventArgs<int, CTcpClientCloseArgs> e)
        {
            if (CliClosed != null)
            {
                CliClosed(this, e);
            }
        }

        void OnCliClosed(int cli, CTcpClientCloseArgs args)
        {
            RaiseCliClosed(CDataEventArgs.Create(cli, args));
        }

        private async void HandleConnection()
        {
            TcpClient cli = null;

            bool safe = false;
            try
            {
                cli = await _listener.AcceptTcpClientAsync();
                safe = true;
            }
            catch (SocketException exception)
            {
                lock (_closeTag)
                {
                    if (_closeTag.Reason == eTcpServerCloseReason.None)
                    {
                        _closeTag.Reason = eTcpServerCloseReason.Exception;
                        _closeTag.Error = eTcpError.SocketError;
                        _closeTag.SockError = exception.SocketErrorCode;
                    }
                }
            }
            catch
            {
                lock (_closeTag)
                {
                    if (_closeTag.Reason == eTcpServerCloseReason.None)
                    {
                        _closeTag.Reason = eTcpServerCloseReason.Exception;
                        _closeTag.Error = eTcpError.Exception;
                        _closeTag.SockError = SocketError.Success;
                    }
                }
            }

            if (safe)
            {
                switch (_state)
                {
                case eTcpServerState.Opened:
                    lock (_cliPre)
                    {
                        _cliPre.Enqueue(cli);
                    }

                    HandleConnection();
                    break;
                case eTcpServerState.Closing:
                case eTcpServerState.Closed:
                case eTcpServerState.Opening:
                case eTcpServerState.ClosingWait:
                    try
                    {
                        using (cli)
                        {
                        }
                    }
                    catch
                    {
                    }

                    _listenning = false;
                    break;
                }
            }
            else
            {
                try
                {
                    using (cli)
                    {
                    }
                }
                catch
                {
                }

                _listenning = false;
            }
        }

        public void Exec()
        {
            switch (_state)
            {
                case eTcpServerState.Closed:
                    break;
                case eTcpServerState.Closing:

                    break;
                case eTcpServerState.ClosingWait:
                    break;
                case eTcpServerState.Opened:
                    break;
                case eTcpServerState.Opening:
                    break;
            }

            if (_cliPre.Count > 0)
            {
                lock (_cliPre)
                {
                    while (_cliPre.Count > 0)
                        _cliPost.Enqueue(_cliPre.Dequeue());
                }
            }

            while (_cliPost.Count > 0)
            {
                CTcpClient cli = null;
                if (_clisPool.Count > 0)
                    cli = _clisPool.Dequeue();
                else
                    cli = new CTcpClient(null);

                var cliId = ++_nextCliId;
                _clis.Add(cliId, cli);

                EventHandler<CDataEventArgs<CTcpClientConnectArgs>> cbConnected = null;
                EventHandler<CDataEventArgs<CTcpClientCloseArgs>> cbClosed = null;

                cbConnected = (sender, e) =>
                {
                    try
                    {
                        OnCliConnected(cliId);
                    }
                    catch (Exception exception)
                    {
                        _log.Error(string.Format("[TcpServer]OnCliClosed exception, cli:\"{0}\", closeArgs:\"{1},{2},{3}\"", cliId, e.Arg1.Result, e.Arg1.Error, e.Arg1.SockError), exception);
                    }
                };

                cbClosed = (sender, e) =>
                {
                    try
                    {
                        _clis.Remove(cliId);

                        cli.Connected -= cbConnected;
                        cli.Closed -= cbClosed;

                        _clisPool.Enqueue(cli);

                        OnCliClosed(cliId, e.Arg1);
                    }
                    catch (Exception exception)
                    {
                        _log.Error(string.Format("[TcpServer]OnCliClosed exception, cli:\"{0}\", closeArgs:\"{1},{2},{3}\"", cliId, e.Arg1.Reason, e.Arg1.Error, e.Arg1.SockError), exception);
                    }
                };


                cli.Connected += cbConnected;
                cli.Closed += cbClosed;
                cli.Connect(_cliPost.Dequeue());
            }

            if (_clis.Count > 0)
            {
                foreach (var e in _clis)
                {
                    e.Value.Exec();
                }
            }
        }


    }
}
