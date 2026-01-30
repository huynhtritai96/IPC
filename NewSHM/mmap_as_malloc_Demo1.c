#include <stdio.h>
#include <sys/mman.h>
#include <errno.h> // <-- for errno

/* mmap() has multiple purpose, this is the example where program simply
do dynamic memory allocation using mmap() instead of malloc() call. There
is no external data source or memory mapping involved. This example simply
shows how mmap() can be used as substitution for malloc()/free().
*/

#if 0
void *
mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);

int munmap(void *addr, size_t length);
#endif

int 
main(int argc, char **argv) {

int N=5;
int *ptr = mmap ( NULL,     /*   Let the OS choose the starting virtual address of the memory, just
                                like you do not have a control as to what address malloc() will return */ // <-- should be NULL
                            N*sizeof(int),      /* Size of memory in bytes being requested for allocation */ 
                             PROT_READ |  /* Memory is Readable */ // <-- Similar to Publisher and Subscriber example
                             PROT_WRITE, /* Memory is Writable */
                             MAP_PRIVATE |  /* This memory is not sharable with any other process, use MAP_SHARED instead */ // <-- Similar to malloc() because another process cannot use it
                             MAP_ANONYMOUS,   /* This memory is not mapped to extern data source, but only RAM by default */ // Not use External Data Source, only RAM 
                             0,     /* FD 0, since no external data source is specified */ // <-- should be 0 because no extern data source 
                             0 );  /* offset value as zero, since no extern data source is specified */ // <-- should be 0 because no extern data source 

if(ptr == MAP_FAILED){ // <-- check for error
    printf("Mapping Failed, errno = %d\n", errno); // <-- print error number, reason memory mapping failed
    return 1;
}

for(int i=0; i<N; i++)
    ptr[i] = i*10;

for(int i=0; i<N; i++)
    printf("[%d] ",ptr[i]);

printf("\n");
int err = munmap(ptr, 10*sizeof(int)); // <-- free the memory allocated using mmap(). must pass the same size as allocated and starting address
if(err != 0){
    printf("UnMapping Failed\n");
    return 1;
}

return 0;
}

/*

Build Steps:
    cd ./IPC/NewSHM
    gcc -o mmap_as_malloc_Demo1 mmap_as_malloc_Demo1.c
    ./mmap_as_malloc_Demo1


Build Log:
    None

Run log:
$ ./mmap_as_malloc_Demo1
    [0] [10] [20] [30] [40]
*/