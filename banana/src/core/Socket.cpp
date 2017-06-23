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
			::memset(&_localAddr, 0, sizeof(_localAddr));
			::memset(&_peerAddr, 0, sizeof(_peerAddr));

			if (!Init())
			{
				//throw exception
			}
		}
		CSocket::~CSocket(void)
		{
			
		}

		bool CSocket::Init(void)
		{
			_sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
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

			_localAddr.sin_family = AF_INET;
			_localAddr.sin_port = localEP.Port();
			_localAddr.sin_addr.S_un.S_addr = localEP.Address().Address();

			return true;
		}
		bool CSocket::Listen(void)
		{
			if (::listen(_sockfd, 32) < 0)
			{
				return false;
			}

			return true;
		}

        //-----------------------------------------------------------------

		int CSocket::fd(void) const
		{
			return _sockfd;
		}

		//-----------------------------------------------------------------

    }
}
