/*!
 * \file CallBacks.h
 * \date 2017/06/30 10:24
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
#ifndef __h_banana__CallBacks_h__
#define __h_banana__CallBacks_h__

#include <functional>

namespace Banana
{
	namespace Net
	{
		class CIPEndPoint;

		typedef std::function<void(int, const CIPEndPoint&)> newConnCallback;
	}
}

#endif	//
