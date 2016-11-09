// Unix-like stuff:
#define _GNU_SOURCE       // Before all #include's
#include <unistd.h>       // getpid
#include <sched.h>        // clone
#include <signal.h>       // SIGCHLD

// Generic stuff:
#include <error.h>        // error
#include <errno.h>        // errno
#include <stdio.h>        // printf

#define STACK_SIZE (0x10000) // 65KB.

int work(void *arg) {
  arg = arg;
  printf("Child's perceived PID: %d\n", getpid());
  return 0;
}

char stack[STACK_SIZE];

int main() {
  printf("Parent's perceived PID: %d\n", getpid());

  long retval = clone(work, stack + STACK_SIZE, 0, NULL);
  if (retval < 0) {
    error(1, errno, "system b0rked ;-/");
  }

  printf("Child's real PID: %ld\n", retval);
}
