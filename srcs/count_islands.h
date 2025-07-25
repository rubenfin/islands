#ifndef COUNT_ISLANDS_H
#define COUNT_ISLANDS_H

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFERSIZE 1

typedef struct islands
{
    int file_fd;
    char* raw;
    int** map;
    int len;
    int width;

    int total_islands;
    int biggest_island;
    int which_island;
} islands;

#endif
