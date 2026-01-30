#include "stdio.h"
#include "stdlib.h"

void MasterProcess() {
  while (1) {
    printf("I am master process, pid = %d\n", getpid());
    sleep(1);
  }
}

void ChildProcess() {
  while (1) {
    printf("I am Child Process, pid = %d\n", getpid());
    sleep(1);
  }
}

int main() {
  printf("parent process pid = %d\n", getpid());
  switch (fork()) {
  case 0: {
    ChildProcess();
    break;
  }
  default:
    MasterProcess();
  }
  return 0;
}

/*

Build Steps:
    cd ./IPC/Fork
    gcc -o ForkDemo ForkDemo.c
    ./ForkDemo


Build Log:
    ForkDemo.c: In function ‘MasterProcess’:
    ForkDemo.c:8:51: warning: implicit declaration of function ‘getpid’
[-Wimplicit-function-declaration] 8 |         printf("I am master process, pid =
%d\n", getpid()); |                                                   ^~~~~~
    ForkDemo.c:9:9: warning: implicit declaration of function ‘sleep’
[-Wimplicit-function-declaration] 9 |         sleep(1); |         ^~~~~
    ForkDemo.c: In function ‘main’:
    ForkDemo.c:25:13: warning: implicit declaration of function ‘fork’
[-Wimplicit-function-declaration] 25 |     switch (fork()) |             ^~~~

Run log:
$ ./ForkDemo
    parent process pid = 6000
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    I am Child Process, pid = 6001
    I am master process, pid = 6000
    I am master process, pid = 6000
    I am Child Process, pid = 6001
    ^C

*/
