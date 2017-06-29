#include "basic.h"
#include "selector.h"
#pragma comment(lib , "ws2_32.lib")



int main(int argc, char** argv)
{
	//return tcpsvr::Runbasic();
	return tcpsvr::RunSelect();
}

// 
// int main(int argc, char** argv)
// {
//     /*º”‘ÿWinsock DLL*/
//     WSADATA        wsd;
//     if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
//     {
//         printf("WinSock ≥ı ºªØ ß∞‹!\n");
//         return 1;
// 
//     }
// 	char ip[20];
// 	memset(ip, 0 , sizeof(ip));
// 	long _addr = 0;
// 	if (1 != ::inet_pton(AF_INET, "10.0.1.2", &_addr))
// 	{
// 		printf("error\n");
// 	}
// 	else
// 	{
// 		printf("success, ip: %d\n", _addr);
// 	}
// 
// 	if (NULL == ::inet_ntop(AF_INET, &_addr, ip, 16))
// 	{
// 		printf("error\n");
// 	}
// 	else
// 	{
// 		printf("success, ip: %s\n", ip);
// 	}
// 
//     int listenfd = ::socket(AF_INET, SOCK_STREAM, 0);
//     if (listenfd < 0)//INVALID_SOCKET
//         return -1;
// 
//     int rc, on = 1;
// 
//     rc = ::setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
//     if (rc < 0)
//         return -1;
// 
//     sockaddr_in addr;
//     ::memset(&addr, 0, sizeof(addr));
//     addr.sin_family = AF_INET;
//     addr.sin_addr.S_un.S_addr = ::htonl(INADDR_ANY);
//     addr.sin_port = 6666;
// 
//     rc = ::bind(listenfd, (sockaddr*)&addr, sizeof(addr));
//     if (rc < 0)
//     {
//         ::closesocket(listenfd);
//         return -1;
//     }
// 
//     rc = ::listen(listenfd, 32);
//     if (rc < 0)
//     {
//         ::closesocket(listenfd);
//         return -1;
//     }
// 
// 
//     int len = 0;
//     int    max_sd, new_sd;
//     int    desc_ready, end_server = FALSE;
//     int    close_conn;
//     char   buffer[80];
//     memset(buffer, 0, sizeof(buffer));
//     struct timeval       timeout;
//     struct fd_set        master_set, working_set;
// 
//     FD_ZERO(&master_set);
//     max_sd = listenfd;
//     FD_SET(listenfd, &master_set);
// 
//     timeout.tv_sec = 180;
//     timeout.tv_usec = 0;
// 
//     do
//     {
//         ::memcpy(&working_set, &master_set, sizeof(master_set));
//         printf("waiting for select...\n");
// 
//         rc = ::select(max_sd + 1, &working_set, NULL, NULL, &timeout);
//         if (rc < 0)
//         {
//             printf("failed to select\n");
//             break;
//         }
// 
//         if (rc == 0)
//         {
//             printf("  select() timed out.  End program.\n");
//             break;
//         }
// 
//         desc_ready = rc;
// 
//         for (int i = 0; i <= max_sd && desc_ready > 0 ; ++i)
//         {
//             if (FD_ISSET(i, &working_set))
//             {
//                 desc_ready -= 1;
// 
//                 if (i == listenfd)
//                 {
//                     printf("  Listening socket is readable\n");
// 
//                     do
//                     {
//                         new_sd = ::accept(listenfd, NULL, NULL);
//                         if (new_sd < 0)
//                         {
//                             if (errno != EWOULDBLOCK)
//                             {
//                                 perror("  accept() failed");
//                                 end_server = TRUE;
//                             }
//                             break;
//                         }
// 
//                         printf("  New incoming connection - %d\n", new_sd);
//                         FD_SET(new_sd, &master_set);
//                         if (new_sd > max_sd)
//                             max_sd = new_sd;
// 
//                     }
//                     while (new_sd != -1);
//                 }
//                 else
//                 {
//                     printf("  Descriptor %d is readable\n", i);
//                     close_conn = FALSE;
// 
//                     do
//                     {
//                         rc = ::recv(i, buffer, sizeof(buffer), 0);
//                         if (rc < 0)
//                         {
//                             if (errno != EWOULDBLOCK)
//                             {
//                                 perror("  recv() failed");
//                                 close_conn = TRUE;
//                             }
//                         }
// 
//                         if (rc == 0)
//                         {
//                             printf("  Connection closed\n");
//                             close_conn = TRUE;
//                             break;
//                         }
// 
//                         len = rc;
//                         printf("  %d bytes received\n", len);
//                         rc = ::send(i, buffer, len, 0);
//                         if (rc < 0)
//                         {
//                             perror("  send() failed");
//                             close_conn = TRUE;
//                             break;
//                         }
// 
//                     }
//                     while (TRUE);
// 
//                     if (close_conn == TRUE)
//                     {
//                         ::closesocket(i);
//                         FD_CLR(i, &master_set);
//                         if (i == max_sd)
//                         {
//                             while (FD_ISSET(max_sd, &master_set) == FALSE)
//                                 max_sd -= 1;
//                         }
//                     }
//                 }
//             }
//         }
// 
//     }
//     while (end_server == FALSE);
// 
//     for (int i = 0; i <= max_sd; ++i)
//     {
//         if (FD_ISSET(i, &master_set))
//             ::closesocket(i);
//     }
// 
//     return 0;
// }