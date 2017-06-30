#include "Poll.h"


namespace Banana
{
	namespace Net
	{
		//-----------------------------------------------------------------

		const std::unordered_map<int, int>& CPoll::GetFds() const
		{
			return _fds;
		}

		int CPoll::GetValue(int fd) const
		{
			auto e = _fds.find(fd);

			return e == _fds.end() ? 0 : e->second;
		}

		//-----------------------------------------------------------------

	}
}

