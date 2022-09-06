#include <udp_nb.h>

int main()
{
    char buffer[100];
    UDP_Non_Blocking client;
    client.initialise(8080);
    client.UDPPacketRecieverFromDeviceToBuffer((unsigned char *)buffer,sizeof(buffer));

    return 0;
}