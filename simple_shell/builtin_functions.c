#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void free_tab(char **split);
int strings_compare(const char *s1, const char *s2);
int shell_cd(char **args, char ***);
int shell_exit(char **args, char ***);
int shell_env(char **args, char ***envp);
int shell_fork_and_run(char **, char **);
int convert_string_to_int(char *source_string);
char *get_env(char *name, char **envp);
char **copy_envp(char *envp[], char *add_new);
int write_to_index(char *source, char *dest, char term, char index);

int shell_cd(char **args, char ***envp){
	if (args[1]==NULL){
	
	} 
	else{
		if ( chdir(args[1]) !=0 ){
			perror(args[1]);
		}
	}
	return 1;
}

int shell_exit(char **args, char ***envp){
	int status;
	if (args[1]==NULL){
		free_tab(*envp);
		free_tab(args);
		exit(0);
	}
	else if (args[2]==NULL){
		status=convert_string_to_int(args[1]);
		if (status==0){
			print_line("exit: Usage: exit [0-255]\n");
			return 1;
		}
		free_tab(*envp);
		free_tab(args);
		exit(status);
	}
	else{
		print_line("exit: Usage: exit [0-255]\n");
	}
	return 1;
}

int shell_env(char **args, char ***envp){
	print_tab(*envp);
	return 1;
}

int shell_setenv(char **args, char ***envp){
	char *line, **envp_new;
	int i, count;
	if (args[3]==NULL){ 
		count=string_length(args[1])+string_length(args[2]);
		if ( line=get_env(args[1], *envp) ){
			free(line);
			line=malloc(sizeof(char)*(count+2));
			i=(write_to_str(args[1], line, '=', 0))+1;
			write_to_index(args[2], line, '\0', i);
			return 0;
		}
		line=malloc(sizeof(char)*(count+2));
		i=(write_to_str(args[1], line, '=', 0))+1;
		write_to_index(args[2], line, '\0', i);
		envp_new=copy_envp(*envp, line);
		free(line);
		free_tab(*envp);
		*envp=envp_new;
		return 0;
	}
	print_line("setenv: Usage: setenv VARIABLE VALUE");
	return 1;
}


int shell_execute(char **args, char ***envp){
	char *builtin_str[] = {
  		"cd",
  		"exit",
  		"env",
  		"setenv"
	};
	int (*built_in[])(char **, char ***)={
		&shell_cd,
		&shell_exit,
		&shell_env,
		&shell_setenv
	};

	int size=sizeof(builtin_str) / sizeof(char *);
	int i;
	for (i=0;i<size;i++){
		if ( strings_compare(args[0], builtin_str[i]) == 0 ){
			return built_in[i](args, envp);
		}
	}
	return shell_fork_and_run(args, *envp);
}

int strings_compare(const char *s1, const char *s2){
  int i;
  for (i=0;*(s1+i)==*(s2+i);i++){
    if (*(s1+i)=='\0')
      return 0;
  }
  return (*(s1+i)-*(s2+i));
}

int convert_string_to_int(char *source_string){
	int n=0;
	for(;*source_string;source_string++){
		if ( (*source_string<'0') || (*source_string>'9') ) return 0;
		n*=10;
		n=n +( ( (int)(*source_string) ) - '0' );
		if (n>255) return 0;
	}
	return n;
}