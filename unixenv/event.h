#ifndef EVENT__
#define EVENT__

#include <iostream>

namespace UnixEnvironment
{
    class Event
    {
    public:
        virtual void handle_event() const = 0;
        virtual std::string read_event() const = 0;
        virtual bool exists_event() const = 0;
        virtual void set_processed(bool) = 0;
        virtual bool is_processed() const = 0;
    };
}

#endif //EVENT__
