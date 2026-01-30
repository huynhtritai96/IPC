#include "stdio.h"
#include "stdlib.h"
#define Nkids 3

void MasterProcess() {
  while (1) {
    printf("I am master process, pid = %d\n", getpid());
    sleep(2);
  }
}

void ChildProcess() {
  while (1) {
    printf("I am Child Process, pid = %d\n", getpid());
    sleep(2);
  }
}

int main() {
  int ret = -1, i = 0;
  printf("parent process pid = %d\n", getpid());
  for (i = 0; i < Nkids; i++) {
    ret = fork();
    switch (ret) {
    case 0: {
      printf("Forking process %d\n", i);
      ChildProcess();
      break;
    }
    default: {
      printf("inside default with i = %d\n", i);
      if (i < Nkids - 1)
        continue;
      MasterProcess();
    }
    }
  } // for ends
  return 0;
}

/*

Build Steps:
    cd ./IPC/Fork
    gcc -o NChildren NChildren.c
    ./NChildren


Build Log:
    NChildren.c: In function ‘MasterProcess’:
    NChildren.c:9:51: warning: implicit declaration of function ‘getpid’
[-Wimplicit-function-declaration] 9 |         printf("I am master process, pid =
%d\n", getpid()); |                                                   ^~~~~~
    NChildren.c:10:9: warning: implicit declaration of function ‘sleep’
[-Wimplicit-function-declaration] 10 |         sleep(2); |         ^~~~~
    NChildren.c: In function ‘main’:
    NChildren.c:29:15: warning: implicit declaration of function ‘fork’
[-Wimplicit-function-declaration] 29 |         ret = fork(); | ^~~~

Run log:
$ ./NChildren
    parent process pid = 6408
    inside default with i = 0
    inside default with i = 1
    Forking process 0
    I am Child Process, pid = 6409
    inside default with i = 2
    I am master process, pid = 6408
    Forking process 1
    I am Child Process, pid = 6410
    Forking process 2
    I am Child Process, pid = 6411
    I am Child Process, pid = 6409
    I am Child Process, pid = 6410
    I am master process, pid = 6408
    I am Child Process, pid = 6411
    I am Child Process, pid = 6410
    I am Child Process, pid = 6409
    I am master process, pid = 6408
    I am Child Process, pid = 6411
    I am Child Process, pid = 6410
    I am Child Process, pid = 6409
    I am master process, pid = 6408
    I am Child Process, pid = 6411
    I am Child Process, pid = 6410
    I am master process, pid = 6408
    I am Child Process, pid = 6411
    I am Child Process, pid = 6409
    I am master process, pid = 6408
    I am Child Process, pid = 6409
    I am Child Process, pid = 6411
    I am Child Process, pid = 6410
    I am master process, pid = 6408
    I am Child Process, pid = 6411
    I am Child Process, pid = 6410
    I am Child Process, pid = 6409
    I am master process, pid = 6408
    I am Child Process, pid = 6411
    I am Child Process, pid = 6410
    I am Child Process, pid = 6409
    I am master process, pid = 6408
    I am Child Process, pid = 6411
    I am Child Process, pid = 6410
    I am Child Process, pid = 6409
    ^C

*/