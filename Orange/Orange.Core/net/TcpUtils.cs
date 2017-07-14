using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;


namespace Orange.Core.net
{
    public enum eTcpError
    {
        Success,
        SocketError,
        Exception,
        WrongState,
        ArgumentNullRange,
    }

    public enum eTcpServerOpenResult
    {
        Success,
        Failure,
    }

    public enum eTcpServerState
    {
        Opened,
        Opening,
        Closed,
        Closing,
        ClosingWait,
    }

    public class CTcpServerOpenArgs
    {
        public eTcpServerOpenResult Result
        {
            get;
            set;
        }

        public eTcpError Error
        {
            get;
            set;
        }

        public SocketError SockError
        {
            get;
            set;
        }
    }

    public enum eTcpServerCloseReason
    {
        None,
        Exception,
        Active,
    }

    public enum eTcpClientState
    {
        DisConnected,
        DisConnecting,
        Connected,
        Connecting,
    }

    public enum eTcpClientCloseReason
    {
        None,
        Exception,
        User,
        Inactive,
    }

    public enum eTcpClientConnectResult
    {
        Success,
        Failure,
    }

    public class CTcpServerCloseArgs
    {
        public eTcpServerCloseReason Reason
        {
            get;
            set;
        }

        public eTcpError Error
        {
            get;
            set;
        }

        public SocketError SockError
        {
            get;
            set;
        }
    }

    public class CTcpClientConnectArgs
    {
        public eTcpClientConnectResult Result
        {
            get;
            set;
        }

        public eTcpError Error
        {
            get;
            set;
        }

        public SocketError SockError
        {
            get;
            set;
        }
    }

    public class CTcpClientCloseArgs
    {
        public eTcpClientCloseReason Reason
        {
            get;
            set;
        }

        public eTcpError Error
        {
            get;
            set;
        }

        public SocketError SockError
        {
            get;
            set;
        }
    }
}
