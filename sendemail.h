#ifndef SENDEMAIL_H
#define SENDEMAIL_H

#include <string>
#include <Poco/Net/Context.h>

class SendEmail
{
public:
    static std::string get_host();
    static std::uint16_t get_port();

    static void set_host(const std::string& the_host);
    static void set_port(const std::uint16_t& the_host);

    static std::string send();
private:
    SendEmail() = default;

    static std::string host;
    static Poco::UInt16 port;
};

#endif // SENDEMAIL_H
