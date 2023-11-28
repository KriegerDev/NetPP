#include <netpp/UDPSocket.hpp>
#include <netpp/SockAddress.hpp>
#include <iostream>

#define PORT 8080

int main(void)
{
	netpp::CSockAddress addr("127.0.0.1", PORT, netpp::SOCK_FAMILY_INET);
	netpp::CUDPSocket sock(netpp::SOCK_FAMILY_INET);
	if (!sock.Initialize())
	{
		sock.GetError()->Throw();
		return 1;
	}

	std::string buffer = "Hello from client";

	if(!sock.SendTo(addr, buffer.c_str()))
	{
		sock.GetError()->Throw();
		return 1;
	}

	std::cout << "Sended Buffer: " << buffer << '\n';
	return 0;
}