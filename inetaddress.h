#ifndef INETADDRESS_H
#define INETADDRESS_H

#include<string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// class represents an IPv4 socket Address
class InetAddress {
private:
    sockaddr_in saddr; //s_addr
    int family;//ai_family

public:
    InetAddress() = default;
    InetAddress(std::string ip, int port);

    sockaddr *getSockaddrP();
    int getFamily() const;
};

#endif // INETADDRESS_H
