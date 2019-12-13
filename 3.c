#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    if (!argc)
        return 1;

    FILE *file = fopen(argv[1], "w");
    if(errno)
            printf("Error open");

    char *buffer = malloc(128 * sizeof(char));

    while (1)
    {
        gets(buffer);
        if ((int)buffer[0] == 6)
            break;
        fputs(buffer, file);
        fputs("\n", file);
    }

    int temp = fclose(file);
    if(errno)
    	printf("Error close");
    return 0;
}


