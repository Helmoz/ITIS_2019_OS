#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

char *my_gets(char *buffer, int amount, FILE *file)
{
    errno = 0;
    for (int i = 0; i < amount; i++)
    {
        buffer[i] = getc(file);
        if (buffer[i] == '\n')
        {
            buffer[i + 1] = '\0';
            break;
        }
        if (errno)
            printf("Error my_gets");
        if (buffer[i] == EOF)
        {
            buffer[i] = '\0';
            break;
        }
    }
    return buffer;
}

void my_puts(char *arr, FILE *file)
{
        errno = 0;
        for(int i = 0; arr[i] != '\0' && arr[i] != EOF; i++)
        {
                fputc(arr[i], file);
                if(errno)
                        printf("Error my_puts");
        }
}

int main(int argc, char const *argv[])
{
    if (!argc)
        return EXIT_FAILURE;

    errno = 0;
        FILE *file = fopen(argv[1], "r");
        if(errno)
                printf("Error open");

    const int GROUPING = atoi(argv[2]);
    char *buffer = malloc(1000 * sizeof(char));
    buffer[0] = 'h';
    while (strlen(buffer))
    {
        if (GROUPING == 0)
        {
            my_gets(buffer, 1000, file);
            my_puts(buffer, stdout);
        }
        else
        {
            getc(stdin);
            for (int i = 0; i < GROUPING; i++)
            {
                my_gets(buffer, 1000, file);
                my_puts(buffer, stdout);
            }
        }
    }
    int temp = fclose(file);
        if(errno)
                printf("Error close");

    return EXIT_SUCCESS;
}


