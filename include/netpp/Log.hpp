#ifndef __NETPP_LOG_H
#define __NETPP_LOG_H
#include <string>
#include <memory>
#include <iostream>
#include <sstream>

namespace netpp
{
	namespace internals
	{
		class Log
		{
		public:
			template <typename... Args>
			static std::string formatString(const std::string& format, Args... args) {
				std::ostringstream stream;
				size_t size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
				std::unique_ptr<char[]> buffer(new char[size]);
				std::snprintf(buffer.get(), size, format.c_str(), args...);
				return std::string(buffer.get(), buffer.get() + size - 1);
			}

			static void Println(const char* str)
			{
				std::cout << str << '\n';
			}

			static void Error(const char* str)
			{
				Println(formatString("NETPP Error:: %s", str).c_str());
			}

			static void Warning(const char* str)
			{
				Println(formatString("NETPP Warning:: %s", str).c_str());
			}

			static void Debug(const char* str)
			{
#if __NETPP_DEBUG_OPT
				Println(formatString("NETPP Debug:: %s", str).c_str());
#endif
			}
		};
	}
}
#endif