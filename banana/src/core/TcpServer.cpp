#include "TcpServer.h"
#include "IpEndPoint.h"
#include "Acceptor.h"
#include "Const.h"
#include "EventLoop.h"
#include "TcpConnection.h"
#include "Utils.h"

#include <functional>

namespace Banana
{
    namespace Net
    {
        //----------------------------------------------------------

        CTcpServer::CTcpServer()
            : _started(false)
            , _stopped(false)
			, io_loop(new CEventLoop())
			, _acceptor(nullptr)
        {

        }

        CTcpServer::~CTcpServer()
        {
            SAFE_DELETE(io_loop);
            SAFE_DELETE(_acceptor);

			for (auto& conn : _conns)
			{
				//conn->second->Stop();
			}
        }

        //----------------------------------------------------------

        void CTcpServer::Bind(const CIPAddress& addr, unsigned short port)
        {
            //_acceptor = new CAcceptor(ep, std::bind(&CTcpServer::HandleConnection, this, std::placeholders::_1, std::placeholders::_2));
            _acceptor = new CAcceptor(io_loop, CIPEndPoint(addr, port), [&](int fd, const CIPEndPoint & ep)
            {
				printf("new conn: %d\n", fd);
                CTcpConnection* conn = new CTcpConnection(fd, ep);
                _conns.insert(std::make_pair(fd, conn));

                io_loop->AddHandler(fd
                                    , std::bind(&CTcpConnection::HandleIO, conn, std::placeholders::_1, std::placeholders::_2)
                                    , static_cast<int>(EventType::eEventType_Read) | static_cast<int>(EventType::eEventType_Write));
            });
        }

        void CTcpServer::Start(void)
        {
            _acceptor->Start();
        }

		void CTcpServer::Stop()
		{

		}

        //----------------------------------------------------------



        //----------------------------------------------------------

    }
}

