#include <stdio.h>  //printf, perror
#include <stdlib.h> //EXIT_SUCCESS, EXIT_FAILURE, exit
#include <string.h> //strcmp, strcspn, strcpy
#include <unistd.h> //fork, execlp, pid_t, wait, chdir, getcwd, getenv

#include "../src/builtins.h" //handle_builtins
#include "../src/input.h"    //parse_input

#define MAX_INPUT_SIZE 1024
#define MAX_PATH_SIZE 1024
#define TOKEN_BUFFER_SIZE 64

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

        if (args[0] != NULL) {
            int result = handle_builtins(args);
            if (result == -1) {
                break;
            }

            if (result == 0) {
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
        }

        free(args);
    }

    printf("shly: goodbye!\n");
    return EXIT_SUCCESS;
}
