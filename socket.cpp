#include "socket.h"

Socket::Socket(InetAddress addr, bool isTcp, bool isPassive) : addr_(addr)
{
    socktype = isTcp? SOCK_STREAM : SOCK_DGRAM;
    flags = isPassive? AI_PASSIVE : 0;

    sockfd_ = ::socket(addr_.getFamily(), socktype, 0);

    if (sockfd_ == -1)
        ::perror("create socket");
}

int Socket::connect()
{
    if (::connect(sockfd_, addr_.getSockaddrP(), sizeof(*addr_.getSockaddrP())) != 0)
    {
        ::perror("while connecting");
        return -1;
    }

    return 0;
}

int Socket::bind()
{
    if (::bind(sockfd_, addr_.getSockaddrP(), sizeof(*addr_.getSockaddrP())) != 0)
    {
        ::perror("while binding");
        return -1;
    }

    return 0;
}

int Socket::listen()
{
    if (::listen(sockfd_, BACKLOG) != 0)
    {
        ::perror("while start listening");
        return -1;
    }

    return 0;
}

int Socket::accept()
{
    int connfd = -1;
    connfd = ::accept(sockfd_, NULL, NULL);

    if (connfd == -1)
    {
        ::perror("while accepting");
    }

    return connfd;
}

int Socket::close()
{
    return ::close(this->sockfd_);
}

