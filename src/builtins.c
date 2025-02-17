#include <stdio.h> //perror
#include <stdlib.h> //getenv
#include <string.h> //strcmp
#include <unistd.h> //chdir

int handle_builtins(char **args) {

  // handle exit or quit command
  if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
    return -1;
  }

  // handle cd command
  if (strcmp(args[0], "cd") == 0) {
    // no arguments provided, we just go home
    if (args[1] == NULL) {
      if (chdir(getenv("HOME")) == -1) {
        perror("chdir");
      }
    } else {
      if (chdir(args[1]) == -1) {
        perror("chdir");
      }
    }

    return 1;
  }

  return 0;
}
