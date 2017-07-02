#include "Socket.h"
#include "IpEndPoint.h"
#include "IpAddress.h"
#include "glog/logging.h"
#include <assert.h>

namespace Banana
{
    namespace Net
    {
        //-----------------------------------------------------------------

        CSocket::CSocket(int fd)
            : _sockfd(fd)
        {

        }
        CSocket::~CSocket(void)
        {
            Destroy();
        }

        //-----------------------------------------------------------------

        bool CSocket::Init(void)
        {
            _sockfd = static_cast<int>(::socket(AF_INET, SOCK_STREAM, 0));
            if (_sockfd < 0)
            {
                LOG(ERROR) << "Failed to init socket.";
                return false;
            }

            SetNonBlock(true);
            setReuseAddr(true);

            return true;
        }
        void CSocket::Destroy(void)
        {
            if (_sockfd != INVALID_FD)
            {
#ifdef _WIN32
                ::shutdown(_sockfd, SD_BOTH);
                ::closesocket(_sockfd);
#else
                ::shutdown(_sockfd, SHUT_RDWR);
                ::close(_sockfd);
#endif
            }
        }
        bool CSocket::Bind(const CIPEndPoint& localEP)
        {
            if (_sockfd == INVALID_FD)
            {
                LOG(ERROR) << "invalid socket fd, can not bind it.";
                return false;
            }

            if (::bind(_sockfd, localEP.SockAddr(), localEP.SockAddrLen()) < 0)
            {
                LOG(ERROR) << "Failed to bind fd: " << _sockfd << " to address: " << localEP.ToString();

                Destroy();
                return false;
            }

            LOG(INFO) << "Successfully bind fd: " << _sockfd << " to address: " << localEP.ToString();

            return true;
        }
        bool CSocket::Listen(int backlog)
        {
            if (::listen(_sockfd, backlog) < 0)
            {
                LOG(ERROR) << "Failed to listen fd: " << _sockfd;

                Destroy();
                return false;
            }

            return true;
        }

        int CSocket::Accept(void)
        {
            sockaddr_in addr;
            ::memset(&addr, 0, sizeof addr);
            int len = sizeof(addr);
            int fd = static_cast<int>(::accept(_sockfd, (sockaddr*)&addr, &len));
            if (fd > 0)
            {
                _peerAddr.SetAddress(addr);
            }
            else if (fd == 0)
            {
                //todo
            }
            else if (fd == -1)
            {

            }

            return fd;
        }
        int CSocket::Send(const char* buf, int len)
        {
            return ::send(_sockfd, buf, len, 0);
        }
        int CSocket::Recv(char* buf, int len)
        {
            return ::recv(_sockfd, buf, len, 0);
        }

        //-----------------------------------------------------------------

        int CSocket::fd(void) const
        {
            return _sockfd;
        }
        const CIPEndPoint& CSocket::RemoteEndPoint(void) const
        {
            return _localAddr;
        }
        const CIPEndPoint& CSocket::LocalEndPoint(void) const
        {
            return _peerAddr;
        }

        //-----------------------------------------------------------------

        void CSocket::SetNonBlock(bool nonblock)
        {
            int flag = -1;
#ifdef _WIN32
            unsigned long nonBlock = (nonblock ? 1 : 0);
            flag = ::ioctlsocket(_sockfd, FIONBIO, &nonBlock);
#else
            flag = ::fcntl(sock, F_GETFL, 0);
            assert(flag >= 0 && "Non Block failed");

            if (nonblock)
                flag = ::fcntl(sock, F_SETFL, flag | O_NONBLOCK);
            else
                flag = ::fcntl(sock, F_SETFL, flag & ~O_NONBLOCK);
#endif

            assert(flag >= 0 && "Non Block failed");
        }

        void CSocket::setTcpNoDelay(bool on)
        {
            char optval = on ? 1 : 0;
            ::setsockopt(_sockfd, IPPROTO_TCP, TCP_NODELAY,
                         &optval, static_cast<socklen_t>(sizeof optval));
        }

        void CSocket::setReuseAddr(bool on)
        {
            char optval = on ? 1 : 0;
            ::setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR,
                         &optval, static_cast<socklen_t>(sizeof optval));
        }

        void CSocket::setReusePort(bool on)
        {
#ifdef SO_REUSEPORT
            int optval = on ? 1 : 0;
            int ret = ::setsockopt(_sockfd, SOL_SOCKET, SO_REUSEPORT,
                                   &optval, static_cast<socklen_t>(sizeof optval));
            if (ret < 0 && on)
            {
                LOG(ERROR) << "SO_REUSEPORT failed.";
            }
#else
            if (on)
            {
                LOG(ERROR) << "SO_REUSEPORT is not supported.";
            }
#endif
        }

        void CSocket::setKeepAlive(bool on)
        {
            char optval = on ? 1 : 0;
            ::setsockopt(_sockfd, SOL_SOCKET, SO_KEEPALIVE,
                         &optval, static_cast<socklen_t>(sizeof optval));
        }
        //-----------------------------------------------------------------

    }
}
