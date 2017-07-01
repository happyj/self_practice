/*!
 * \file TcpServer.h
 * \date 2017/06/29 10:32
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

#ifndef __h_banana__TcpServer_h__
#define __h_banana__TcpServer_h__


#include <unordered_map>
#include "CallBacks.h"
#include "IpAddress.h"

namespace Banana
{
    namespace Net
    {
        class CIPAddress;
        class CEventLoop;
        class CAcceptor;
		class CTcpConnection;

        class CTcpServer
        {
        public:
            CTcpServer();
			~CTcpServer();
            CTcpServer(const CTcpServer&) = delete;
            CTcpServer& operator=(const CTcpServer&) = delete;

        public:
			void Bind(const CIPAddress& addr, unsigned short port);
            void Start(void);
			void Stop(void);

		private:

        private:
			bool _started;
			bool _stopped;
			CEventLoop* io_loop;
            CAcceptor* _acceptor;
			std::unordered_map<int, CTcpConnection*> _conns;
        };
    }
}

#endif
