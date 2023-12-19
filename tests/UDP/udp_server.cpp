#include <netpp/Socket.hpp>
#include <netpp/SockAddress.hpp>
#include <iostream>

#define PORT 8080

int main(void)
{
	std::cout << "Initializing udp server...\n";

	netpp::SockAddress addr(PORT, netpp::SOCK_FAMILY_INET);
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

	if(!sock.Bind(addr))
	{
		sock.getError()->Throw();
		return 1;
	}

	std::string buffer;
	std::cout << "Receiving data...\n";
	netpp::SockAddress sender;

	if(!sock.ReceiveFrom(buffer, sender))
	{
		sock.getError()->Throw();
		return 1;
	}

	if(!sender.setup())
	{
		sender.getError()->Throw();
		return 1;
	}

	std::cout << "Buffer: " << buffer << '\n';

	if(!sock.SendTo(sender, "Server has received ur buffer"))
	{
		sock.getError()->Throw();
		return 1;
	}

	sock.Close();
	return 0;
}