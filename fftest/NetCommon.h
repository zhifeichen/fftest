#ifndef NET_COMMON_H
#define NET_COMMON_H

#if  defined(__WIN32__) || defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define CloseSock closesocket
#define rest_getLastError() WSAGetLastError()

#define REST_EWOULDBLOCK WSAEWOULDBLOCK
#define REST_SEND SD_SEND

extern "C" int initializeWinsockIfNecessary();
extern "C" void uninitializeWinsockIfNecessary(void);
#else
/* Unix */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <ctype.h>
#include <fcntl.h>

#define CloseSock close
#define rest_getLastError() errno

#define REST_EWOULDBLOCK EINPROGRESS
#define REST_SEND SHUT_WR

#define initializeWinsockIfNecessary() 1
#define uninitializeWinsockIfNecessary() 
#define SOCKET_ERROR -1
#endif // #if  defined(__WIN32__) || defined(_WIN32)

#endif // #ifndef NET_COMMON_H
