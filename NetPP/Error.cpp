#include <netpp/Error.hpp>

#include <cerrno>
#include <cstring>
#include <iostream>

namespace netpp
{

	Error::Error(NETPP_ERROR netpp_error, const int npp_errno, const char* desc) :
		m_errno(npp_errno),
		m_code(netpp_error),
		m_message(desc)
	{
	}

	Error::Error(NETPP_ERROR netpp_error, const int npp_errno) :
		m_errno(npp_errno),
		m_code(netpp_error)
	{
		this->m_message = strErrno(npp_errno);
	}

	const char* Error::strErrno(int err)
	{
		char buffer[1028];
#ifdef NETPP_PLATFORM_WINDOWS
		
		strerror_s(buffer, sizeof(buffer), errno);
#else
		strerror_r(errno, buffer, sizeof(buffer));
#endif
		return buffer;
	}

	void Error::Throw() const
	{
		const int err = this->m_code;
		std::cout << "errno " << this->m_errno << " || netpp code " << err << " => " << this->m_message << '\n';
	}
}
