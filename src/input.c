#include <stdio.h>  //printf, fgetsa, perror
#include <stdlib.h> //malloc, realloc
#include <string.h> //strtok

// parse_input takes a string input and a buffer size and returns an array of
// strings (tokens)
char **parse_input(char *input, int init_buffer_size) {
    int buffer_size = init_buffer_size;
    char **tokens = malloc(buffer_size * sizeof(char *));
    if (tokens == NULL) {
        fprintf(
            stderr, "Memory allocation failed when parsing input into tokens\n"
        );
        return NULL;
    }

    char *saveptr = NULL;
    char *token = strtok_r(input, " ", &saveptr);

    int i = 0;
    while (token != NULL) {
        tokens[i] = token;
        token = strtok_r(NULL, " ", &saveptr);
        i++;

        // if the next iteration is out of bounds, we can extend the buffer
        // with the initial buffer size and re allocate the memory
        if (i >= buffer_size) {
            buffer_size += init_buffer_size;
            tokens = realloc(tokens, buffer_size * sizeof(char *));
        }
    }
    tokens[i] = NULL;

    return tokens;
}
