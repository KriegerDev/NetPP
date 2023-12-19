#include <netpp/Socket.hpp>
#include <netpp/SockAddress.hpp>
#include <iostream>

#define PORT 8080

int main(void)
{
	netpp::SockAddress addr("127.0.0.1", PORT, netpp::SOCK_FAMILY_INET);
	if(!addr.setup())
	{
		addr.getError()->Throw();
		return 1;
	}

	netpp::Socket sock(netpp::SOCK_FAMILY_INET, netpp::SOCK_TYPE_DGRAM, netpp::SOCK_PROTO_UDP);

	if (!sock.Initialize())
	{
		sock.getError()->Throw();
		return 1;
	}

	const char* buffer = "Hello from client";

	if(!sock.SendTo(addr, buffer))
	{
		sock.getError()->Throw();
		return 1;
	}

	std::cout << "Sended Buffer: " << buffer << '\n';

	const bool result = sock.ReceiveFrom([](const std::string& buffer, const netpp::SockAddress& address)
	{
		std::cout << "Received from: " << address.str() << '\n';
		std::cout << "Content: " << buffer << '\n';
	});

	sock.Close();

	return 0;
}