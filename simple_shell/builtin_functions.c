#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void free_tab(char **split);
int strings_compare(const char *s1, const char *s2);
int shell_cd(char **args, char ***);
int shell_exit(char **args, char ***envp, char **d_or, char **d_ampersand, char **semicolon);
int shell_env(char **args, char ***envp);
int shell_fork_and_run(char **, char **);
int convert_string_to_int(char *source_string);
char *get_env(char *name, char **envp);
char **add_envp(char *envp[], char *add_new);
char **remove_envp(char *envp[], char *remove_ptr);
int write_to_index(char *source, char *dest, char term, char index);
int shell_setenv(char **args, char ***envp);
int get_env_index(char *name, char **envp);

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

int shell_exit(char **args, char ***envp, char **d_or, char **d_ampersand, char **semicolon){
	int status;
	if (args[1]==NULL){
		free_tab(*envp);
		free_tab(args);
		free_tab(d_or);
		free_tab(d_ampersand);
		free_tab(semicolon);
		exit(0);
	}
	else if (args[2]==NULL){
		if ( ( status=convert_string_to_int(args[1]) ) == 0){
			print_line("exit: Usage: exit [0-255]\n");
			return 1;
		}
		free_tab(*envp);
		free_tab(args);
		free_tab(d_or);
		free_tab(d_ampersand);
		free_tab(semicolon);
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
		if ( (i=get_env_index(args[1], *envp)) >= 0 ){
			free( (*envp)[i] );
			(*envp)[i]=malloc(sizeof(char)*(count+2));
			count=(write_to_str(args[1], (*envp)[i], '=', 0))+1;
			write_to_index(args[2], (*envp)[i], '\0', count);
			return 0;
		}
		line=malloc(sizeof(char)*(count+2));
		i=(write_to_str(args[1], line, '=', 0))+1;
		write_to_index(args[2], line, '\0', i);
		envp_new=add_envp(*envp, line);
		free(line);
		*envp=envp_new;
		return 0;
	}
	print_line("setenv: Usage: setenv VARIABLE VALUE");
	return 1;
}

int shell_unsetenv(char **args, char ***envp){
	char *line, **envp_new;
	if (args[2]==NULL){ 
		if ( line=get_env(args[1], *envp) ){
			envp_new=remove_envp(*envp, line);
			*envp=envp_new;
			return 0;
		}
		else{
			print_line(args[1]);
			print_line(" doesn't exist");
			return 1;
		}
	}
	print_line("setenv: Usage: unsetenv VARIABLE VALUE");
	return 1;
}

int shell_alias(char **args, char ***alias){

}


/*char *variable_name(char *source){
	int i, j, prev;
	for (i=0, source[i], i++){
		if (source[i]=='$'){
			prev=i;
			for (;source[i]; i++){

			}
		}
	}
}

void initial_processing(char **args, char ***envp){
	int i, index;
	for (i=0;args[i];i++){
		if ( index=get_index(args[i],'$') ){

		}
	}
}*/

int shell_execute(char **args, char ***envp, char **d_or, char **d_ampersand, char **semicolon){
	/*initial_processing(char **args, char ***envp);*/

	char *builtin_str[] = {
  		"cd",
  		"env",
  		"setenv",
  		"unsetenv",
  		"alias",
  		NULL
	};
	int (*built_in[])(char **, char ***)={
		&shell_cd,
		&shell_env,
		&shell_setenv,
		&shell_unsetenv,
		&shell_alias
	};

	/*int size=sizeof(builtin_str) / sizeof(char *);*/
	int i;
	for (i=0;builtin_str[i];i++){
		if ( strings_compare(args[0], builtin_str[i]) == 0 ){
			return built_in[i](args, envp);
		}
	}
	if ( strings_compare(args[0], "exit") == 0 ){
		return shell_exit(args, envp, d_or, d_ampersand, semicolon);
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