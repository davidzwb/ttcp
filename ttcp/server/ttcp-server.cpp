#include <iostream>
#include <memory>

#include <sys/time.h>

#include "../../inetaddress.h"
#include "../../tcpstream.h"

double now()
{
  struct timeval tv = { 0, 0 };
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main() {


    //create server addr
    InetAddress addr = InetAddress("", 27777);
    //create tcp stream connecting server
    TcpStream tcpstream = TcpStream(addr, true);

    if (!tcpstream.start()) {
        std::cout << "starting server failed." << std::endl;
        return 0;
    }

    while (1) {
        TcpStream connstream = TcpStream();

        if (!tcpstream.accept(connstream)) {
            std::cout << "accept failed." << std::endl;
            return 0;
        }

        //first receive header
        struct ttcp_header {
            int32_t length;
            int32_t count;
        };

        ttcp_header header;

        connstream.readALL(reinterpret_cast<char *>(&header), sizeof(header));

        int32_t length = header.length;
        int32_t count = header.count;

        //send ack of length
        connstream.writeALL(reinterpret_cast<char *>(&length), sizeof(length));

        // record start time
        double start = now();
        double total_mb = 1.0 * length * count / 1024 / 1024;
        printf("%.3f MiB in total\n", total_mb);

        //RAII! wrap up the char array with container, free it automatically
        std::unique_ptr<char[]> buf(new char[length]);

        //receive message
        int i = 0;
        for ( ; i < count; ++i) {
            if (connstream.readALL(buf.get(), length) <= 0) {
                std::cout << "server: abandoning receiving data." << std::endl;

                return 0;
            }

            //std::cout << buf << std::endl;
            ::memset(buf.get(), 0, length);

            //acknowledge data just received.
            connstream.writeALL(reinterpret_cast<char *>(&length), sizeof(length));
        }

        //record end time.
        double elapsed = now() - start;
        printf("%.3f seconds\n%.3f MiB/s\n", elapsed, total_mb / elapsed);

        if (i != count) {
            std::cout << "server received wrong count: " << i << std::endl;
            return 0;
        }

        //send ack of number
        connstream.writeALL(reinterpret_cast<char *>(&i), sizeof(i));

        std::cout << "received " << i << " messages." << std::endl;
    }

    return 0;
}


