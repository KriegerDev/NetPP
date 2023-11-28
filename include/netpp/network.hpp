#ifndef __NETPP_NETWORK_H
#define __NETPP_NETWORK_H

#ifdef NETPP_PLATFORM_WINDOWS
#include <WinSock2.h>
#include <ws2tcpip.h>

#define NETPP_INVALID_SOCKET INVALID_SOCKET
typedef int socklen_t;
typedef SOCKET netpp_sock_t;
typedef int netpp_ssize_t;

#endif

#ifdef NETPP_PLATFORM_LINUX
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#define NETPP_INVALID_SOCKET (-1)
typedef int netpp_sock_t;
typedef ssize_t netpp_ssize_t;
#endif

#include <cerrno>

namespace netpp
{
    enum SOCK_TYPE
    {
        SOCK_TYPE_DGRAM = SOCK_DGRAM,
        SOCK_TYPE_STREAM = SOCK_STREAM,
    };

    enum SOCK_PROTO
    {
        SOCK_PROTO_TCP = IPPROTO_TCP,
        SOCK_PROTO_UDP = IPPROTO_UDP
    };

    enum SOCK_FAMILY
    {
        SOCK_FAMILY_INET = AF_INET,
        SOCK_FAMILY_INET6 = AF_INET6,
        SOCK_FAMILY_UNIX = AF_UNIX
    };

    extern unsigned int g_sockCount;

    class SockAddress;
    class Socket;
}

#endif