#ifndef LISTENEREVENT__
#define LISTENEREVENT__

#include <iostream>
#include "event.h"

namespace UnixEnvironment
{
    class ListenerEvent : public Event
    {
    public:
        void add_event(const std::string &new_event);
        void handle_event() const;
        std::string read_event() const;
        bool exists_event() const;
        void set_processed(bool is_processed);
        bool is_processed() const;
    private:
        bool m_is_processed;
        bool m_exists_event;
        std::string m_new_event;
    };
}

#endif // LISTENEREVENT__
