#include <unistd.h>
#include <thread>
#include <syslog.h>

#include "../unixenv/daemonize.h"
#include "../unixenv/event.h"
#include "../unixenv/listener_event.h"

int
main()
{
    syslog(LOG_NOTICE, "Starting daemon...");
    std::thread t(task);
    t.join();
}

void task() {
    Event *callbackEvent = new ListenerEvent();
    Daemon daemon(*callbackEvent);
    daemon.run();
}

