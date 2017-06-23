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

namespace Banana
{
	namespace Net
	{
		class CIPEndPoint
		{
		public:
			CIPEndPoint(const CIPAddress& address, int port);

		public:
			int Port(void) const;
			const CIPAddress& Address(void) const;

		private:
			CIPAddress _addr;
			int _port;
		};
	}
}



#endif

