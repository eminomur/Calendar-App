#include "aboutevent.h"

#include <string>

std::string AboutEvent::selected_date;
std::string AboutEvent::event_name;
std::string AboutEvent::event_info;
bool AboutEvent::is_send_message;
std::string AboutEvent::to;
std::string AboutEvent::subject;
std::string AboutEvent::message;

void AboutEvent::initialize()
{
    event_name.clear();
    event_info.clear();
    is_send_message = false;
    to.clear();
    subject.clear();
    message.clear();
}

void AboutEvent::initialize(std::string the_event)
{
    event_name = the_event.substr(the_event.find("\", \"eventname\" : \"") + 18,
                                  the_event.find("\", \"aboutevent\" : \"") - (the_event.find("\", \"eventname\" : \"") + 18));

    event_info = the_event.substr(the_event.find("\", \"aboutevent\" : \"") + 19,
                                  the_event.find("\", \"sendmessage\" : ") - (the_event.find("\", \"aboutevent\" : \"") + 19));

    if (the_event.find("\", \"sendmessage\" : true") == std::string::npos) {
        is_send_message = false;
    } else {
        is_send_message = true;
    }

    to = the_event.substr(the_event.find(", \"to\" : \"") + 10,
                          the_event.find("\", \"subject\" : \"") - (the_event.find(", \"to\" : \"") + 10));

    subject = the_event.substr(the_event.find("\", \"subject\" : \"") + 16,
                               the_event.find("\", \"message\" : \"") - (the_event.find("\", \"subject\" : \"") + 16));

    message = the_event.substr(the_event.find("\", \"message\" : \"") + 16,
                               the_event.find_last_of("\"") - (the_event.find("\", \"message\" : \"") + 16));
}

bool AboutEvent::is_initialized()
{
    return event_name.empty() &&
            event_info.empty() &&
            !is_send_message &&
            to.empty() &&
            subject.empty() &&
            message.empty();
}

std::string AboutEvent::get_selected_date()
{
    return selected_date;
}

std::string AboutEvent::get_event_name()
{
    return event_name;
}

std::string AboutEvent::get_event_info()
{
    return event_info;
}

bool AboutEvent::get_is_send_message()
{
    return is_send_message;
}

std::string AboutEvent::get_to()
{
    return to;
}

std::string AboutEvent::get_subject()
{
    return subject;
}

std::string AboutEvent::get_message()
{
    return message;
}

void AboutEvent::set_selected_date(std::string the_selected_date)
{
    selected_date = the_selected_date;
}

void AboutEvent::set_event_name(std::string the_event_name)
{
    event_name = the_event_name;
}

void AboutEvent::set_event_info(std::string the_event_info)
{
    event_info = the_event_info;
}

void AboutEvent::set_is_send_message(bool the_is_send_message)
{
    is_send_message = the_is_send_message;
}

void AboutEvent::set_to(std::string the_to)
{
    to = the_to;
}

void AboutEvent::set_subject(std::string the_subject)
{
    subject = the_subject;
}

void AboutEvent::set_message(std::string the_message)
{
    message = the_message;
}
