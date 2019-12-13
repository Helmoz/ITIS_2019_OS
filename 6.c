#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
        DIR *dir = opendir(getenv("PWD"));
        if(!dir){
                printf("Failed read current dir\n");
                return 1;
        }
        struct dirent *dir1;
        printf("Current dir:\n");
        while( (dir1 = readdir(dir)) != NULL){
                printf("%s\n", dir1->d_name);
        }
        closedir(dir);
        printf("\n");
        DIR *dir2 = opendir(argv[1]);
        if(!dir){
                printf("Failed read argument dir\n");
                return 1;
        }
        struct dirent *dir3;
        printf("Argument dir:\n");
        while( (dir3 = readdir(dir2)) != NULL){
                printf("%s\n", dir3->d_name);
        }
        closedir(dir2);
        return 0;
}

