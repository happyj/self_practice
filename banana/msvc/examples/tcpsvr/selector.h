#pragma once



#include <WS2tcpip.h>
#include <winsock.h>
#include <stdio.h>
#include <fcntl.h>
#include "core/Select.h"
#include "core/Const.h"


namespace tcpsvr
{
    int RunSelect(void)
    {
        /*加载Winsock DLL*/
        WSADATA        wsd;
        if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
        {
            printf("WinSock 初始化失败!\n");
            return 1;
        }

        int _fd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (_fd == -1)
        {
            return -1;
        }

        sockaddr_in _addr;
        ::memset(&_addr, 0, sizeof(_addr));
        _addr.sin_port = ::htons(6666);
        _addr.sin_family = AF_INET;
        _addr.sin_addr.S_un.S_addr = ::htonl(INADDR_ANY);

        int ec = ::bind(_fd, (sockaddr*)&_addr, sizeof(_addr));
        if (ec < 0)
        {
            return -1;
        }

        int on = 1;
        ec = ::setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
        if (ec < 0)
		{
			return -1;
		}

		int flags = 1;
		if (0 != ioctlsocket(_fd, FIONBIO, (unsigned long*)&flags))
		{
			return -1;
		}
// 		int flags = fcntl(sockfd, F_GETFL, 0);                        //获取文件的flags值。
// 
// 		fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);   //设置成非阻塞模式；

        ec = ::listen(_fd, 32);
        if (ec < 0)
        {
            return -1;
        }

        fd_set _readfds, _writefds;
        FD_ZERO(&_readfds);
        FD_ZERO(&_writefds);
        FD_SET(_fd, &_readfds);

        timeval _timeval;
        _timeval.tv_sec = 60;
        _timeval.tv_usec = 0;

        char _buf[1024];
        ::memset(_buf, 0, sizeof(_buf));

        bool _stoploop = false;
        int _maxfds = _fd;
        int _newfd = 0;
        bool _closeconn = false;

        fd_set _workingfds;

		printf("prepared....\n");

		Banana::Net::CSelect selector;
		selector.Register(_fd, (int)Banana::Net::EventType::eEventType_Read);

        do
        {
			::memset(_buf, 0, sizeof(_buf));

			selector.Poll(60);

			auto& fds = selector.GetFds();

			for (auto& e : fds)
			{
				if (e.second & (int)Banana::Net::EventType::eEventType_Read)
				{
					if (e.first == _fd)
					{
						_newfd = 0;

						do
						{
							_newfd = ::accept(_fd, nullptr, nullptr);
							if (_newfd == -1)
							{
								if (WSAGetLastError() == WSAENOTSOCK)
								{
									printf("failed to accept new conn\n");
									_stoploop = true;

								}
								break;
								//printf("accept error: %d\n", (int)WSAGetLastError());
							}
							else
							{
								printf("new connection, fd: %d\n", _newfd);
								selector.Register(_newfd, (int)Banana::Net::EventType::eEventType_Read);
							}
						} while (_newfd != -1);
					}
					else
					{
						_closeconn = false;

						do
						{
							int num = ::recv(e.first, _buf, sizeof _buf, 0);
							if (num == -1)
							{
								if (WSAGetLastError() == WSAENOTSOCK)
								{
									printf("read err from fd: %d, error no: %d\n", e.first, (int)WSAGetLastError());
									_closeconn = true;
								}
								break;
							}
							else
							{
								printf("recv msg from socket: %d, content: %s\n", e.first, _buf);
								int ec = ::send(e.first, _buf, num, 0);
								if (ec == -1)
								{
									_closeconn = true;
								}
							}
						} while (!_closeconn);

						if (_closeconn)
						{
							::closesocket(e.first);
							selector.Unregister(e.first);
						}
					}
				}
			}

//             //printf("prepared....\n");
//             ::memcpy(&_workingfds, &_readfds, sizeof _readfds);
//             ::memset(_buf, 0, sizeof(_buf));
// 
//             int count = ::select(_maxfds + 1, &_workingfds, &_writefds, nullptr, &_timeval);
//             if (count == -1)
//             {
//                 printf("failed to select\n");
//                 break;
//             }
// 
//             //printf("select count: %d\n", count);
// 			printf("_workingfds count:%d\n", _workingfds.fd_count);
//             for (int i = 0; i <= _maxfds && count > 0; ++i)
//             {
//                 if (FD_ISSET(i, &_workingfds))
//                 {
//                     count--;
// 
//                     //new connection
//                     if (i == _fd)
//                     {
//                         _newfd = 0;
// 
//                         do
//                         {
//                             _newfd = ::accept(_fd, nullptr, nullptr);
//                             if (_newfd == -1)
//                             {
// 								if (WSAGetLastError() == WSAENOTSOCK)
// 								{
// 									printf("failed to accept new conn\n");
// 									_stoploop = true;
// 									
// 								}
// 								break;
// 								//printf("accept error: %d\n", (int)WSAGetLastError());
//                             }
//                             else
//                             {
//                                 printf("new connection, fd: %d\n", _newfd);
//                                 FD_SET(_newfd, &_readfds);
//                                 if (_newfd > _maxfds)_maxfds = _newfd;
//                             }
//                         }
//                         while (_newfd != -1);
// 
//                     }
//                     else
//                     {
//                         _closeconn = false;
// 
//                         do
//                         {
//                             int num = ::recv(i, _buf, sizeof _buf, 0);
//                             if (num == -1)
//                             {
// 								if (WSAGetLastError() == WSAENOTSOCK)
// 								{
// 									printf("read err from fd: %d, error no: %d\n", i, (int)WSAGetLastError());
// 									_closeconn = true;
// 								}
// 								break;
//                             }
//                             else
//                             {
// 								printf("recv msg from socket: %d, content: %s\n", i, _buf);
//                                 int ec = ::send(i, _buf, num, 0);
//                                 if (ec == -1)
//                                 {
//                                     _closeconn = true;
//                                 }
//                             }
//                         }
//                         while (!_closeconn);
// 
//                         if (_closeconn)
//                         {
//                             ::closesocket(i);
//                             FD_CLR(i, &_readfds);
//                             if (i == _maxfds)
//                             {
//                                 while (FD_ISSET(_maxfds, &_readfds) == FALSE)
//                                 {
//                                     _maxfds--;
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }


        }
        while (!_stoploop);

        for (int i = 0; i < _maxfds; ++i)
        {
            if (FD_ISSET(i, &_readfds))
            {
                ::closesocket(i);
            }
        }

        return 0;
    }
}
