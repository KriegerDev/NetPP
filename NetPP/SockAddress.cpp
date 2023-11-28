#include <cstring>
#include <netpp/SockAddress.hpp>
#include <string>
#include <netpp/Error.hpp>

namespace netpp
{
	SockAddress::SockAddress(const std::string& host, const unsigned short port, SOCK_FAMILY family) :
		m_method(SETUP_METHOD_DEFAULT),
		m_host(host),
		m_port(port),
		m_family(family),
		m_setup(false)
	{
	}

	SockAddress::SockAddress(const unsigned short port, SOCK_FAMILY family) :
		m_method(SETUP_METHOD_INADDR_ANY),
		m_family(family),
		m_port(port),
		m_host("0.0.0.0"),
		m_setup(false)
	{
	}

	SockAddress::SockAddress(const sockaddr_in& sockaddr, const socklen_t& len) :
		m_method(SETUP_METHOD_CUSTOM_ADDR_IN),
		m_sockaddr_in(sockaddr),
		m_socklen(len),
		m_setup(false)
	{
	}

	SockAddress::SockAddress() :
		m_method(SETUP_METHOD_CUSTOM_ADDR_IN)
	{
	}

	bool SockAddress::setup()
	{
		if (this->m_method == SETUP_METHOD_DEFAULT)
		{
			memset(&this->m_sockaddr_in, 0, sizeof this->m_sockaddr_in);
			this->m_sockaddr_in.sin_family = this->m_family;
			this->m_sockaddr_in.sin_port = htons(this->m_port);
			const int result = inet_pton(this->m_family, this->m_host.c_str(), &this->m_sockaddr_in.sin_addr);
			if (result != 1)
			{
				delete this->m_Error;
				this->m_Error = new Error(NETPP_ERROR_ADDRESS, errno);
				return false;
			}
		}
		else if (this->m_method == SETUP_METHOD_INADDR_ANY)
		{
			memset(&this->m_sockaddr_in, 0, sizeof this->m_sockaddr_in);
			this->m_sockaddr_in.sin_family = this->m_family;
			this->m_sockaddr_in.sin_port = htons(this->m_port);
			this->m_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
		}
		else
		{
			char buffer[24];
			if (inet_ntop(this->m_sockaddr_in.sin_family, &this->m_sockaddr_in.sin_addr, buffer, sizeof buffer) == nullptr)
			{
				delete this->m_Error;
				this->m_Error = new Error(NETPP_ERROR_ADDRESS, errno, "Cannot convert ip address");
				return false;
			}
			this->m_host = buffer;
			this->m_port = this->m_sockaddr_in.sin_port;
		}

		this->m_socklen = sizeof(this->m_sockaddr_in);
		this->m_setup = true;
		return true;
	}
}