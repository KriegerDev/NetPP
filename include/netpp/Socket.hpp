#ifndef __NETPP_SOCKET_H
#define __NETPP_SOCKET_H

#include <netpp/network.hpp>
#include <netpp/SockAddress.hpp>
#include <netpp/Error.hpp>
#include <functional>
#include <memory>
#include <string>

namespace netpp
{
	class Socket
	{
	public:
		explicit Socket(const SOCK_FAMILY sock_family, const SOCK_TYPE sock_type, const SOCK_PROTO protocol);
		~Socket();
		bool Initialize();
		bool Bind(const SockAddress& bindAddress);

		// UDP Sockets
		bool ReceiveFrom(std::string& buffer);
		bool ReceiveFrom(std::string& buffer, SockAddress& from);
		bool SendTo(const SockAddress& toAddr, const char* buffer);

		using UDPReceiveCallback = std::function<void(const std::string&, const SockAddress&)>;
		bool ReceiveFrom(UDPReceiveCallback callback);

	public:
		inline const Error* getError() const
		{
			return this->m_Error;
		}

		inline SockAddress getBindAddress() const
		{
			return this->m_BindAddress;
		}

		inline unsigned int getId() const
		{
			return this->m_sockId;
		}

		inline bool isBinded() const
		{
			return this->m_binded;
		}

		bool Shutdown(const int HOW);

		bool Close();

	private:
		Error* m_Error;

		netpp_sock_t m_sockfd;
		SockAddress m_BindAddress;

		SOCK_PROTO m_protocol;
		SOCK_FAMILY m_family;
		SOCK_TYPE m_type;

		bool m_initialized;
		bool m_binded;
		unsigned int m_sockId;
	};
}
#endif