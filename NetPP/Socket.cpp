#include <netpp/Socket.hpp>
#include <netpp/SockAddress.hpp>
#include <netpp/Error.hpp>
#include <cstring>

namespace netpp
{
	unsigned int g_sockCount = 0;

	Socket::Socket(const SOCK_FAMILY sock_family, const SOCK_TYPE sock_type, const SOCK_PROTO protocol)
	{

		this->m_family = sock_family;
		this->m_type = sock_type;
		this->m_protocol = protocol;
		this->m_sockfd = NETPP_INVALID_SOCKET;

		this->m_Error = nullptr;

		this->m_initialized = false;
		this->m_sockId = g_sockCount;
		this->m_binded = false;
		g_sockCount++;
	}

	Socket::~Socket()
	{
		this->Close();
	}

	bool Socket::Initialize()
	{
		if (this->m_initialized)
		{
			std::cout << "Socket already initialized\n";
			return true;
		}

#ifdef NETPP_PLATFORM_WINDOWS
		WSADATA wsaData;
		const int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0)
		{

			this->m_Error = new Error(NETPP_ERROR_SOCKET, errno, "WSA Startup error");
			return false;
		}
#endif

		this->m_sockfd = socket(this->m_family, this->m_type, this->m_protocol);
		if (this->m_sockfd == NETPP_INVALID_SOCKET)
		{
			this->m_Error = new Error(NETPP_ERROR_SOCKET, errno);
			return false;
		}
		this->m_initialized = true;
		return true;
	}

	bool Socket::Bind(const SockAddress& bindAddress)
	{
		if (this->m_sockfd == NETPP_INVALID_SOCKET)
		{
			this->m_Error = new Error(NETPP_ERROR_SOCKET, errno, "Attempt to bind an invalid socket");
			return false;
		}

		if (!bindAddress.IsReady())
		{
			this->m_Error = new Error(NETPP_ERROR_SOCKET, errno, "Attempt to bind socket with an unready address");
			return false;
		}

		sockaddr_in sockAddr = bindAddress.getAddress();
		const int result = bind(this->m_sockfd, reinterpret_cast<const sockaddr*>(&sockAddr), bindAddress.getLen());
		if (result < 0)
		{
			this->m_Error = new Error(NETPP_ERROR_SOCKET, errno);
			return false;
		}

		this->m_BindAddress = bindAddress;
		this->m_binded = true;

		return true;
	}

	// UDP Sockets
	bool Socket::ReceiveFrom(std::string& buffer)
	{
		if (this->m_sockfd == NETPP_INVALID_SOCKET)
		{
			this->m_Error = new Error(NETPP_ERROR_RECEIVE, errno, "Attempted to received data with an invalid socket");
			return false;
		}

		char buff[1036];
		const netpp_ssize_t bytes_received = recvfrom(this->m_sockfd, buff, strlen(buff), 0, NULL, NULL);
		if (bytes_received < 0)
		{
			this->m_Error = new Error(NETPP_ERROR_RECEIVE, errno);
			return false;
		}

		if (bytes_received == 0)
		{
			std::cout << "NetPP Warning:: Socket received 0 bytes\n";
		}

		buffer.assign(std::string(buff));

		return true;
	}

	bool Socket::ReceiveFrom(std::string& buffer, SockAddress& from)
	{
		if (this->m_sockfd == NETPP_INVALID_SOCKET)
		{
			this->m_Error = new Error(NETPP_ERROR_RECEIVE, errno, "Attempted to received data with an invalid socket");
			return false;
		}

		sockaddr_in from_addr_in;
		socklen_t from_len = sizeof(from_addr_in);
		std::memset(&from_addr_in, 0, sizeof from_addr_in);

		char buff[1024];
		const netpp_ssize_t bytes_received = recvfrom(this->m_sockfd, buff, sizeof(buff), 0, reinterpret_cast<sockaddr*>(&from_addr_in), &from_len);
		if (bytes_received < 0)
		{
			
			this->m_Error = new Error(NETPP_ERROR_RECEIVE, errno);
			return false;
		}

		if (bytes_received == 0)
		{
			std::cout << "NetPP Warning:: Socket received 0 bytes\n";
		}

		buffer.assign(std::string(buff));
		SockAddress fromAddress(from_addr_in, from_len);

		if(!fromAddress.setup())
		{
			this->m_Error = new Error(NETPP_ERROR_ADDRESS, errno, "Failed to setup address");
			return false;
		}

		from = fromAddress;
		return true;
	}

	bool Socket::ReceiveFrom(UDPReceiveCallback callback)
	{
		if (this->m_sockfd == NETPP_INVALID_SOCKET)
		{

			this->m_Error = new Error(NETPP_ERROR_RECEIVE, errno, "Attempted to received data with an invalid socket");
			return false;
		}

		sockaddr_in from_addr_in;
		socklen_t from_len = sizeof(from_addr_in);
		std::memset(&from_addr_in, 0, sizeof from_addr_in);

		char buff[1024];
		const netpp_ssize_t bytes_received = recvfrom(this->m_sockfd, buff, sizeof(buff), 0, reinterpret_cast<sockaddr*>(&from_addr_in), &from_len);
		if (bytes_received < 0)
		{
			this->m_Error = new Error(NETPP_ERROR_RECEIVE, errno);
			return false;
		}

		if (bytes_received == 0)
		{
			std::cout << "NetPP Warning:: Socket received 0 bytes\n";
		}

		SockAddress fromAddress(from_addr_in, from_len);
		fromAddress.setup();
		callback(std::string(buff), fromAddress);
		return true;
	}

	bool Socket::SendTo(const SockAddress& toAddr, const char* buffer)
	{
		if (this->m_sockfd == NETPP_INVALID_SOCKET)
		{
			
			this->m_Error = new Error(NETPP_ERROR_RECEIVE, errno, "Attempted to send data with an invalid socket");
			return false;
		}

		if (!toAddr.IsReady())
		{
			
			this->m_Error = new Error(NETPP_ERROR_SOCKET, errno, "Attempt to send data with an unready address");
			return false;
		}

		sockaddr_in sockAddr = toAddr.getAddress();
		const socklen_t len = toAddr.getLen();

		const netpp_ssize_t bytes_sent = sendto(this->m_sockfd, buffer, 1024, 0, reinterpret_cast<const sockaddr*>(&sockAddr), len);
		if (bytes_sent < 0)
		{
			
			this->m_Error = new Error(NETPP_ERROR_SEND, errno);
			return false;
		}

		if (bytes_sent == 0)
		{
			std::cout << "NetPP Warning:: Socket sent 0 bytes\n";
		}

		return true;
	}

	bool Socket::Shutdown(const int HOW)
	{
		if (this->m_sockfd == NETPP_INVALID_SOCKET)
		{
			
			this->m_Error = new Error(NETPP_ERROR_SOCKET, errno, "Attempted to shutdown an invalid socket");
			return false;
		}

		const int result = shutdown(this->m_sockfd, HOW);
		if (result < 0)
		{
			
			this->m_Error = new Error(NETPP_ERROR_SOCKET, errno);
			return false;
		}

		return true;
	}

	bool Socket::Close()
	{
		if (this->m_sockfd == NETPP_INVALID_SOCKET)
		{
			
			this->m_Error = new Error(NETPP_ERROR_SOCKET, errno, "Attempted to close an invalid socket");
			return false;
		}

#ifdef NETPP_PLATFORM_WINDOWS
		closesocket(this->m_sockfd);
		WSACleanup();
#endif
#ifdef NETPP_PLATFORM_LINUX
		close(this->m_sockfd);
#endif

		this->m_sockfd = NETPP_INVALID_SOCKET;
		delete this->m_Error;
		return true;
	}

}
