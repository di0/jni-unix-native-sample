#include <iostream>

#include "../include/UnixUtilities.h"

using namespace std;
using namespace UnixEnvironment;

void task();
Event* callbackEvent = new ListenerEvent();

JNIEXPORT jstring JNICALL Java_UnixUtilities_ipconfig
        (JNIEnv* env, jobject obj)
{
    string ip("192.168.0.5/24");
    return env->NewStringUTF(ip.c_str());
}

void task() {
    Daemon daemon(*callbackEvent);
    daemon.run();
}
