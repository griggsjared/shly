#include <stdio.h>  //perror
#include <stdlib.h> //getenv
#include <string.h> //strcmp
#include <unistd.h> //chdir

int handle_cd(char **args) {
  if (strcmp(args[0], "cd") == 0) {
    // no arguments provided, we just go home
    if (args[1] == NULL) {
      if (chdir(getenv("HOME")) == -1) {
        perror("cd");
      }
    } else if (chdir(args[1]) == -1) {
      perror("cd");
    }
    return 1;
  }
  return 0;
}

int handle_exit(char **args) {
  if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
    return -1;
  }
  return 0;
}

int handle_builtins(char **args) {
  int result = 0;
  if (handle_cd(args) == 1) {
    result = 1;
  } else if (handle_exit(args) == -1) {
    result = -1;
  }
  return result;
}
