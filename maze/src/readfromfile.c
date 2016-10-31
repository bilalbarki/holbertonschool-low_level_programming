#include <stdio.h>
#include <math.h>
#include "../inc/description.h"

int readfromfile(char *path) {
    int  i=0, j=0;
    size_t count = 100;
    size_t width;
    char *line = malloc(100);

    FILE *file;  /* declare a FILE pointer  */
    file = fopen(path, "r");  /* open a text file for reading */

    while( (int) (width = getline(&line, &count, file))!=-1) {

        j=0;
        for (; width > 1; width--, j++){
            worldMap[i][j] = (int)line[j] -48;

        }
        mapWidth=j;
        i++;
    }
    mapHeight = i;
    free(line);
    fclose(file);
    return 0;
}