#include "stdio.h"
#include "stdlib.h"
#define Nkids 3

void MasterProcess(int *mem) {
  while (1) {
    *mem = 0;
    printf("I am master process, pid = %d, mem = %d, address = 0x%x\n",
           getpid(), *mem, (unsigned int)mem);
    sleep(2);
  }
}

void ChildProcess(int *mem) {
  while (1) {
    *mem = -11;
    printf("I am Child Process, pid = %d, mem = %d, address = 0x%x\n", getpid(),
           *mem, (unsigned)mem);
    sleep(2);
  }
}

int main() {
  int ret = -1, i = 0;
  /* Shared memory between processes*/
  int *mem = (int *)malloc(sizeof(int));
  printf("shared memory created. address = 0x%x\n", (unsigned int)mem);
  *mem = ret;

  for (i = 0; i < Nkids; i++) {
    ret = fork();
    switch (ret) {
    case 0: {
      ChildProcess(mem);
      break;
    }
    default: {
      if (i < Nkids - 1)
        continue;
      MasterProcess(mem);
    }
    }
  } // for ends
  return 0;
}

/*
Problem:
    Not share memory here <___________________________________________>
    Same address ≠ same memory

Solution:
    int *mem = mmap(NULL,
                sizeof(int),
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS,
                -1,
                0);

Explain:
    ret = fork();
    Linux does NOT copy all memory.

    Instead, it does:

    1️⃣ Duplicate page tables
    2️⃣ Mark pages as read-only + COW
    3️⃣ Parent and child now point to the same physical pages
    This is copy-on-write (COW). <------------------ :)) We need to share memory

Memory Layout:
    PID 6917: 0x6d95c2a0 → phys 0xAAA (Parent)
    PID 6918: 0x6d95c2a0 → phys 0xBBB
    PID 6919: 0x6d95c2a0 → phys 0xCCC
    PID 6920: 0x6d95c2a0 → phys 0xDDD

    Your output:

        I am Child Process, pid = 6918, mem = -11, address = 0x6d95c2a0
        I am master process, pid = 6917, mem = 0, address = 0x6d95c2a0

    This proves:

        Parent never sees -11
        Children never see 0
        Each process modifies its own private copy
        If memory were truly shared, values would overwrite each other
continuously.

/*

Build Steps:
    cd ./IPC/Fork
    gcc -o SharedMemFork SharedMemFork.c
    ./SharedMemFork


Build Log:
    SharedMemFork.c: In function ‘MasterProcess’:
    SharedMemFork.c:10:77: warning: implicit declaration of function ‘getpid’
[-Wimplicit-function-declaration] 10 |         printf("I am master process, pid
= %d, mem = %d, address = 0x%x\n", getpid(), *mem, (unsigned int)mem); | ^~~~~~
    SharedMemFork.c:10:93: warning: cast from pointer to integer of different
size [-Wpointer-to-int-cast] 10 |         printf("I am master process, pid = %d,
mem = %d, address = 0x%x\n", getpid(), *mem, (unsigned int)mem); | ^
    SharedMemFork.c:12:5: warning: implicit declaration of function ‘sleep’
[-Wimplicit-function-declaration] 12 |     sleep(2); |     ^~~~~
    SharedMemFork.c: In function ‘ChildProcess’:
    SharedMemFork.c:20:92: warning: cast from pointer to integer of different
size [-Wpointer-to-int-cast] 20 |         printf("I am Child Process, pid = %d,
mem = %d, address = 0x%x\n", getpid(), *mem, (unsigned)mem); | ^
    SharedMemFork.c: In function ‘main’:
    SharedMemFork.c:30:55: warning: cast from pointer to integer of different
size [-Wpointer-to-int-cast] 30 |     printf("shared memory created. address =
0x%x\n", (unsigned int)mem); | ^ SharedMemFork.c:35:15: warning: implicit
declaration of function ‘fork’ [-Wimplicit-function-declaration] 35 | ret =
fork(); |               ^~~~

Run log:
$ ./SharedMemFork
    shared memory created. address = 0x6d95c2a0
    I am Child Process, pid = 6918, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6919, mem = -11, address = 0x6d95c2a0
    I am master process, pid = 6917, mem = 0, address = 0x6d95c2a0
    I am Child Process, pid = 6920, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6918, mem = -11, address = 0x6d95c2a0
    I am master process, pid = 6917, mem = 0, address = 0x6d95c2a0
    I am Child Process, pid = 6919, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6920, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6918, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6919, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6920, mem = -11, address = 0x6d95c2a0
    I am master process, pid = 6917, mem = 0, address = 0x6d95c2a0
    I am Child Process, pid = 6918, mem = -11, address = 0x6d95c2a0
    I am master process, pid = 6917, mem = 0, address = 0x6d95c2a0
    I am Child Process, pid = 6919, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6920, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6918, mem = -11, address = 0x6d95c2a0
    I am master process, pid = 6917, mem = 0, address = 0x6d95c2a0
    I am Child Process, pid = 6919, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6920, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6918, mem = -11, address = 0x6d95c2a0
    I am master process, pid = 6917, mem = 0, address = 0x6d95c2a0
    I am Child Process, pid = 6919, mem = -11, address = 0x6d95c2a0
    I am Child Process, pid = 6920, mem = -11, address = 0x6d95c2a0
    ^C

*/
