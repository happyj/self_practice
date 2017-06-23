#include "IpAddress.h"
#include <assert.h>

#ifdef _WIN32
#include <WS2tcpip.h>
#else
#include <arpa/inet.h>
#endif


namespace Banana
{
    namespace Net
    {
        //-----------------------------------------------------------------

        CIPAddress::CIPAddress(const char* ip)
        {
			Init(ip);
        }
        CIPAddress::CIPAddress(const std::string& ip)
        {
			Init(ip.c_str());
        }
        CIPAddress::CIPAddress(long ip)
            : _addr(ip)
        {
			::memset(_pAddr, 0, sizeof(_pAddr));

			if (nullptr == ::inet_ntop(AF_INET, &_addr, _pAddr, INET_ADDRSTRLEN))
			{
				//throw exception
			}
        }

        void CIPAddress::Init(const char* ip)
        {
			_addr = 0;
			::memset(_pAddr, 0, sizeof(_pAddr));

            if (1 != ::inet_pton(AF_INET, ip, &_addr))
            {
                //throw exception
            }
			else
			{
				::memcpy(_pAddr, ip, INET_ADDRSTRLEN);
			}
        }

        //-----------------------------------------------------------------

        long CIPAddress::Address(void) const
        {
            return _addr;
        }
        std::string CIPAddress::ToString(void) const
        {
			return _pAddr;
        }

        //-----------------------------------------------------------------
    }
}




