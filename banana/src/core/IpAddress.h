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


#ifndef _h_banana_net_ipaddress_h_
#define _h_banana_net_ipaddress_h_

#include <string>

namespace Banana
{
    namespace Net
    {
        class CIPAddress
        {
        private:
            static const int INET_SUCCESS = 1;

        public:
            static const CIPAddress Any;
            static const CIPAddress Loopback;

        public:
            CIPAddress();
            CIPAddress(const char* ip);
            CIPAddress(const std::string& ip);
            CIPAddress(long ip);
            CIPAddress(const CIPAddress& ip);
            CIPAddress& operator=(const CIPAddress& ip);

        public:
            long Address(void) const;
            std::string ToString(void) const;
            int Family(void) const;

        private:
            void Init(const char* ip);

        private:
            long _addr;
            int _family;
        };
    }
}

#endif // !_h_banana_net_ipaddress_h_


