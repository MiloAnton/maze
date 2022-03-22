#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

FILE *fp;
char *line = NULL;
size_t len = 0;
ssize_t read;

int sizeX = 0;
int sizeY = 0;

int startX;
int startY;

char **maze;

void readTxt(char caca[])
{
    char buff[1000][1000];
    printf("%s", caca);
    fp = fopen(caca, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1)
    {
        sizeX = strlen(line);
        for (int x = 0; x < sizeX; x++)
        {
            buff[sizeY][x] = line[x];
        }
        sizeY++;
    }

    maze = (char **)malloc(sizeX * sizeY * sizeof(char *));
    for (int i = 0; i < sizeY; i++)
    {
        maze[i] = (char *)malloc(sizeX * sizeof(char));
    }

    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            if (buff[i][j] == '1')
            {
                startX = j;
                startY = i;
            }
            maze[i][j] = buff[i][j];
        }
    }
    fclose(fp);
    if (line)
        free(line);
}

bool explore(int posX, int posY){
    if (posX < 0 || posY < 0 || posX >= sizeX || posY >= sizeY){
        return false;
    }
    if (maze[posY][posX] == '2'){
        return true;
    }
    else if (maze[posY][posX] == ' ' || maze[posY][posX] == '1'){
        maze[posY][posX] = 'o';
        if(explore(posX+1, posY)){
            maze[posY][posX] = 'x';
            return true;
        }
        if(explore(posX, posY-1)){
            maze[posY][posX] = 'x';
            return true;
        }
        if(explore(posX-1, posY)){
            maze[posY][posX] = 'x';
            return true;
        }
        if(explore(posX, posY+1)){
            maze[posY][posX] = 'x';
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    clock_t begin = clock();
    readTxt(argv[1]);
    explore(startX, startY);
    clock_t end = clock();
    for(int i = 0; i < sizeY; i++) {
        for(int j = 0; j < sizeX; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTemps d'execution : %f s\n", time_spent);
}