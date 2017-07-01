/*!
 * \file all.h
 * \date 2017/07/01 15:29
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
#ifndef __h_banana__all_h__
#define __h_banana__all_h__

#include "core/TcpServer.h"


namespace tcpsvr
{
	int RunCore()
	{
		Banana::Net::CTcpServer server;

		server.Bind(Banana::Net::CIPAddress::Loopback, 6666);
		server.Start();

		return 0;
	}
}

#endif	//
