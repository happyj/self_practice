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


#ifndef _h_banana_asio_ipendpoint_h_
#define _h_banana_asio_ipendpoint_h_

#include "IpAddress.h"
#include <string>

#ifdef _WIN32
#include <WS2tcpip.h>
#else
#include <netinet/in.h>
#endif // _WIN32


namespace Banana
{
    namespace Net
    {
        class CIPEndPoint
        {
        public:
            CIPEndPoint();
            CIPEndPoint(const CIPAddress& address, unsigned short port);
            CIPEndPoint(const CIPEndPoint& ep);
            CIPEndPoint& operator=(const CIPEndPoint& ep);

		private:
			void Init(const CIPAddress& addr, unsigned short port);

        public:
            unsigned short Port(void) const;
            const CIPAddress& Address(void) const;
            int Family(void) const;
			std::string ToString(void) const;

		public:
			sockaddr* SockAddr(void) const;
			int SockAddrLen(void) const;

        public:
            void SetAddress(const sockaddr_in& addr);
            void SetAddress(const sockaddr_in6& addr);

        private:
            CIPAddress _addr;
            unsigned short _port;
			union
			{
				sockaddr_in _sock4;
				sockaddr_in6 _sock6;
			};
        };
    }
}



#endif

