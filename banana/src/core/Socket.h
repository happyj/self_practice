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

#include "IpEndPoint.h"
#include "Const.h"


namespace Banana
{
    namespace Net
    {
        class CSocket
        {
        public:
            explicit CSocket(int fd = INVALID_FD);
            ~CSocket(void);
            CSocket(const CSocket&) = delete;
            CSocket& operator=(const CSocket&) = delete;

		public:
			bool Init(void);
			void Destroy(void);
            bool Bind(const CIPEndPoint& localEP);
            bool Listen(int backlog = _DEFAULT_BACKLOG);
            int Accept(void);
			int Send(const char* buf, int len);
			int Recv(char* buf, int len);

        public:
            int fd(void) const;
            const CIPEndPoint& RemoteEndPoint(void) const;
            const CIPEndPoint& LocalEndPoint(void) const;

		private:
			void SetNonBlock(bool nonblock);
			///
			/// Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm).
			///
			void setTcpNoDelay(bool on);

			///
			/// Enable/disable SO_REUSEADDR
			///
			void setReuseAddr(bool on);

			///
			/// Enable/disable SO_REUSEPORT
			///
			void setReusePort(bool on);

			///
			/// Enable/disable SO_KEEPALIVE
			///
			void setKeepAlive(bool on);

        private:
            int _sockfd;
            CIPEndPoint _localAddr;
            CIPEndPoint _peerAddr;
        };
    }
}
