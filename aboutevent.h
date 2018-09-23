#ifndef ABOUTEVENT_H
#define ABOUTEVENT_H

#include <string>

// This class will keep information about the lastly added event
// so that it can be added to database easily

// Note: selected_date member variable is not initialized
class AboutEvent
{
public:
    // This function initializes all the member variables
    // to their initial values
    static void initialize();
    static void initialize(std::string the_event);
    static bool is_initialized();

    static std::string get_selected_date();
    static std::string get_event_name();
    static std::string get_event_info();
    static bool get_is_send_message();
    static std::string get_to();
    static std::string get_subject();
    static std::string get_message();

    static void set_selected_date(std::string the_selected_date);
    static void set_event_name(std::string the_event_name);
    static void set_event_info(std::string the_event_info);
    static void set_is_send_message(bool the_is_send_message);
    static void set_to(std::string the_to);
    static void set_subject(std::string the_subject);
    static void set_message(std::string the_message);
private:
    AboutEvent() = default;
    ~AboutEvent() = default;

    static std::string selected_date;   // This will be used only for modifying and
                                        // deleting selected event

    static std::string event_name;      // Name of the event
    static std::string event_info;      // Additional information about event
    static bool is_send_message;        // Is there a message to be sent
                                        // If this value is false, even to, subject and message are not empty strings,
                                        // nothing will be sent
    static std::string to;              // Recipient of the message
    static std::string subject;         // Subject of message
    static std::string message;         // Message that will be sent
};

#endif // ABOUTEVENT_H
