#include "sendemail.h"
#include <string>
#include "credential.h"
#include "aboutevent.h"
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/NetException.h>
#include <Poco/AutoPtr.h>

#include <iostream>

std::string SendEmail::host = "smtp.gmail.com";
Poco::UInt16 SendEmail::port = 587;

std::string SendEmail::get_host()
{
    return host;
}

std::uint16_t SendEmail::get_port()
{
    return port;
}

void SendEmail::set_host(const std::string& the_host)
{
    host = the_host;
}

void SendEmail::set_port(const std::uint16_t& the_port)
{
    port = the_port;
}

std::string SendEmail::send()
{
    Poco::Net::MailMessage message;

    message.setSender(Credential::get_email());
    message.addRecipient(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, AboutEvent::get_to()));
    message.setSubject(Poco::Net::MailMessage::encodeWord(AboutEvent::get_subject(), "UTF-8"));
    message.setContentType("text/plain; charset=UTF-8");
    message.setContent(AboutEvent::get_message(), Poco::Net::MailMessage::ENCODING_8BIT);

    try {
        Poco::Net::initializeSSL();
        Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> ptr_handler = new Poco::Net::AcceptCertificateHandler(false);
        Poco::Net::Context::Ptr ptr_context = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_RELAXED,
                                                                     9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
        Poco::Net::SSLManager::instance().initializeClient(nullptr, ptr_handler, ptr_context);

        Poco::Net::SecureSMTPClientSession session("smtp.gmail.com", 587);

        try {
            session.login();

            if (session.startTLS()) {
                session.login(Poco::Net::SMTPClientSession::AUTH_LOGIN, Credential::get_email(), Credential::get_email_password());
                session.sendMessage(message);
            }

            session.close();
            Poco::Net::uninitializeSSL();
        } catch (Poco::Net::SMTPException& e) {
            session.close();
            Poco::Net::uninitializeSSL();
            return e.what();
        }
    } catch (Poco::Net::NetException& e) {
        return e.what();
    }

    return "";
}
