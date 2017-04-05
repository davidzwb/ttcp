#include "tcpstream.h"

bool TcpStream::start()
{
    //server
    if (flags == AI_PASSIVE)
    {
        if (bind() == -1)
            return false;

        if (listen() == -1)
            return false;

//        if ((connfd_ = accept()) < 0)
//            return false;

//        sockfd_ = connfd_;
    }
    else //client
    {
        if (connect() == -1)
            return false;
    }

    return true;
}

bool TcpStream::accept(TcpStream &tcpstream)
{
    if (flags != AI_PASSIVE)
        return false;

    int connfd = Socket::accept();

    if (connfd < 0)
        return false;

    tcpstream.sockfd_ = connfd;

    return true;
}

bool TcpStream::writeALL(const std::string &buf)
{
    int num = 0;
    int left = buf.size();

    while (left > 0)
    {
        num = ::write(sockfd_, buf.c_str(), buf.size());
        if (num != -1)
        {
            left -= num;
        }
        else
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
                return false;
        }
    }

    return true;
}

int TcpStream::writeSome(const std::string &buf)
{
    int num = 0;
    num = ::write(sockfd_, buf.c_str(), buf.size());

    return num;
}

int TcpStream::readALL(char *buf, int len)
{
    return ::recv(sockfd_, buf, len, MSG_WAITALL);
}

int TcpStream::readSome(char *buf, int len)
{
    return ::read(sockfd_, buf, len);
}
