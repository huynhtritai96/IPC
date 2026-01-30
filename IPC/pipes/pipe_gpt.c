#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024

static void die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  int fd[2];
  ssize_t n;
  char buf[BUF_SIZE];

  const char *data = (argc > 1) ? argv[1] : "default pipe data";

  /* 1. Create pipe */
  if (pipe(fd) == -1)
    die("pipe");

  /* 2. Write side */
  ssize_t len = strlen(data);
  if (write(fd[1], data, len) != len)
    die("write");

  /* Important: close write end to signal EOF */
  close(fd[1]);

  /* 3. Read side (generic loop) */
  while ((n = read(fd[0], buf, sizeof(buf) - 1)) > 0) {
    buf[n] = '\0';
    printf("read %zd bytes: \"%s\"\n", n, buf);
  }

  if (n == -1)
    die("read");

  close(fd[0]);
  return EXIT_SUCCESS;
}
