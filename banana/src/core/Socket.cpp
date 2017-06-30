#include "Socket.h"
#include "IpEndPoint.h"
#include "IpAddress.h"

namespace Banana
{
    namespace Net
    {
        //-----------------------------------------------------------------

        CSocket::CSocket(void)
            : _sockfd(-1)
        {
            if (!Init())
            {
                //throw exception
            }
        }
        CSocket::~CSocket(void)
        {
			Destroy();
        }

        bool CSocket::Init(void)
        {
            _sockfd = static_cast<int>(::socket(AF_INET, SOCK_STREAM, 0));
            if (_sockfd < 0)
            {
                return false;
            }

            return true;
        }
        void CSocket::Destroy(void)
        {
#ifdef _WIN32
            if (::closesocket(_sockfd) < 0)
#else
            ::shutdown(_sockfd, SHUT_RDWR);
            if (::close(_sockfd) < 0)
#endif // DEBUG
            {

            }
        }

        //-----------------------------------------------------------------

        bool CSocket::Bind(const CIPEndPoint& localEP)
        {
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
