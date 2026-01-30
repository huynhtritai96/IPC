#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <memory.h>

/* This program shows how mmap() can be used to memory map the text
file present on disk into process's Virtual address space */
static void  breakpoint () {}

typedef struct student_ {

    int roll_no;
    int marks;
    char name[128];
    char city[128];

} student_t;

int 
main(int argc, char *argv[]){

    if(argc < 2){
        printf("File path not mentioned\n");
        exit(0);
    }
   
    const char *filepath = argv[1]; // <- path to file: file_demo2_tai.txt

    /* OPen the file in Read-Write OMode */
    int fd = open(filepath, O_RDWR ); // <-- open the file: Read-Write Mode

    if(fd < 0){
        printf("\n\"%s \" could not open\n",
               filepath);
        exit(1);
    }

    /* Extract the size of the file */
    struct stat statbuf;
    int err = fstat(fd, &statbuf); // <-- get file size to pass to mmap()
    if(err < 0){
        printf("\n\"%s \" could not open\n",
                       filepath);
        exit(2);
    }

    char *ptr = mmap(NULL, /*Let Kernel decide the starting address of mapping in Virtual Memory */
                    statbuf.st_size,  /* Memory size to Map */ // <-- size of file
                    PROT_READ | PROT_WRITE,  /* Map the memory in Read-Write mode, meaning the Virtual Memory can be read 
                                                and written by the process. Note that, this permission must be compatible
                                                with permissions with which the file is open using open () */
                    MAP_SHARED,  /* To see the changes in the file, should be always MAP_SHARED.   */ // <-- changes should be visible to other processes ****
                    fd,  /* FD represents the identifier of the external data source, in this case it is a file */ // <-- file descriptor
                    0);  /* Offset into the text file from which the mapping has to begin, pass zero to map from the beginning of the file */ // <-- offset 0: beginning of file. otherwise data will be written from offset position

    if(ptr == MAP_FAILED){
        printf("Mapping Failed, errorno = %d\n", errno);
        return 1;
    }
    
     close(fd);      /* We will not going to read/write into file using file-handling routines, hence close the fd. mmap can still
                                use this file even if its fd is closed */

    student_t stud = {123, 90, "Abhishek", "Bangalore"};

    memcpy (ptr, &stud, sizeof(stud)); // <-- copy data to mapped memory

    msync(ptr, sizeof(stud), MS_SYNC); // <-- ensure data is written to file ******

    err = munmap(ptr, statbuf.st_size);     /* Destroy the mapping once done */ // <-- unmap the memory
   
    if(err != 0){
        printf("UnMapping Failed\n");
        return 1;
    }
    
    return 0;
}

/*
Build Steps:
    touch file_demo2_tai.txt
    cd ./IPC/NewSHM
    gcc -o mmap_file_write_Demo2 mmap_file_write_Demo2.c
    ./build/mmap_file_write_Demo2 /home/htritai/Downloads/IPC/NewSHM/file_demo2_tai.txt


Build Log:
    None

Run log:

NOTE: *txt need to have data. If empty:
Mapping Failed, errorno = 22


*/