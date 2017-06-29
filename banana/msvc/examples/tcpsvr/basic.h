#pragma once


#include <WS2tcpip.h>
#include <winsock.h>
#include <stdio.h>

namespace tcpsvr
{
	int Runbasic(void)
	{
		/*º”‘ÿWinsock DLL*/
		WSADATA        wsd;
		if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
		{
			printf("WinSock ≥ı ºªØ ß∞‹!\n");
			return 1;
		}

		int _fd = ::socket(AF_INET, SOCK_STREAM, 0);
		if (_fd < 0)
		{
			return -1;
		}

		sockaddr_in _addr;
		::memset(&_addr, 0, sizeof(_addr));
		_addr.sin_family = AF_INET;
		_addr.sin_port = ::htons(6666);
		_addr.sin_addr.S_un.S_addr = ::htonl(INADDR_ANY);

		int ec = ::bind(_fd, (sockaddr*)&_addr, sizeof(_addr));
		if (ec < 0)
		{
			return -1;
		}

		ec = ::listen(_fd, 32);
		if (ec < 0)
		{
			return -1;
		}

		sockaddr_in _cliAddr;
		::memset(&_cliAddr, 0, sizeof(_cliAddr));
		int len = sizeof(_cliAddr);

		char _recvBuf[100];
		memset(_recvBuf, 0, sizeof(_recvBuf));

		while (true)
		{
			int _clifd = ::accept(_fd, (sockaddr*)&_cliAddr, &len);
			if (_clifd < 0)
			{
				printf("Accept failed:%d", WSAGetLastError());
				break;
			}

			//printf("Accept client IP:[%s]\n", inet_ntoa(_cliAddr.sin_addr));
			printf("accept client\n");

			while (true)
			{
				memset(_recvBuf, 0, sizeof(_recvBuf));
				ec = ::recv(_clifd, _recvBuf, 100, 0);
				if (ec == -1)
				{
					printf("recv error\n");
					break;
				}

				printf("recv msg: %s\n", _recvBuf);

				ec = ::send(_clifd, _recvBuf, strlen(_recvBuf), 0);
				if (ec == -1)
				{
					printf("send error\n");
					break;
				}
			}

		}

		return 0;
	}
}