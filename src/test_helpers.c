#include <fcntl.h>  // open
#include <unistd.h> // dup, dup2

static int saved_stderr;

void suppress_stderr() {
  int null_fd = open("/dev/null", O_WRONLY);
  saved_stderr = dup(STDERR_FILENO);
  dup2(null_fd, STDERR_FILENO);
  close(null_fd);
}

void restore_stderr() {
  dup2(saved_stderr, STDERR_FILENO);
  close(saved_stderr);
}
