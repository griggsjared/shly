#include <limits.h> //PATH_MAX
#include <stdio.h>  //printf, fgetsa, perror
#include <stdlib.h> //EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> //strcmp, strlen, strcspn, strcpy
#include <unistd.h> //fork, execlp, pid_t, wait

#define MAX_INPUT_SIZE 1024
#define MAX_PATH_SIZE 1024
#define TOKEN_BUFFER_SIZE 64

// parse_input takes a string input and a buffer size and returns an array of
// strings (tokens)
char **parse_input(char *input, int buffer_size) {
  char **tokens = malloc(buffer_size * sizeof(char *));
  if (tokens == NULL) {
    fprintf(stderr,
            "Memory allocation failed when parsing input into tokens\n");
    return NULL;
  }

  char *token = strtok(input, " ");

  int i = 0;
  while (token != NULL) {
    // TODO: increase buffer size if needed instead of returning NULL1
    if (i >= buffer_size) {
      fprintf(stderr, "Buffer size exceeded\n");
      return NULL;
    }

    tokens[i] = token;
    token = strtok(NULL, " ");
    i++;
  }
  tokens[i] = NULL;

  return tokens;
}

int main() {
  char input[MAX_INPUT_SIZE];
  char cwd[MAX_PATH_SIZE];

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

    // parse the entire input into argument tokens
    char **args = parse_input(input, TOKEN_BUFFER_SIZE);
    if (args == NULL) {
      fprintf(stderr, "Failed to parse input into tokens\n");
      return EXIT_FAILURE;
    }

    if (args[0] == NULL) {
      free(args);
      continue;
    }

    // handle typing exit or quit
    if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
      break;
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
      continue;
    }

    // handle basic commands that can be handled through fork/exec
    if (args[0] != NULL) {
      pid_t pid = fork();
      if (pid == 0) {
        // child process
        execvp(args[0], args);
        perror("exec");
        return EXIT_FAILURE;
      } else if (pid > 0) {
        wait(NULL);
      }
    }

    free(args);
  }

  printf("shly says goodbye!\n");

  return EXIT_SUCCESS;
}
