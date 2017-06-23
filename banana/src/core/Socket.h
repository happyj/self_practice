//////////////////////////////////////////////////////////////////////////
///
///
///
/// Author      : kerryhe
///
///
///
///
///
///
/// Copyright © : All rights reserved
///
//////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#include <winsock.h>
#pragma comment(lib , "ws2_32.lib")
#else
#include <netinet/in.h>
#endif // WIN32

namespace Banana
{
    namespace Net
    {
		class CIPEndPoint;


        class CSocket
        {
        public:
			CSocket(void);
			~CSocket(void);
			CSocket(const CSocket&) = delete;
			CSocket& operator=(const CSocket&) = delete;

		private:
			bool Init(void);
			void Destroy(void);

        public:
            bool Bind(const CIPEndPoint& localEP);
            bool Listen(void);

		public:
			int fd(void) const;

        private:
			int _sockfd;
            sockaddr_in _localAddr;
            sockaddr_in _peerAddr;
        };
    }
}
