#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include "tree.h"
void filter_it(char *str);
void filter_back(char *str);
int ntree_insert(NTree **, char **, char *);
char **string_split(const char *, char);
void free_str_array(char **);
void list_dir (char *, int, NTree **);
char *string_concat(char *s1, char joiner, char *s2);

/**
 * read_folder - Reads a folder and subfolders
 * @path: Path to folder
 * Description: Puts all files/folders to an ntree
 */
NTree *read_folder(const char *path)
{
        NTree *tree;
	int len;
        for (len=0; path[len]; len++);
        ntree_insert(&tree, NULL, (char *)path);
        list_dir ((char *)path, len, &tree);
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
				char *path;
				path = string_concat(dir_name, '/', d_name);
				list_dir (path, len, tree);
				free(path);
			}
		}
	}
	closedir (d);
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

/**
 * string_concat - Concats two string with a joiner
 * @s1: First input string
 * @joiner: The joiner is the middle char in between
 * @s2: Second input string
 * Description: Puts all files/folders to an ntree
 */
char *string_concat(char *s1, char joiner, char *s2)
{
	int i,j,p;
	char *concat;
	for ( i=0; s1[i]!='\0'; i++ );
	for ( j=0; s2[j]!='\0'; j++ );
	j=j+i;
	concat=malloc( sizeof(char) * (j+2) );
	if (concat == NULL)
	{
		return NULL;
	}
	for ( p=0; s1[p]; p++ ) concat[p]=s1[p];
	concat[p]=joiner;
	p++;
	for (i=0 ; s2[i]; p++, i++ ) concat[p]=s2[i];
	concat[p]='\0';
	return concat;
}
