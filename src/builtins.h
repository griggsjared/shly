//handle_builtins should return -1 if the program should exit, 1 if the program should continue, and 0 if the program should fork and exec the command
int handle_builtins(char **args);

//handle_cd should return 1 if the program should continue, and 0 if the program should fork and exec the command
int handle_cd(char **args);

//handle_exit should return -1 if the program should exit, and 0 if the program should fork and exec the command
int handle_exit(char **args);

