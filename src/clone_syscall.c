// Unix-like stuff:
#define _GNU_SOURCE       // Before all #include's
#include <unistd.h>       // getpid, syscall
#include <signal.h>       // SIGCHLD
#include <sys/syscall.h>  // SYS_clone

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

  size_t *zstack = (size_t*)stack;
  zstack[(STACK_SIZE/sizeof(size_t))-1] = (size_t)work;

  long retval = syscall(SYS_clone, 0, stack + STACK_SIZE - 8);
  if (retval < 0) {
    error(1, errno, "system b0rked ;-/");
  }

  if (retval == 0) {
    printf("Child's perceived PID: %d\n", getpid());
  } else {
    printf("Child's real PID: %ld\n", retval);
  }
}
