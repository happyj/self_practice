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
            CSocket(void);
            ~CSocket(void);
            CSocket(const CSocket&) = delete;
            CSocket& operator=(const CSocket&) = delete;

        private:
            bool Init(void);
            void Destroy(void);

        public:
            bool Bind(const CIPEndPoint& localEP);
            bool Listen(int backlog = _DEFAULT_BACKLOG);
            int Accept(void);

        public:
            int fd(void) const;
            const CIPEndPoint& RemoteEndPoint(void) const;
            const CIPEndPoint& LocalEndPoint(void) const;

        private:
            int _sockfd;
            CIPEndPoint _localAddr;
            CIPEndPoint _peerAddr;
        };
    }
}
