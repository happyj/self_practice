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
		enum class EventType
		{
			eEventType_None = 0x001,
			eEventType_Read = 0x002,
			eEventType_Write = 0x004,
			eEventType_Error = 0x008,
		};
	}
}


#endif
