#include "listener_event.h"

namespace UnixEnvironment
{
    void ListenerEvent::add_event(const std::string &new_event)
    {
        m_new_event = new_event;
    }

    std::string ListenerEvent::read_event() const
    {
        return "Just test";
    }

    bool ListenerEvent::exists_event() const
    {
        return true;
    }

    void ListenerEvent::handle_event() const
    {
    }

    void ListenerEvent::set_processed(bool is_processed)
    {
        m_is_processed = is_processed;
    }

    bool ListenerEvent::is_processed() const
    {
        return m_is_processed;
    }
}
