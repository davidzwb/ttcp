#ifndef SOCKET_H
#define SOCKET_H

#include <cstdio>

#include "inetaddress.h"

class Socket
{
#define BACKLOG 128

protected:
    InetAddress addr_;
    int sockfd_;
    int flags;//ai_flags, AI_PASSIVE or not
    int socktype;

public:
    Socket() : addr_(), sockfd_(-1), flags(0), socktype(0) {}
    Socket(InetAddress addr, bool isTcp, bool isPassive);

    int connect();

    int bind();
    int listen();
    int accept();
};

#endif // SOCKET_H
