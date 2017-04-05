#include <iostream>

#include "../inetaddress.h"
#include "../tcpstream.h"

int main(int argc, char *argv[])
{
    InetAddress addr = InetAddress("127.0.0.1", 27777);
    TcpStream tcpstream = TcpStream(addr, false); //false indicating client, which is active
    if(!tcpstream.start())
    {
        std::cout << "client start failed." << std::endl;
        return 0;
    }

    tcpstream.writeALL(std::string("Hello World!"));

    return 0;
}
