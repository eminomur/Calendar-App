#ifndef CREDENTIAL_H
#define CREDENTIAL_H

#include <string>

// This class will be used to store credentials of user
// after log in
// It may also be used to change user's credentials, if needed
class Credential
{
public:
    // This static function extracts values from a string in bson format
    // to set member variables
    static void initialize_credential(std::string new_credential);

    static std::string get_id();
    static std::string get_email();
    static std::string get_email_password();
    static std::string get_firstname();
    static std::string get_lastname();
    static std::string get_username();
    static std::string get_password();

    static void set_id(std::string the_id);
    static void set_email(std::string the_email);
    static void set_email_password(std::string the_email_password);
    static void set_firstname(std::string the_firstname);
    static void set_lastname(std::string the_lastname);
    static void set_username(std::string the_username);
    static void set_password(std::string the_password);
private:
    Credential() = default;
    ~Credential() = default;

    static std::string id;
    static std::string email;
    static std::string email_password;
    static std::string firstname;
    static std::string lastname;
    static std::string username;
    static std::string password;
};

#endif // CREDENTIAL_H
