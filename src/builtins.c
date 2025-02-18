#include <stdio.h>  //perror
#include <stdlib.h> //getenv
#include <string.h> //strcmp
#include <unistd.h> //chdir

#include "builtins.h" //builtin_command_t

int handle_cd(char **args) {
  if (strcmp(args[0], "cd") != 0) {
    return 0;
  }

  if (args[1] == NULL) {
    if (chdir(getenv("HOME")) == -1) {
      perror("cd");
    }
  } else if (chdir(args[1]) == -1) {
    perror("cd");
  }

  return 1;
}

int handle_exit(char **args) {
  if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
    return -1;
  }

  return 0;
}

int handle_builtins(char **args) {
  if (args[0] == NULL) {
    return 0;
  }

  builtin_command_t builtins[] = {
    {"cd", handle_cd},
    {"exit", handle_exit},
    {"quit", handle_exit},
    {NULL, NULL}
  };

  for (builtin_command_t *builtin = builtins; builtin->command != NULL;
       builtin++) {
    if (strcmp(args[0], builtin->command) != 0) {
      continue;
    }

    int result = builtin->handler(args);
    if (result != 0) {
      return result;
    }
  }

  return 0;
}
