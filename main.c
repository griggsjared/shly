#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

int main() {
  char input[MAX_INPUT_SIZE];

  while (1) {
    printf("shly: ");
    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
      break;
    }

    // remove newline character
    input[strcspn(input, "\n")] = '\0';

    //handle typeing exit or quit
    if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
      break;
    }
  }

  return EXIT_SUCCESS;
}
