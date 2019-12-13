#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    if (!argc)
        return 1;
        errno = 0;

        FILE *src = fopen(argv[1], "r");
        if(src == NULL){
                printf("Source file doesnt exist");
                return 1;
        }
        FILE *dist = fopen(argv[2], "w");
        if(dist == NULL){
                printf("Destination file error");
                return 1;
        }
        struct stat stats;
        stat(argv[1], &stats);
        int letter;

    while ((letter = getc(src)) != EOF)
    {
                putc(letter, dist);
    }

    fclose(src);
        fclose(dist);
        if(errno){
                printf("Error close");
                return 1;
        }

        chmod(argv[2], stats.st_mode);

    return 0;
}

