#include <limits.h> //PATH_MAX
#include <stdio.h>  //printf, fgetsa, perror
#include <stdlib.h> //EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> //strcmp, strlen, strcspn, strcpy
#include <unistd.h> //fork, execlp, pid_t, wait

#define MAX_INPUT_SIZE 1024

int main() {
  char input[MAX_INPUT_SIZE];
  char cwd[PATH_MAX]; // 1024

  while (1) {

    // setting up the initial cwd
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
      perror("getcwd");
      return EXIT_FAILURE;
    }

    // showing our super basic prompt with the cwd
    printf("%s $ ", cwd);

    // get the input
    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
      break;
    }

    // remove newline character
    input[strcspn(input, "\n")] = '\0';

    // handle typing exit or quit
    if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
      break;
    }

    // handle cd command
    if (strcmp(input, "cd") == 0) {
      if (chdir(getenv("HOME")) == -1) {
        perror("chdir");
      }
      continue;
    } else if (strncmp(input, "cd ", 3) == 0) {
      if (chdir(input + 3) == -1) {
        perror("chdir");
      }
      continue;
    }

    // handle basic commands that can be handled through fork/exec
    if (strlen(input) > 0) {
      pid_t pid = fork();
      if (pid == 0) {
        // child process
        execlp(input, input, NULL);
        perror("exec");
        return EXIT_FAILURE;
      } else if (pid > 0) {
        wait(NULL);
      }
    }
  }

  printf("Shly says goodbye!\n");

  return EXIT_SUCCESS;
}
