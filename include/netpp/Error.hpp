#ifndef __NETPP_ERROR_H
#define __NETPP_ERROR_H
#include <string>
#include <netpp/Log.hpp>

namespace netpp
{
	enum NETPP_ERROR
	{
		NETPP_ERROR_NONE = 0,
		NETPP_ERROR_UNKNOWN = 1,
		NETPP_ERROR_SOCKET = 2,
		NETPP_ERROR_LISTEN,
		NETPP_ERROR_SEND,
		NETPP_ERROR_RECEIVE,
		NETPP_ERROR_ADDRESS
	};


	class Error
	{
	public:
		Error(NETPP_ERROR netpp_error, const int npp_errno, const char* message);

		Error(NETPP_ERROR netpp_error, const int npp_errno);

		inline int getErrno() const
		{
			return this->m_errno;
		}

		inline NETPP_ERROR getCode() const
		{
			return this->m_code;
		}

		inline std::string getMessage() const
		{
			return this->m_message;
		}

		const char* strErrno(int err);

		void Throw() const;

	private:
		int m_errno;
		NETPP_ERROR m_code;
		std::string m_message;
	};
}
#endif