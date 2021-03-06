#include "IpEndPoint.h"
#include "assert.h"
#include "glog/logging.h"

#ifdef _WIN32
#include <WS2tcpip.h>
#else
#include <arpa/inet.h>
#endif


//     /* Structure describing an Internet socket address.  */
//     struct sockaddr_in {
//         sa_family_t    sin_family; /* address family: AF_INET */
//         uint16_t       sin_port;   /* port in network byte order */
//         struct in_addr sin_addr;   /* internet address */
//     };
//
//     /* Internet address. */
//     typedef uint32_t in_addr_t;
//     struct in_addr {
//         in_addr_t       s_addr;     /* address in network byte order */
//     };
//
//     struct sockaddr_in6 {
//         sa_family_t     sin6_family;   /* address family: AF_INET6 */
//         uint16_t        sin6_port;     /* port in network byte order */
//         uint32_t        sin6_flowinfo; /* IPv6 flow information */
//         struct in6_addr sin6_addr;     /* IPv6 address */
//         uint32_t        sin6_scope_id; /* IPv6 scope-id */
//     };

// struct in6_addr {
// 	uint8_t s6_addr[16];              /* IPv6  address */
// };

#pragma warning(disable: 4996)

namespace Banana
{
    namespace Net
    {
        //-----------------------------------------------------------------

        CIPEndPoint::CIPEndPoint()
        {
			Init(CIPAddress::Any, 0);
        }
        CIPEndPoint::CIPEndPoint(const CIPAddress& address, unsigned short port)
            : _addr(address)
            , _port(port)
        {
			Init(address, port);
        }
        CIPEndPoint::CIPEndPoint(const CIPEndPoint& ep)
        {
			Init(ep.Address(), ep.Port());
        }
        CIPEndPoint& CIPEndPoint::operator=(const CIPEndPoint& ep)
        {
            if (this == &ep)
                return *this;

			Init(ep.Address(), ep.Port());

            return *this;
        }
		void CIPEndPoint::Init(const CIPAddress& addr, unsigned short port)
		{
			_addr = addr;
			_port = port;

			::memset(&_sock4, 0, sizeof _sock4);
			::memset(&_sock6, 0, sizeof _sock6);
#ifdef _WIN32
			switch (Family())
			{
			case AF_INET:
				_sock4.sin_family = AF_INET;
				_sock4.sin_port = ::htons(_port);
				_sock4.sin_addr.S_un.S_addr = ::htonl(_addr.Address());
				break;
			case AF_INET6:
				_sock6.sin6_family = AF_INET6;
				_sock6.sin6_port = ::htons(_port);
				sprintf((char*)_sock6.sin6_addr.u.Byte, "%d", _addr.Address());
				break;
			default:
				break;
			}
#else
            switch (Family())
            {
            case AF_INET:
                _sock4.sin_family = AF_INET;
                _sock4.sin_port = ::htons(_port);
                if (::inet_pton(AF_INET, "", &_sock4.sin_addr) <= 0)
                {
                    LOG(ERROR) << "failed to convert ipv4 address";
                }
                //_sock4.sin_addr = ::htonl(_addr.Address());
                break;
            case AF_INET6:
                _sock6.sin6_family = AF_INET6;
                _sock6.sin6_port = ::htons(_port);
                if (::inet_pton(AF_INET6, "ip", &addr->sin6_addr) <= 0)
                {
                    LOG(ERROR) << "failed to convert ipv6 address";
                }
                //sprintf((char*)_sock6.sin6_addr.u.Byte, "%d", _addr.Address());
                break;
            default:
                break;
            }
#endif            
		}

        //-----------------------------------------------------------------

        unsigned short CIPEndPoint::Port(void) const
        {
			return _port;
        }
        const CIPAddress& CIPEndPoint::Address(void) const
        {
            return _addr;
        }
        int CIPEndPoint::Family(void) const
        {
            return _addr.Family();
        }
		std::string CIPEndPoint::ToString(void) const
		{
			char tmp[10];
			return _addr.ToString() + ":" + itoa(_port, tmp, 10);
		}

        //-----------------------------------------------------------------

        sockaddr* CIPEndPoint::SockAddr(void) const
        {
            switch (Family())
            {
            case AF_INET:
                return (sockaddr*)&_sock4;
            case AF_INET6:
                return (sockaddr*)&_sock6;
            default:
                return nullptr;
            }
        }
        int CIPEndPoint::SockAddrLen(void) const
        {
            switch (Family())
            {
            case AF_INET:
                return sizeof _sock4;
            case AF_INET6:
                return sizeof _sock6;
            default:
                return 0;
            }
        }

        //-----------------------------------------------------------------

        void CIPEndPoint::SetAddress(const sockaddr_in& addr)
        {

        }
        void CIPEndPoint::SetAddress(const sockaddr_in6& addr)
        {

        }

        //-----------------------------------------------------------------
    }
}




