#include "Select.h"
#include "Const.h"



namespace Banana
{
	namespace Net
	{
		//-----------------------------------------------------------------

		CSelect::CSelect()
		{
			FD_ZERO(&_read_fds);
			FD_ZERO(&_write_fds);
			FD_ZERO(&_error_fds);
		}
		CSelect::~CSelect()
		{

		}

		//-----------------------------------------------------------------

		bool CSelect::Register(int fd, int events)
		{
			if (FD_ISSET(fd, &_read_fds) || FD_ISSET(fd, &_write_fds) || FD_ISSET(fd, &_error_fds))
				return false;

			if (events & static_cast<int>(EventType::eEventType_Read))
				FD_SET(fd, &_read_fds);
			if (events & static_cast<int>(EventType::eEventType_Write))
				FD_SET(fd, &_write_fds);
			if (events & static_cast<int>(EventType::eEventType_Error))
				FD_SET(fd, &_error_fds);

			return true;
		}

		void CSelect::Unregister(int fd)
		{
			FD_CLR(fd, &_read_fds);
			FD_CLR(fd, &_write_fds);
			FD_CLR(fd, &_error_fds);
		}
		
		void CSelect::Modify(int fd, int events)
		{
			Unregister(fd);
			Register(fd, events);
		}

		int CSelect::Poll(int timeout)
		{
			_fds.clear();

			struct timeval t;
			t.tv_sec = timeout;
			t.tv_usec = 0;

			fd_set read_fds = _read_fds;
			fd_set write_fds = _write_fds;
			fd_set error_fds = _error_fds;

			int count = ::select(0, &read_fds, &write_fds, &error_fds, &t);
			if (count == 0)
			{
				return 0;
			}

			if (count == -1)
			{
				return -1;
			}

			for each (auto e in read_fds.fd_array)
			{
				if (FD_ISSET(e, &read_fds))
				{
					_fds[e] = GetValue(e) | static_cast<int>(EventType::eEventType_Read);
				}
			}

			for each (auto e in write_fds.fd_array)
			{
				if (FD_ISSET(e, &write_fds))
				{
					_fds[e] = GetValue(e) | static_cast<int>(EventType::eEventType_Write);
				}
			}

			for each (auto e in error_fds.fd_array)
			{
				if (FD_ISSET(e, &error_fds))
				{
					_fds[e] = GetValue(e) | static_cast<int>(EventType::eEventType_Error);
				}
			}

			return 0;
		}

		//-----------------------------------------------------------------

		const std::unordered_map<int, int>& CSelect::GetFds(void) const
		{
			return _fds;
		}

		int CSelect::GetValue(int fd) const
		{
			auto e = _fds.find(fd);

			return e == _fds.end() ? 0 : e->second;
		}

		//-----------------------------------------------------------------

	}
}

