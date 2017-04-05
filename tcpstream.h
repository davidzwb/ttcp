#ifndef TCPSTREAM_H
#define TCPSTREAM_H

#include <string>

#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <cerrno>

#include "inetaddress.h"
#include "socket.h"

class TcpStream : public Socket
{
public:
    //int connfd_;
    TcpStream() : Socket() {}
    TcpStream(InetAddress addr, bool isPassive) : Socket(addr, true, isPassive) {}

    bool start();//start the stream
    bool accept(TcpStream& tcpstream);//accept and return a new stream pointer, only usable for passive stream.

    bool writeALL(const std::string& buf);
    int writeSome(const std::string& buf);
    int readALL(char *buf, int len);
    int readSome(char *buf, int len);
};

#endif // TCPSTREAM_H
