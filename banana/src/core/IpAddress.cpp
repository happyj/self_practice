#include "IpAddress.h"
#include <assert.h>
#include <stdio.h>

#ifdef _WIN32
#include <WS2tcpip.h>
#else
#include <arpa/inet.h>
#endif


namespace Banana
{
    namespace Net
    {
		const CIPAddress CIPAddress::Any = CIPAddress("0.0.0.0");
		const CIPAddress CIPAddress::Loopback = CIPAddress("127.0.0.1");

        //-----------------------------------------------------------------

        CIPAddress::CIPAddress()
            : _addr(0)
            , _family(AF_UNSPEC)
        {

        }
        CIPAddress::CIPAddress(const char* ip)
        {
            Init(ip);
        }
        CIPAddress::CIPAddress(const std::string& ip)
        {
            Init(ip.c_str());
        }
        #ifdef _WIN32
        CIPAddress::CIPAddress(long ip)
            : _addr(::htonl(ip))
        #else
            CIPAddress::CIPAddress(long ip)
            : _addr(ip)
        #endif
            , _family(AF_UNSPEC)
        {
            //检查ip的合法性
            if (ToString().empty())
            {
                //errno
            }
        }
        CIPAddress::CIPAddress(const CIPAddress& ip)
            : _addr(ip.Address())
            , _family(ip.Family())
        {

        }
        CIPAddress& CIPAddress::operator=(const CIPAddress& ip)
        {
            if (this == &ip)
                return *this;

            _addr = ip.Address();
            _family = ip.Family();

            return *this;
        }

        void CIPAddress::Init(const char* ip)
        {
            _addr = 0;
            _family = AF_UNSPEC;

            char buf[sizeof(struct in6_addr)];
            ::memset(buf, 0, sizeof buf);

            if (INET_SUCCESS == ::inet_pton(AF_INET6, ip, &buf))
            {
                _addr = atol(buf);
                _family = AF_INET6;
            }
            else if (INET_SUCCESS == ::inet_pton(AF_INET, ip, &buf))
            {
                _addr = atol(buf);
                _family = AF_INET;
            }
            else
            {
                //errno
            }
        }

        //-----------------------------------------------------------------

        long CIPAddress::Address(void) const
        {
            return _addr;
        }
        std::string CIPAddress::ToString(void) const
        {
            char buf[INET6_ADDRSTRLEN];
            ::memset(buf, 0, sizeof(buf));

            switch (_family)
            {
            case AF_INET:
                if (nullptr == ::inet_ntop(AF_INET, &_addr, buf, INET6_ADDRSTRLEN))
                {
                    //errno
                }
                break;
            case AF_INET6:
                if (nullptr == ::inet_ntop(AF_INET6, &_addr, buf, INET6_ADDRSTRLEN))
                {
                    //errno
                }
                break;
            default:
                break;
            }

            return buf;
        }
        int CIPAddress::Family(void) const
        {
            return _family;
        }

        //-----------------------------------------------------------------
    }
}





