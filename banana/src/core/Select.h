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

#include "Poll.h"

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

		class CSelect : public CPoll
		{
		public:
			CSelect();
			virtual ~CSelect();
			CSelect(const CSelect&) = delete;
			CSelect& operator=(const CSelect&) = delete;

		public:
			virtual bool Register(int fd, int events) override;
			virtual bool Unregister(int fd) override;
			virtual bool Modify(int fd, int events) override;
			virtual int Poll(int microSeconds) override;

		private:
			fd_set _read_fds;
			fd_set _write_fds;
			fd_set _error_fds;
		};
	}
}

#endif // !_h_banana_core_select_h_

