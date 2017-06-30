#include "TcpServer.h"
#include "IpEndPoint.h"
#include "Acceptor.h"
#include "Const.h"
#include "EventLoop.h"
#include "TcpConnection.h"

#include <functional>

namespace Banana
{
    namespace Net
    {
        //----------------------------------------------------------

        CTcpServer::CTcpServer()
            : _started(false)
            , _stopped(false)
        {

        }

        CTcpServer::~CTcpServer()
        {
            SAFE_DELETE(io_loop);
            SAFE_DELETE(_acceptor);
        }

        //----------------------------------------------------------

        void CTcpServer::Bind(const CIPEndPoint& ep)
        {
            //_acceptor = new CAcceptor(ep, std::bind(&CTcpServer::HandleConnection, this, std::placeholders::_1, std::placeholders::_2));
            _acceptor = new CAcceptor(ep, [&](int fd, const CIPEndPoint & ep)
            {
                CTcpConnection* conn = new CTcpConnection(fd, ep);
				_conns.insert(std::make_pair(fd, conn));
            });
        }
        void CTcpServer::Start(void)
        {
            _acceptor->Start();
        }

        //----------------------------------------------------------



        //----------------------------------------------------------

    }
}

