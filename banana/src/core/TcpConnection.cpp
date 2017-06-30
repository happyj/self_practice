#include "TcpConnection.h"


namespace Banana
{
	namespace Net
	{
		//-----------------------------------------------------------------

		CTcpConnection::CTcpConnection(int fd, const CIPEndPoint& ep)
			: _fd(fd)
			, _peerEp(ep)
		{

		}
		
		CTcpConnection::~CTcpConnection()
		{

		}

		//-----------------------------------------------------------------

		int CTcpConnection::fd(void) const
		{
			return _fd;
		}
		const CIPEndPoint& CTcpConnection::RemoteEndPoint(void) const
		{
			return _peerEp;
		}

		//-----------------------------------------------------------------

	}
}

