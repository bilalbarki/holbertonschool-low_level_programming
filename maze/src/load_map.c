#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/extern.h"
#include "../inc/definitions.h"

/**
 * counts number of rows in the map file
 * @*path: path to map text file
 * RETURNS: returns count if all goes well, -1 if there is an error in opening the file
 */
int row_count( char *path )
{
    int c, count;
    FILE *fin;
    count = 0;
   
    fin = fopen( path, "r" );
    if( fin == NULL )
    {
        return -1;
    }
    while (1)
    {
        c = fgetc( fin );
        if (c =='\n')
            count++;
        else if( c == EOF )
            break;
    }
    fclose(fin);
    return count;
}

/**
 * counts number of columns in the map file
 * @*path: path to map text file
 * RETURNS: returns count if all goes well, -1 if there is an error in opening the file
 */
int column_count( char *path )
{
    int c, count;
    FILE *fin;
    count = 0;
   
    fin = fopen( path, "r" );
    if( fin == NULL )
    {
        return -1;
    }
    while (1)
    {
        c = fgetc( fin );
        if( c == EOF || c == '\n' )
            break;
        count++;
    }
    fclose(fin);
    return count;
}

/**
 * loads map from the file to a 2d array
 * @*path: path to map text file
 * @*ncolumn: number of columns for the map
 * RETURNS: returns 0 if all goes well, 1 if there is an error in opening the file
 */
int load_map_from_file(char *path, size_t ncolumn) {
    int  i=0, j=0;
    //size_t count;
    size_t width;
    char *line;
    
    //ncolumn = column_count(path);
    line = malloc(ncolumn);
   
    FILE *file;  /* declare a FILE pointer  */
    file = fopen(path, "r");  /* open a text file for reading */
    if( file == NULL )
    {
        return 1;
    }

    while( (int) (width = getline(&line, &ncolumn, file))!=-1) {

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

/**
 * initializes and loads world map
 * @*path: path to map text file
 * RETURNS: returns 0 if all goes well, 1 if there was an error
 */
int initialize_world_map(char *path)
{
    int nrows, ncolumns, i;
    nrows = row_count(path);
    ncolumns = column_count(path);
    worldMap = malloc( (nrows+1) * sizeof(int *));
    for (i=0; i<nrows; i++) {
        worldMap[i] = malloc(ncolumns * sizeof(int));
    }
    worldMap[nrows] = NULL;
    load_map_from_file(path, ncolumns);
    return 0;
}