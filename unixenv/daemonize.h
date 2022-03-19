#ifndef DAEMONIZE__
#define DAEMONIZE__

#include "event.h"

namespace UnixEnvironment
{
    class Daemon
    {
    public:
        Daemon(Event & event);
        void run();
        void stop() const;
    private:
        void prepare_log();
        void create_process();
        void prepare_environment();
        void catch_event();

        Event & event;
    };
}

#endif // END DAEMONIZE__
