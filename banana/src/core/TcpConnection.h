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
		class CSocket;
		class CBuffer;

		class CTcpConnection
		{
			static const int IO_ERROR = -1;
		public:
			CTcpConnection(int fd, const CIPEndPoint& ep);
			~CTcpConnection();

		public:
			int fd(void) const;
			const CIPEndPoint& RemoteEndPoint(void) const;

		public:
			void HandleIO(int fd, int events);
			bool Send(const char* buf, int len);
			void Recv(char* buf, int len);
			void Stop(void);

		private:
			int _fd;
			CIPEndPoint _peerEp;
			CSocket* _socket;
			CBuffer* _recvBuf;
			CBuffer* _sendBuf;
		};
	}
}

#endif	//
