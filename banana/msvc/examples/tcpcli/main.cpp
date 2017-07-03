#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "glog/logging.h"

#pragma comment(lib , "ws2_32.lib")


int main(int argc, char** argv)
{
	/*����Winsock DLL*/
	WSADATA        wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WinSock ��ʼ��ʧ��!\n");
		return 1;
	}

	google::InitGoogleLogging(argv[0]);  //����Ϊ�Լ��Ŀ�ִ���ļ���  

	google::SetLogDestination(google::GLOG_INFO, "./tcpcli");


	int _fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (_fd < 0)
	{
		LOG(ERROR) << "failed";
		return -1;
	}

	LOG(INFO) << "socket() success";

	sockaddr_in _addr;
	::memset(&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = ::htons(6666);
	if (1 != ::inet_pton(AF_INET, "127.0.0.1", &_addr.sin_addr.S_un.S_addr))
	{
		closesocket(_fd); //�ر��׽���  
		WSACleanup();       //�ͷ��׽�����Դ  
		return -1;
	}	

	int rc = ::connect(_fd, (sockaddr*)&_addr, sizeof(_addr));
	if (rc != 0)
	{
		closesocket(_fd); //�ر��׽���  
		WSACleanup();       //�ͷ��׽�����Դ  

		return -1;
	}
	else
	{
		printf("connected\n");
	}

	const int BUFF_LEN = 1024;
	char recvBuf[BUFF_LEN];
	char sendBuf[BUFF_LEN];

	while (true)
	{
		::memset(sendBuf, 0, sizeof(sendBuf));
		::memset(recvBuf, 0, sizeof(recvBuf));

		std::cin >> sendBuf;

		rc = ::send(_fd, sendBuf, strlen(sendBuf), 0);
		if (rc == SOCKET_ERROR)
		{
			closesocket(_fd); //�ر��׽���  
			WSACleanup();       //�ͷ��׽�����Դ  

			return -1;
		}

		rc = ::recv(_fd, recvBuf, sizeof(recvBuf), 0);
		if (rc == -1)
		{
			closesocket(_fd); //�ر��׽���  
			WSACleanup();       //�ͷ��׽�����Դ  
			break;
		}
		else
		{
			std::cout <<  "�ӷ������������ݣ�" << recvBuf << std::endl;
		}
	}

	closesocket(_fd); //�ر��׽���  
	WSACleanup();       //�ͷ��׽�����Դ  

	return 0;
}