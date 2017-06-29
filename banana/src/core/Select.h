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

#ifndef _h_banana_core_select_h_
#define _h_banana_core_select_h_

#ifdef _WIN32
#include <winsock.h>
#else
#include <sys/select.h>
#endif // _WIN32

#include <unordered_map>

namespace Banana
{
	namespace Net
	{
		class CFdArgs
		{
		public:
			int _fd;
			int _events;
		};

		class CSelect
		{
		public:
			CSelect();
			~CSelect();

		public:
			bool Register(int fd, int events);
			void Unregister(int fd);
			void Modify(int fd, int events);
			int Poll(int timeout);
			const std::unordered_map<int, int>& GetFds(void) const;

		private:
			int GetValue(int fd) const;

		private:
			fd_set _read_fds;
			fd_set _write_fds;
			fd_set _error_fds;
			std::unordered_map<int, int> _fds;
		};
	}
}

#endif // !_h_banana_core_select_h_

