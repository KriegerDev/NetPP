#include <netpp/UDPSocket.hpp>
#include <netpp/SockAddress.hpp>
#include <iostream>

#define PORT 8080

int main(void)
{
	netpp::CSockAddress addr(PORT, netpp::SOCK_FAMILY_INET);
	netpp::CUDPSocket sock(netpp::SOCK_FAMILY_INET);
	if (!sock.Initialize())
	{
		sock.GetError()->Throw();
		return 1;
	}

	if(!sock.Bind(addr))
	{
		sock.GetError()->Throw();
		return 1;
	}

	std::string buffer;

	if(!sock.Receive(buffer))
	{
		sock.GetError()->Throw();
		return 1;
	}

	std::cout << "Buffer: " << buffer << '\n';
	return 0;
}