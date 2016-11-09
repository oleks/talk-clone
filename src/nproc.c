// Unix-like stuff:
#define _GNU_SOURCE       // Before all #include's
#include <unistd.h>       // getpid
#include <sched.h>        // clone
#include <signal.h>       // SIGCHLD
#include <sys/resource.h> // setrlimit, struct rlimit

// Generic stuff:
#include <error.h>        // error
#include <errno.h>        // errno
#include <stdio.h>        // printf

#define STACK_SIZE (0x10000) // 65KB.

int work(void *arg) {
  arg = arg;
  printf("Child's perceived PID: %d\n", getpid());

  // Forkbomb!
  pid_t pid;
  while((pid = fork()) > 0) {
    printf("PID: %d\n", pid);
  }

  return 0;
}

char stack[STACK_SIZE];

int main() {
  printf("Parent's perceived PID: %d\n", getpid());

  struct rlimit rlim;

  rlim.rlim_max = rlim.rlim_cur = 30;
  int ret = setrlimit(RLIMIT_NPROC, &rlim);
  if (ret < 0) {
    error(1, errno, "setrlimit b0rked ;-/");
  }

  long retval = clone(work, stack + STACK_SIZE, 0, NULL);
  if (retval < 0) {
    error(1, errno, "system b0rked ;-/");
  }

  printf("Child's real PID: %ld\n", retval);
}
