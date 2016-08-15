#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include "tree.h"
int string_length(char *str);
void filter_it(char *str);
void filter_back(char *str);
int ntree_insert(NTree **, char **, char *);
char **string_split(const char *, char);
void free_str_array(char **);
void list_dir (char *, int, NTree **);

/**
 * read_folder - Reads a folder and subfolders
 * @path: Path to folder
 * Description: Puts all files/folders to an ntree
 */
NTree *read_folder(const char *path)
{
        NTree *tree;
        ntree_insert(&tree, NULL, (char *)path);
        list_dir ((char *)path, string_length((char *)path), &tree);
        return tree;
}

/**
 * list_dir - Recursively goes through all the folders
 * @dir_name: path
 * @len: length of original path
 * @tree: path to ntree 
 * Description: Puts all file/folder names to an ntree
 */
void list_dir (char * dir_name, int len, NTree **tree)
{
	DIR * d;
	d = opendir (dir_name);
	while (1)
	{
		char **array;
		struct dirent * entry;
		char * d_name;
		entry = readdir (d);
		if (! entry)
		{
			break;
		}
		d_name = entry->d_name;
		if (strcmp(d_name, ".") == 0 || strcmp(d_name, "..") == 0)
		{ 
			continue;
		}
		filter_it(dir_name+len);
		ntree_insert(tree, (array = string_split(dir_name, ' ')), d_name);
		free_str_array(array);
		filter_back(dir_name+len);
		if (entry->d_type & DT_DIR)
		{
			if (strcmp(d_name, "..")!=0 && strcmp(d_name, ".")!=0)
			{
				int path_length;
				char path[PATH_MAX];
				path_length = snprintf (path, 
					 PATH_MAX,"%s/%s", dir_name, d_name);
				list_dir (path, len, tree);
			}
		}
	}
	closedir (d);
}

/**
 * string_length - calculates string length
 * @str: input string
 * Description: Returns string length
 */
int string_length(char *str)
{
        int i;
        for (i=0;str[i]; i++);
        return i;
}

/**
 * filter_it - Filters file path
 * @str: String to be filtered
 * Description: Returns nothing
 */
void filter_it(char *str) {
        int i;
        for (i=0; str[i]; i++) {
                if (str[i] == '/')
                {
                        str[i] = ' ';
                }
        }
}

/**
 * filter_back - filters back a file path
 * @str: String to be filtered
 * Description: Returns nothing
 */
void filter_back(char *str) {
        int i;
        for (i=0; str[i]; i++) {
                if (str[i] == ' ')
                {
                        str[i] = '/';
                }
        }
}
