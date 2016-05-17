#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
  struct stat stat_buf;   
  struct dirent *file_info;
  ino_t itself_ino;       /* holds current folder inode */
  ino_t parent_ino;       /* holds parent folder inode */
  char Current[PATH_MAX];  /* folder name */
  char Path[PATH_MAX];     /* holds the full path */
  char Slash[PATH_MAX];    /* add / before the folder name */ 
  DIR *dir;

  while (1)
    {   
      dir = opendir(".");
      if(dir == NULL) { 
	fprintf(stderr, "cannot get current directory.\n");
	exit(-1);
      }
      /* read the information about the current folder */
      file_info = readdir(dir);

      lstat(file_info->d_name, &stat_buf);
      itself_ino = stat_buf.st_ino;
      closedir(dir);

      chdir("..");    /* go to parent directory */
      dir = opendir(".");

      file_info = readdir(dir);
      lstat(file_info->d_name, &stat_buf);
      parent_ino = stat_buf.st_ino;

      if(itself_ino == parent_ino) {
	/*closedir(dir);*/
	break;
      } else {
	strcpy(Slash, "/");
	strcpy(Current, file_info->d_name);
	strcat(Slash, Current);  /* add "/" as the first */ 
	strcat(Slash, Path);     /* charcter of the directory */ 

	/* check the length of the pathname */
	if(strlen(Slash)  >= PATH_MAX) {
	  fprintf(stderr, "Error! Path too long!\n");
	  exit(0);
	}           
	/* save the full pathname */       
	strcpy(Path, Slash);
      }
      closedir(dir);
    }

  /* print the full path of the current working directory */
  printf("%s\n", Path);
  return 0;
}
