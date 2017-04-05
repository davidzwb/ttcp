#include <iostream>

#include <cstring>

#include "../inetaddress.h"
#include "../tcpstream.h"

int main(int argc, char *argv[])
{
    InetAddress addr = InetAddress("", 27777);
    TcpStream tcpstream = TcpStream(addr, true);

    if (!tcpstream.start())
    {
        std::cout << "server start failed." << std::endl;
        return 0;
    }

    char readline[128];

    while (1)
    {
        ::memset(readline, 0, 128);

        TcpStream connstream = TcpStream();
        if (!tcpstream.accept(connstream))
            return 0;

        int num = connstream.readSome(readline, 128);
        readline[num] = '\0';

        std::cout << readline << std::endl;
    }

    return 0;
}
