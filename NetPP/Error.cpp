#include <netpp/Error.hpp>
#include <netpp/Log.hpp>

namespace netpp
{

	Error::Error(NETPP_ERROR netpp_error, const int npp_errno, const char* desc) :
		m_code(netpp_error),
		m_errno(npp_errno),
		m_message(desc)
	{
	}

	Error::Error(NETPP_ERROR netpp_error, const int npp_errno) :
		m_code(netpp_error),
		m_errno(npp_errno)
	{

		this->m_message = strErrno(npp_errno);
	}

	const char* Error::strErrno(int err)
	{
#if NETPP_PLATFORM_WINDOWS
		char buffer[256];
		strerror_s(buffer, sizeof(buffer), errno);
		const char *p = buffer;
		return p;
#else
		return hstrerror(err);
#endif
	}

	void Error::Throw() const
	{
		const int err = this->m_code;
		const std::string str = internals::Log::formatString("errno %d || netpp code %d => %s", this->m_errno, err, this->m_message);
		internals::Log::Error(str.c_str());
	}
}
