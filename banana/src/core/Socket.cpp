#include "Socket.h"
#include "IpEndPoint.h"
#include "IpAddress.h"

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

        //-----------------------------------------------------------------

        bool CSocket::Init(void)
        {
            _sockfd = static_cast<int>(::socket(AF_INET, SOCK_STREAM, 0));
            if (_sockfd < 0)
            {
                return false;
            }

            return true;
        }
        bool CSocket::Bind(const CIPEndPoint& localEP)
        {
			if (_sockfd != INVALID_FD)
				return false;

            if (::bind(_sockfd, (sockaddr*)&_localAddr, sizeof(_localAddr)) < 0)
            {
                return false;
            }

            return true;
        }
        bool CSocket::Listen(int backlog)
        {
            if (::listen(_sockfd, backlog) < 0)
            {
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

    }
}
