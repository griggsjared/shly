//builtin_command_t is a struct that holds the command and the handler function
typedef struct {
  //command is the base command to match
  const char *command;
  //handler is the function to call if the command matches
  int (*handler)(char **args);
} builtin_command_t;

// handle_builtins should process any builtings and return a status code
// -1 to signal the built in wants to exit
// 1 if the built in was handled
// 0 if the built in was not handled
int handle_builtins(char **args);

// handle_cd handles the cs command
int handle_cd(char **args);

// handle_exit handles the exit and quit commands
int handle_exit(char **args);
