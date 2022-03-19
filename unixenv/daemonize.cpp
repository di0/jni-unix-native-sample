#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/types.h>

#include <iostream>
#include <string>
#include <fstream>

#include "daemonize.h"

#define DAEMON_NAME "vdaemon"
#define no_exit true

using namespace std;

static int pipe_TERM[2];
static int pipe_HUP[2];

struct sigaction sigaction_hup;
struct sigaction sigaction_term;

void
__signal_oper(int signal_flag)
{
    switch (signum)
    {
        case SIGTERM: /* Stop the daemon. */
            fd = pipe_TERM[1];
            break;
        case SIGHUP: /* Reload the configuration with commands. */
            fd = pipe_HUP[1];
            break;
        default:
            syslog(LOG_WARNING, "Got unexpected signal (number: %d).", signal_flag);
            return;
            break;
    }
}

void
__redirect_file_descriptors()
{
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    int i = open ("/dev/null", O_RDWR);
    dup(i);
}

void
__prepare_signal_handlers()
{
    memset(&sigaction_hup, 0, sizeof(sigaction_hup));
    memset(&sigaction_term, 0, sizeof(sigaction_term));
    sigaction_hup.sa_handler = sig_handler;
    sigaction_term.sa_handler = sig_handler;
}

namespace UnixEnvironment
{
    Daemon::Daemon(Event &event) :
            event(event){}

    pid_t pid;

    void Daemon::run()
    {
        __redirect_file_descriptors();
        __prepare_signal_handlers();
        prepare_log();
        create_process();
        prepare_environment();

        while (no_exit)
        {
            syslog(LOG_NOTICE, "Testing running ...");
            catch_event();
            sleep(60);
        }
    }

    void Daemon::stop() const
    {
        syslog(LOG_NOTICE, "Signal kill received ...");
        closelog();
        if (pid)
            kill(pid, SIGKILL);
    }

    void Daemon::catch_event()
    {
        event.handle_event();
        if (event.exists_event())
        {
            const char *message = event.read_event().c_str();
            syslog(LOG_NOTICE, message);
            event.set_processed(true);
            syslog(LOG_NOTICE, "Processed successfully.");
        }
        else
        {
            syslog(LOG_NOTICE, "No message found");
        }
    }

    void Daemon::create_process()
    {
        pid = fork();
        if (pid < 0)
            throw "Error at create process";

        if (pid > 0)
        {
            char *pid_value = (char *) malloc(10);
            sprintf(pid_value, "pid created: %d", pid);
            syslog(LOG_NOTICE, pid_value);
            free(pid_value);
            exit(EXIT_SUCCESS);
        }
    }

    void Daemon::prepare_log() 
    {
        setlogmask(LOG_UPTO(LOG_NOTICE));
        openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);

        syslog(LOG_INFO, "Daemon launched ...");
    }

    void Daemon::prepare_environment()
    {
        pid_t sid = setsid();
        if (sid < 0)
        {
            throw("Error at set session id.");
        }

        if ((chdir("/")) < 0)
        {
            throw("Error at change directory.");
        }

        umask(0);
    }
}
