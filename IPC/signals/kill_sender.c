#include <stdio.h>
#include <signal.h>

int
main(int argc, char **argv){


    kill(5479, SIGUSR1);
    scanf("\n");
    return 0;
}

/*
Build:
    ps -aux | grep kill_recv
    5479 pts/4    00:00:00 kill_recv
    make

Run log:
    htritai@ubuntu:~/Downloads/IPC$ ./build/IPC/signals/kill_sender
    a
    htritai@ubuntu:~/Downloads/IPC$ ./build/IPC/signals/kill_sender

Terminal 2:
    htritai@ubuntu:~/Downloads/IPC$ ./build/IPC/signals/kill_recv
    Signal 10 recieved
    Signal 10 recieved
*/