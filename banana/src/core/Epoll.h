/*!
 * \file Epoll.h
 * \date 2017/06/29 16:41
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
#ifndef __h_banana__Epoll_h__
#define __h_banana__Epoll_h__

#ifdef __gnu_linux__

#include "Poll.h"

namespace Banana
{
	namespace Net
	{
		class CEpoll : public CPoll
		{
			enum {MAX_EVENTS = 64,};

			const int kInvalid = -1;

		public:
			CEpoll();
			virtual ~CEpoll();
			CEpoll(const CEpoll&) = delete;
			CEpoll& operator=(const CEpoll&) = delete;

		public:
			virtual bool Register(int fd, int events) override;
			virtual void Unregister(int fd) override;
			virtual void Modify(int fd, int events) override;
			virtual int Poll(int microSeconds) override;

		private:
			int _fd;
		};
	}
}

#endif

#endif	//
