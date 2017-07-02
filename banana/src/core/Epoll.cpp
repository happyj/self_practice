#ifdef __gnu_linux__

#include "Epoll.h"

#include <sys/epoll.h>
#include <string.h>
#include <unistd.h>

namespace Banana
{
	namespace Net
	{
		//-----------------------------------------------------------------
		
		CEpoll::CEpoll()
		{
			_fd = epoll_create1(EPOLL_CLOEXEC);
			if (_fd == kInvalid)
			{
				//throw exception
			}
		}
		CEpoll::~CEpoll()
		{
			if (_fd != kInvalid)
			{
				::close(_fd);
			}
		}

		//-----------------------------------------------------------------

		bool CEpoll::Register(int fd, int events)
		{
			struct epoll_event ev;
			ev.events = events;
			ev.data.fd = fd;

			if (epoll_ctl(_fd, EPOLL_CTL_ADD, fd, &ev) == -1)
				return false;

			return true;
		}

		bool CEpoll::Unregister(int fd)
		{
			struct epoll_event ev;

			if (epoll_ctl(_fd, EPOLL_CTL_DEL, fd, &ev) == -1)
				return false;
			return true;
		}

		bool CEpoll::Modify(int fd, int events)
		{
			struct epoll_event ev;
			ev.events = events;
			ev.data.fd = fd;

			if (epoll_ctl(_fd, EPOLL_CTL_MOD, fd, &ev) == -1)
				return false;
			return true;
		}

		int CEpoll::Poll(int microSeconds)
		{
			struct epoll_event evlist[MAX_EVENTS];
			::memset(evlist, 0, sizeof(struct epoll_event));

			int count = epoll_wait(_fd, evlist, MAX_EVENTS, microSeconds);
			if (count <= 0)
			{
				return count;
			}

			for (int i = 0; i < count; ++i)
			{
				_fds[evlist[i].data.fd] = evlist[i].events;
			}

			return count;
		}

		//-----------------------------------------------------------------


	}
}

#endif
