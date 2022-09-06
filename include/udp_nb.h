#ifndef UDP_NB 
#define UDP_NB

#include <WinSock2.h>
#include <iostream>
//#include <unistd.h>
#pragma once

class UDP_Non_Blocking
{
    private:
        WSADATA data;
        SOCKET soc_udp;
        int result;
        u_long iMode = 1;
        sockaddr_in destination;

    public:
        UDP_Non_Blocking();
        void initialise(uint16_t port);
		uint32_t UDPPacketRecieverFromDeviceToBuffer(unsigned char * buffer, int maxBufferLength);
        ~UDP_Non_Blocking();
};


#endif //UDP_NB