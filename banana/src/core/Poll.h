/*!
 * \file Poll.h
 * \date 2017/06/29 17:08
 *
 * \author kerryhe
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __h_banana__Poll_h__
#define __h_banana__Poll_h__

#include <unordered_map>

namespace Banana
{
	namespace Net
	{
		class CPoll
		{
		public:
			CPoll() = default;
			virtual ~CPoll() = default;

			CPoll(const CPoll&) = delete;
			CPoll& operator=(const CPoll&) = delete;

		public:
			virtual bool Register(int fd, int events) = 0;
			virtual bool Unregister(int fd) = 0;
			virtual bool Modify(int fd, int events) = 0;
			virtual int Poll(int microSeconds) = 0;

		public:
			const std::unordered_map<int, int>& GetFds(void) const;
			int GetValue(int fd) const;

		protected:
			std::unordered_map<int, int> _fds;
		};
	}
}

#endif	//
