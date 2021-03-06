#include "EventLoop.h"
#include "Const.h"
#include "Poll.h"
#include "Select.h"
#include "Utils.h"
#include <assert.h>

namespace Banana
{
    namespace Net
    {
        //-----------------------------------------------------------------

        CEventLoop::CFdHandler::CFdHandler(int fd, int events, FdHander handler)
            : _fd(fd)
            , _events(events)
            , _handler(handler)
        {

        }

        //-----------------------------------------------------------------

        CEventLoop::CEventLoop()
            : _poller(new CSelect())
        {

        }

        CEventLoop::~CEventLoop()
        {
            SAFE_DELETE(_poller);
        }

        //-----------------------------------------------------------------

        void CEventLoop::Run()
        {
            while (true)
            {
                int count = _poller->Poll(10);

				if (count > 0)
				{
					for (auto& e : _poller->GetFds())
					{
						auto it = _handlers.find(e.first);

						if (it != _handlers.end() && it->second != nullptr)
						{
							it->second(e.first, e.second);
						}
					}
				}
				else if (count == 0)
				{

				}
				else
				{

				}
            }
        }

        //-----------------------------------------------------------------

		void CEventLoop::AddHandler(int fd, FdHander handler, int events)
        {
			assert(fd != INVALID_FD);
			_handlers.emplace(fd, handler);
			_poller->Register(fd, events | static_cast<int>(EventType::eEventType_Error));
        }
		void CEventLoop::UpdateHandler(int fd, int events)
        {
			_poller->Modify(fd, events | static_cast<int>(EventType::eEventType_Error));
        }
        void CEventLoop::RemoveHandler(int fd)
        {
			_poller->Unregister(fd);
			_handlers.erase(fd);
        }

        //-----------------------------------------------------------------

    }
}

