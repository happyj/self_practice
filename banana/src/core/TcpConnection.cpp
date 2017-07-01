#include "TcpConnection.h"
#include "Socket.h"
#include "Utils.h"
#include "Buffer.h"


namespace Banana
{
	namespace Net
	{
		//-----------------------------------------------------------------

		CTcpConnection::CTcpConnection(int fd, const CIPEndPoint& ep)
			: _fd(fd)
			, _peerEp(ep)
			, _socket(new CSocket(fd))
			, _recvBuf(new CBuffer(1024))
			, _sendBuf(new CBuffer(1024))
		{

		}
		
		CTcpConnection::~CTcpConnection()
		{
			SAFE_DELETE(_socket);
			SAFE_DELETE(_recvBuf);
			SAFE_DELETE(_sendBuf);
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

		void CTcpConnection::HandleIO(int fd, int events)
		{
			if (events & static_cast<int>(EventType::eEventType_Read))
			{
				char buf[100];
				::memset(buf, 0, 100);
				int bytes = ::recv(_fd, buf, 100, 0);
				if (bytes > 0)
				{
					printf("sock: %d recv buf: %s\n", buf);
					::send(_fd, buf, strlen(buf), 0);
				}
				else
				{

				}

			}

			if (events & static_cast<int>(EventType::eEventType_Write))
			{

			}

			if (events & static_cast<int>(EventType::eEventType_Error))
			{

			}
		}

		bool CTcpConnection::Send(const char* buf, int len)
		{
			return true;
		}
		void CTcpConnection::Recv(char* buf, int len)
		{

		}
		void CTcpConnection::Stop(void)
		{

		}

		//-----------------------------------------------------------------

	}
}

