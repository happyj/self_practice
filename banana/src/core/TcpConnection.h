/*!
 * \file TcpConnection.h
 * \date 2017/06/30 16:55
 *
 * \author kerryhe
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#ifndef __h_banana__TcpConnection_h__
#define __h_banana__TcpConnection_h__

#include "IpEndPoint.h"


namespace Banana
{
	namespace Net
	{
		class CIPEndPoint;

		class CTcpConnection
		{
		public:
			CTcpConnection(int fd, const CIPEndPoint& ep);
			~CTcpConnection();

		public:
			int fd(void) const;
			const CIPEndPoint& RemoteEndPoint(void) const;

		private:
			int _fd;
			CIPEndPoint _peerEp;
		};
	}
}

#endif	//
