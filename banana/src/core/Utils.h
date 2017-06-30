/*!
 * \file Utils.h
 * \date 2017/06/30 19:00
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
#ifndef __h_banana__Utils_h__
#define __h_banana__Utils_h__


namespace Banana
{
	namespace Net
	{
#ifndef SAFE_DELETE
#define SAFE_DELETE(e) {if(e){delete (e); (e) = nullptr;}}
#endif

	}
}

#endif	//
