# Purpose

Experimental System-V semantics Daemoen implementation, receiving signals
from native from java code.

# How compile it

javac -d bin/ IPConfig.java

# Generate header

javah -cp .:bin/ IPConfig (ou javac -h)

# How compile the library dynamically

```bash
g++ -shared -std=c++11 -fPIC -I/opt/jdk1.8.0_151/include/ \
   -I/opt/jdk1.8.0_151/include/linux utilities/ipconfig.cpp \
   -o lib/libunixenvironment.so unixenv/daemonize.o unixenv/listener_event.o
```

# How run

```bash
java -cp .:bin -Djava.library.path=lib/ UnixUtilities
```
