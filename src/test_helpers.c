#include <fcntl.h>  // open
#include <unistd.h> // dup, dup2

static int saved_stderr;
static int saved_stdout;

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

void suppress_stdout() {
    int null_fd = open("/dev/null", O_WRONLY);
    saved_stdout = dup(STDOUT_FILENO);
    dup2(null_fd, STDOUT_FILENO);
    close(null_fd);
}

void restore_stdout() {
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
}
