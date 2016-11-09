// Unix-like stuff:
#include <unistd.h>       // getpid

// Generic stuff:
#include <stdio.h>        // printf

int work(void *arg) {
  arg = arg;
  printf("Child's perceived PID: %d\n", getpid());
  return 0;
}

int main() {
  work(NULL);
}
