// Unix-like stuff:
#define _GNU_SOURCE       // Before all #include's
#include <unistd.h>       // getpid, syscall
#include <signal.h>       // SIGCHLD
#include <sys/syscall.h>  // SYS_clone

// Generic stuff:
#include <error.h>        // error
#include <errno.h>        // errno
#include <stdio.h>        // printf

int main() {
  printf("Parent's perceived PID: %d\n", getpid());

  long retval = syscall(SYS_clone, SIGCHLD, NULL);
  if (retval < 0) {
    error(1, errno, "system b0rked ;-/");
  }

  if (retval == 0) {
    printf("Child's perceived PID: %d\n", getpid());
  } else {
    printf("Child's real PID: %ld\n", retval);
  }
}
