#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../src/builtins.h"
#include "../src/test_helpers.h"

void test_handle_cd() {
  suppress_stderr();
  char original_path[PATH_MAX];
  char new_path[PATH_MAX];

  // Save current working directory
  getcwd(original_path, PATH_MAX);

  // Test changing to a specific directory
  char *args[] = {"cd", "src", NULL};
  assert(handle_cd(args) == 1);
  getcwd(new_path, PATH_MAX);
  assert(strstr(new_path, "src") != NULL);

  // Test changing back to parent directory
  char *args_parent[] = {"cd", "..", NULL};
  assert(handle_cd(args_parent) == 1);
  getcwd(new_path, PATH_MAX);
  assert(strcmp(new_path, original_path) == 0);

  // Test changing to home directory
  char *args_home[] = {"cd", NULL};
  assert(handle_cd(args_home) == 1);
  getcwd(new_path, PATH_MAX);
  assert(strstr(new_path, getenv("HOME")) != NULL);

  // Test invalid directory
  char *args_invalid[] = {"cd", "/nonexistent_directory", NULL};
  assert(handle_cd(args_invalid) == 1);
  getcwd(new_path, PATH_MAX);
  // Should remain in the same directory after failed cd
  assert(strcmp(new_path, getenv("HOME")) == 0);

  chdir(original_path);

  restore_stderr();

  printf("All handle_cd tests passed!\n");
}

void test_handle_exit() {
  // Test exit
  char *args[] = {"exit", NULL};
  assert(handle_exit(args) == -1);

  // Test quit
  char *args2[] = {"quit", NULL};
  assert(handle_exit(args2) == -1);

  printf("All handle_exit tests passed!\n");
}

void test_handle_pwd() {
  suppress_stdout();
  // Test pwd
  char *args[] = {"pwd", NULL};
  assert(handle_pwd(args) == 1);

  restore_stdout();
  printf("All handle_pwd tests passed!\n");
}

void test_handle_builtins() {
  suppress_stdout();
  suppress_stderr();

  char original_path[PATH_MAX];
  getcwd(original_path, PATH_MAX);

  // Test cd
  char *args_cd[] = {"cd", getenv("HOME"), NULL};
  assert(handle_builtins(args_cd) == 1);

  // test pwd
  char *args4[] = {"pwd", NULL};
  assert(handle_builtins(args4) == 1);

  // Test exit
  char *args2[] = {"exit", NULL};
  assert(handle_builtins(args2) == -1);

  // Test quit
  char *args3[] = {"quit", NULL};
  assert(handle_builtins(args3) == -1);

  chdir(original_path);

  restore_stdout();
  restore_stderr();

  printf("All handle_builtins tests passed!\n");
}

int main() {
  test_handle_cd();
  test_handle_exit();
  test_handle_pwd();
  test_handle_builtins();
  return 0;
}
