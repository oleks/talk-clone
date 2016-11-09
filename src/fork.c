// Unix-like stuff:
#include <unistd.h>       // getpid, fork
#include <sys/types.h>    // pid_t

// Generic stuff:
#include <error.h>        // error
#include <errno.h>        // errno
#include <stdio.h>        // printf

int main() {
  printf("Parent's perceived PID: %d\n", getpid());

  pid_t retval = fork();
  if (retval < 0) {
    error(1, errno, "system b0rked ;-/");
  }

  if (retval == 0) {
    printf("Child's perceived PID: %d\n", getpid());
  } else {
    printf("Child's real PID: %d\n", retval);
  }
}
