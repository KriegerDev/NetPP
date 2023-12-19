#ifndef __NETPP_SOCKADDRESS_H
#define __NETPP_SOCKADDRESS_H
#include <netpp/network.hpp>
#include <netpp/Error.hpp>
#include <type_traits>
#include <iostream>
#include <stdexcept>
#include <sstream>

namespace netpp
{
    class SockAddress
    {
    public:
        SockAddress(const std::string &host, const unsigned short port, SOCK_FAMILY family);
        SockAddress(const unsigned short port, SOCK_FAMILY family);
        SockAddress(const sockaddr_in &sockaddr, const socklen_t &len);
        SockAddress();

        bool setup();


        inline SOCK_FAMILY getFamily() const
        {
            return this->m_family;
        }

        inline sockaddr_in getAddress() const
        {
            return this->m_sockaddr_in;
        }

        inline int getLen() const
        {
            return this->m_socklen;
        }

        inline bool IsReady() const
        {
            return this->m_setup;
        }

        inline const Error *getError() const
        {
            return this->m_Error;
        }

        inline std::string str() const
        {
            std::stringstream oss;
            oss << this->m_host << ":" << this->m_port;
            return std::string(oss.str());
        }

        
    private:
        enum SETUP_METHOD
        {
            SETUP_METHOD_DEFAULT = 0,
            SETUP_METHOD_INADDR_ANY = 1,
            SETUP_METHOD_CUSTOM_ADDR_IN = 2
        };
        SETUP_METHOD m_method;

        Error* m_Error;
        bool m_setup;

        sockaddr_in m_sockaddr_in;
        SOCK_FAMILY m_family;
        socklen_t m_socklen;

        std::string m_host;
        unsigned short m_port;
    };
}
#endif