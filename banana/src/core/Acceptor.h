/*!
 * \file Acceptor.h
 * \date 2017/06/29 19:57
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

#ifndef __h_banana__Acceptor_h__
#define __h_banana__Acceptor_h__

#include "CallBacks.h"

namespace Banana
{
	namespace Net
	{
		class CSocket;
		class CIPEndPoint;
		class CEventLoop;

		class CAcceptor
		{
		public:
			CAcceptor(CEventLoop* loop, const CIPEndPoint& ep, newConnCallback callback);
			~CAcceptor();
			CAcceptor(const CAcceptor&) = delete;
			CAcceptor& operator=(const CAcceptor&) = delete;

		public:
			void Start(void);
			void Stop(void);
			bool Listenning(void) const;

		private:
			void HandleRead(int fd, int events);

		private:
			CEventLoop* _loop;
			CSocket* _socket;
			bool _listenning;
			newConnCallback _newConnCallback;
		};
	}
}

#endif	//
