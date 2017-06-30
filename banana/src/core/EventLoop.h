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


#ifndef _h_banana_net_eventloop_h_
#define _h_banana_net_eventloop_h_

#include <unordered_map>
#include <functional>

namespace Banana
{
	namespace Net
	{
		class CPoll;

		class CEventLoop
		{
		private:
			typedef std::function<void(int, int)> FdHander;//(fd, events)

			class CFdHandler
			{
			public:
				CFdHandler(int fd, int events, FdHander handler);
			public:
				int _fd;
				int _events;
				FdHander _handler;
			};

		public:
			CEventLoop();
			~CEventLoop();
			CEventLoop(const CEventLoop&) = delete;
			CEventLoop& operator=(const CEventLoop&) = delete;

		public:
			void Run(void);

		public:
			void AddHandler(int fd, FdHander handler, int events);
			void UpdateHandler(int fd, int events);
			void RemoveHandler(int fd);

		private:
			CPoll* _poller;
			std::unordered_map<int, FdHander> _handlers;
		};
	}
}


#endif

