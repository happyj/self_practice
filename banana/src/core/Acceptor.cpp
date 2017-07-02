#include "Acceptor.h"
#include "Socket.h"
#include "IpEndPoint.h"
#include "Const.h"
#include "EventLoop.h"
#include "Utils.h"

#include <functional>

namespace Banana
{
    namespace Net
    {
        //-----------------------------------------------------------------

        CAcceptor::CAcceptor(CEventLoop* loop, const CIPEndPoint& ep, newConnCallback callback)
            : _loop(loop)
            , _socket(new CSocket())
            , _listenning(false)
            , _newConnCallback(callback)
        {
            _socket->Init();
            _socket->Bind(ep);

            _loop->AddHandler(_socket->fd()
                              , std::bind(&CAcceptor::HandleRead, this, std::placeholders::_1, std::placeholders::_2)
                              , static_cast<int>(EventType::eEventType_Read));
        }
        CAcceptor::~CAcceptor()
        {
            SAFE_DELETE(_socket);
        }

        //-----------------------------------------------------------------

        void CAcceptor::Start(void)
        {
			_listenning = true;

            _socket->Listen();
        }

        void CAcceptor::Stop(void)
        {
            _listenning = false;

            _loop->RemoveHandler(_socket->fd());
        }

        bool CAcceptor::Listenning(void) const
        {
            return _listenning;
        }

        void CAcceptor::HandleRead(int fd, int events)
        {
            int ec = _socket->Accept();

            if (ec > 0)
            {
                if (_newConnCallback != nullptr)
                {
                    _newConnCallback(ec, _socket->RemoteEndPoint());
                }
            }
            else if (ec == 0)
            {

            }
            else if (ec == -1)
            {

            }
        }

        //-----------------------------------------------------------------
    }
}
