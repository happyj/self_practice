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
		public:
			CIPAddress(const char* ip);
			CIPAddress(const std::string& ip);
			CIPAddress(long ip);

		public:
			long Address(void) const;
			std::string ToString(void) const;

		private:
			void Init(const char* ip);

		private:
			long _addr;
			char _pAddr[50];
		};
	}
}

#endif // !_h_banana_net_ipaddress_h_
