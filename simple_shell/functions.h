void print_tab(char **split);
void free_tab(char **split);
void get_split_exec_loop(char **);
char *read_line(const int fd);
char **string_split(const char *str, char separator);
int shell_fork_and_run(char **, char **);

