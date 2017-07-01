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

#ifndef _h_banana_core_const_h_
#define _h_banana_core_const_h_

namespace Banana
{
    namespace Net
    {
        //# Constants from the epoll module
        const int _EPOLLIN = 0x001;
        const int _EPOLLPRI = 0x002;
        const int _EPOLLOUT = 0x004;
        const int _EPOLLERR = 0x008;
        const int _EPOLLHUP = 0x010;
        const int _EPOLLRDHUP = 0x2000;
        const int _EPOLLONESHOT = (1 << 30);
        const int _EPOLLET = (1 << 31);

        //# Our events map exactly to the epoll events
        enum class EventType
        {
            eEventType_None = 0,
            eEventType_Read = _EPOLLIN,
            eEventType_Write = _EPOLLOUT,
            eEventType_Error = _EPOLLERR | _EPOLLHUP,
        };

		const int _DEFAULT_BACKLOG = 32;
		const int INVALID_FD = -1;

    }
}


#endif
