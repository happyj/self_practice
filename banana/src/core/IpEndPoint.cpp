#include "IpEndPoint.h"
#include "assert.h"


namespace Banana
{
    namespace Net
    {
        //-----------------------------------------------------------------

        CIPEndPoint::CIPEndPoint(const CIPAddress& address, int port)
			: _addr(address)
			, _port(port)
        {
			//todo check if port is valid
        }

        //-----------------------------------------------------------------

        int CIPEndPoint::Port(void) const
        {
            return _port;
        }
        const CIPAddress& CIPEndPoint::Address(void) const
        {
            return _addr;
        }

        //-----------------------------------------------------------------
    }
}




