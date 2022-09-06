#include "udp_nb.h"

UDP_Non_Blocking::UDP_Non_Blocking()
{

	result = WSAStartup(MAKEWORD(2, 2), &(this->data));
	if (result != NO_ERROR)
		std::cout << "Error at WSAStartup()\n";

	soc_udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (soc_udp == INVALID_SOCKET)
	{
		std::cout << "Socket Init Failed :" << WSAGetLastError() << std::endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	// If iMode = 0, blocking is enabled; 
	// If iMode != 0, non-blocking mode is enabled.
	result = ioctlsocket(soc_udp, FIONBIO, &iMode);
	if (result != NO_ERROR)
		std::cout << "ioctlsocket failed with error:" << result << std::endl;
}

void UDP_Non_Blocking::initialise(uint16_t port)
{
	destination.sin_family = AF_INET;
	destination.sin_addr.s_addr = htonl(INADDR_ANY);
	destination.sin_port = htons(port);

	int ret = bind(soc_udp, (SOCKADDR *)(&destination), sizeof(destination));
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Bind failed");

	connect(soc_udp, (struct sockaddr *)&destination, sizeof(destination));

	DWORD dw =(500);// (timeout_ms);        // this is in miliseconds
	setsockopt(soc_udp, SOL_SOCKET, SO_RCVTIMEO, (char *)&dw, sizeof(dw));
}

uint32_t UDP_Non_Blocking::UDPPacketRecieverFromDeviceToBuffer(unsigned char * buffer, int maxBufferLength)
{
	int size = sizeof(destination);
	//int result = recv(soc_udp, (char *)buffer, maxBufferLength, 0); //if needed
	int result = recvfrom(soc_udp, (char *)buffer, maxBufferLength, 0, (struct sockaddr*)&destination, &size);
	if (result < 0)
	{
		int Error=WSAGetLastError();
		if(Error==WSAEWOULDBLOCK)
		{
			return 0;
		}
		else
		{
			std::cout << "Recvfrom WSA Error :" << WSAGetLastError() << std::endl;
		}
		
	}
	else
	{
		for (int i = 0; i < result; i++)
			printf("%c", *(buffer + i));
		std::cout << std::endl;
	}
	//Sleep(3000); mili seconds 
	return result;
}

UDP_Non_Blocking::~UDP_Non_Blocking()
{
	closesocket(soc_udp);
	WSACleanup();
}