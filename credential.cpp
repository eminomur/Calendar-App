#include "credential.h"
#include <string>
#include <cstring>

std::string Credential::id;
std::string Credential::email;
std::string Credential::email_password;
std::string Credential::firstname;
std::string Credential::lastname;
std::string Credential::username;
std::string Credential::password;

void Credential::initialize_credential(std::string new_credential)
{
    // This way is not reliable, program can fail easily
    // so if there is a better way, inform me
    id = new_credential.substr(new_credential.find("\"$oid\" : \"") + 10, 24);

    email = new_credential.substr(new_credential.find("\"email\" : \"") + 11,
                                  new_credential.find("\"emailpassword\" : ") - (new_credential.find("\"email\" : \"") + 14));

    email_password = new_credential.substr(new_credential.find("\", \"emailpassword\" : \"") + 22,
                                           new_credential.find("\", \"firstname\" : ") - (new_credential.find("\", \"emailpassword\" : \"") + 22));

    firstname = new_credential.substr(new_credential.find("\"firstname\" : ") + 15,
                                      new_credential.find("\", \"lastname\" : \"") - (new_credential.find("\"firstname\" : \"") + 15));

    lastname = new_credential.substr(new_credential.find("\"lastname\" : \"") + 14,
                                     new_credential.find("\", \"username\" : \"") - (new_credential.find("\"lastname\" : \"") + 14));

    username = new_credential.substr(new_credential.find("\", \"username\" : \"")  + 17,
                                     new_credential.find("\", \"password\" : \"") - (new_credential.find("\", \"username\" : \"") + 17));

    password = new_credential.substr(new_credential.find("\", \"password\" : \"") + 17,
                                     new_credential.find_last_of("\"") - (new_credential.find("\", \"password\" : \"") + 17));
}

std::string Credential::get_id()
{
    return id;
}

std::string Credential::get_email()
{
    return email;
}

std::string Credential::get_email_password()
{
    return email_password;
}

std::string Credential::get_firstname()
{
    return firstname;
}

std::string Credential::get_lastname()
{
    return lastname;
}

std::string Credential::get_username()
{
    return username;
}

std::string Credential::get_password()
{
    return password;
}

void Credential::set_id(std::string the_id)
{
    id = the_id;
}

void Credential::set_email(std::string the_email)
{
    email = the_email;
}

void Credential::set_email_password(std::string the_email_password)
{
    email_password = the_email_password;
}

void Credential::set_firstname(std::string the_firstname)
{
    firstname = the_firstname;
}

void Credential::set_lastname(std::string the_lastname)
{
    lastname = the_lastname;
}

void Credential::set_username(std::string the_username)
{
    username = the_username;
}

void Credential::set_password(std::string the_password)
{
    password = the_password;
}
