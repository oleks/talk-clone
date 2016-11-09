// Unix-like stuff:
#define _GNU_SOURCE       // Before all #include's
#include <unistd.h>       // getpid
#include <sched.h>        // clone
#include <signal.h>       // SIGCHLD
#include <fcntl.h>        // O_RDONLY

// Generic stuff:
#include <error.h>        // error
#include <errno.h>        // errno
#include <stdio.h>        // printf

#define STACK_SIZE (0x10000) // 65KB.

int work(void *arg) {
  arg = arg;

  int fd = open("fork.c", O_RDONLY);
  printf("Child fd = %d\n", fd);

  return 0;
}

char stack[STACK_SIZE];

int main(int argc, char *argv[]) {
  argv = argv;

  printf("Parent's perceived PID: %d\n", getpid());

  int flags = argc > 1 ? CLONE_FILES : 0;
  long retval = clone(work, stack + STACK_SIZE, flags, NULL);
  if (retval < 0) {
    error(1, errno, "system b0rked ;-/");
  }

  int fd = open("fork.c", O_RDONLY);
  printf("Parent fd = %d\n", fd);

  printf("Child's real PID: %ld\n", retval);
}
