#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <dirent.h>
int string_ncompare(const char *s, const char *t, size_t n);
void print_tab(char **split);
char **string_split(const char *str, char separator);
char *dir_path(char *s1, char *s2);
/*

int search_dir(char **args, char **envp){
	DIR *directory;

}*/

void print_line(char *line){
  for (;*line;line++)
    print_char(*line);
}

int strings_compare(const char *s1, const char *s2){
  int i;
  for (i=0;*(s1+i)==*(s2+i);i++){
    if (*(s1+i)=='\0')
      return 0;
  }
  return (*(s1+i)-*(s2+i));
}

int main (__attribute__((unused)) int argc, __attribute__((unused)) char *args[], char *envp[]){
  int i;
  char **paths, *dirpath;
  DIR *directory;
  struct dirent *dir_info;
  for (i=0;envp[i];i++){
    if ( string_ncompare(envp[i],"PATH",4) == 0 ){
    	paths=string_split(envp[i]+5, ':');
    	break;
    }
  }
  for (i=0;paths[i];i++){
  	directory=opendir(paths[i]);
  	if (directory==NULL){
  		continue;
  	}
  	while( ( dir_info=readdir(directory) )!=NULL ){
  		if ( strings_compare(dir_info->d_name,args[1])==0 ){
  			dirpath=dir_path(paths[i],dir_info->d_name);
  			print_line( dirpath );
  			free(dirpath);
  			print_line("\n");
  			break;
  		}
  	}
  	closedir(directory);
  }
  free_tab(paths);
  return 1;
}

int string_ncompare(const char *s, const char *t, size_t n) {
	for ( ; n--; s++, t++) {
    	if(*s != *t) {
      	  return *s - *t;
    	}
	}
}
/*
char *concat_strings(char *dest, const char *src){
  int i;
  char *dest_start;
  dest_start=dest;
  for (;*dest!='\0';dest++);
  for (i=0;*(src+i)!='\0';i++)
    *(dest++)=*(src+i);
  *dest='\0';
  return dest_start;
}*/

char *dir_path(char *s1, char *s2){
	int i, count;
	char *joined_string;
	for (count=0, i=0; s1[i];i++)
		count++;
	for (i=0; s2[i];i++)
		count++;
	if (count==0) return NULL;
	joined_string=malloc( sizeof(char)*(count+2) );
	for (i=0; s1[i];i++)
		joined_string[i]=s1[i];
	joined_string[i]='/';
	i++;
	for (count=0; s2[count];count++,i++)
		joined_string[i]=s2[count];
	joined_string[i]='\0';
	return joined_string;
}