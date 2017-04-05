#include "inetaddress.h"


InetAddress::InetAddress(std::string ip, int port) {

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    //FIXME in case ip is a web address, getnamebyhost

    if (!ip.empty())
        inet_pton(AF_INET, ip.c_str(),  static_cast<void *>(&saddr.sin_addr));
    else
        saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    family = AF_INET;

}

int InetAddress::getFamily() const
{
    return family;
}

sockaddr *InetAddress::getSockaddrP()
{
    return reinterpret_cast<sockaddr *>(&saddr);
}
