#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/input.h"

void test_parse_input() {
    // test does it tokenize the input correctly
    char input1[] = "ls -l /home";
    char **result1 = parse_input(input1, 64);
    assert(result1 != NULL);
    assert(strcmp(result1[0], "ls") == 0);
    assert(strcmp(result1[1], "-l") == 0);
    assert(strcmp(result1[2], "/home") == 0);
    free(result1);

    // test for empty input
    char input2[] = "";
    char **result2 = parse_input(input2, 64);
    assert(result2 != NULL);
    assert(result2[0] == NULL);

    // test for multiple spaces
    char input3[] = "shly  is   cool      ";
    char **result3 = parse_input(input3, 64);
    assert(result3 != NULL);
    assert(strcmp(result3[0], "shly") == 0);
    assert(strcmp(result3[1], "is") == 0);
    assert(strcmp(result3[2], "cool") == 0);
    free(result3);

    // test if its can increase the buffer size
    char input4[] = "ls -l /home";
    char **result4 = parse_input(input4, 1);
    assert(result4 != NULL);
    assert(strcmp(result4[0], "ls") == 0);
    assert(strcmp(result4[1], "-l") == 0);
    assert(strcmp(result4[2], "/home") == 0);

    printf("All parse_input tests passed!\n");
}

int main() {
    test_parse_input();
    return 0;
}
