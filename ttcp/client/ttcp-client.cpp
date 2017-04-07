#include <iostream>

#include "../../inetaddress.h"
#include "../../tcpstream.h"

#define MSGLENGTH 7
#define MSGCOUNT 100

int main(int argc, char *argv[]) {

    //create server addr
    InetAddress addr = InetAddress("127.0.0.1", 27777);
    //create tcp stream connecting server
    TcpStream tcpstream = TcpStream(addr);

    if (!tcpstream.start()) {
        std::cout << "starting client failed." << std::endl;
    }

    //first send header
    struct ttcp_header {
        int32_t length;
        int32_t count;
    };

    ttcp_header header;

    if (argc < 3) {
        header.length = MSGLENGTH;
        header.count = MSGCOUNT;
    }
    else {
        header.length = atoi(argv[1]);
        header.count = atoi(argv[2]);
    }


    tcpstream.writeALL(reinterpret_cast<char *>(&header), sizeof(header));

    //receive ack of length
    int32_t ack;
    tcpstream.readALL(reinterpret_cast<char *>(&ack), sizeof(ack));

    //FIXME byte order
    if (ack != header.length) {
        std::cout << "received wrong length." << std::endl;
        return 0;
    }

    //send message
    std::string data(header.length, 'x');
    int32_t len = 0;
    for (int i = 0; i < header.count; ++i) {
        tcpstream.writeALL(data.c_str(), data.size());

        tcpstream.readALL(reinterpret_cast<char *>(&len), sizeof(len));

        if (len != header.length)
            return 0;
    }

    //receive ack of number
    int32_t count = 0;
    tcpstream.readALL(reinterpret_cast<char *>(&count), sizeof(count));

    if (count != header.count) {
        std::cout << "received wrong count." << std::endl;
    }

    std::cout << "sent " << header.count << " messages." << std::endl;

    //tcpstream.close();

    return 0;
}


