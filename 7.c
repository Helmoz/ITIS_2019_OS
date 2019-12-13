#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h> 
 
int get_files(char *path, char ***files);
void sort_files(char **arr, int len, int sort, char *dir);
int write_files(char **arr, int len, char *to, char *from);
char *createPath(char *prefix, char *suffix);

char *createPath(char *prefix, char *suffix)
{
    const int str_len = strlen(prefix) + strlen(suffix);
    char *buffer = malloc(sizeof(char) * str_len + 2);
    memcpy(
        buffer,
        prefix,
        sizeof(char) * strlen(prefix));
    buffer[strlen(prefix)] = '/';
    memcpy(
        &buffer[strlen(prefix) + 1],
        suffix,
        sizeof(char) * strlen(suffix));
    buffer[str_len + 1] = '\0';
    return buffer;
}

int file_comparator_lex(const void *a, const void *b)
{
    const char *first = *(const char **)a;
    const char *second = *(const char **)b;
    const int len = strlen(first) > strlen(second) ? strlen(second) : strlen(first);
    for (int i = 0; i < len; i++)
        if (first[i] - second[i])
            return first[i] - second[i];
    return strlen(first) - strlen(second);
}
 
int get_files(char *path, char ***files) {
    DIR *dir = opendir(path);
    struct dirent *dd;
    int len = 0;
	*files = (char **)malloc(sizeof(char) * 1000);

    while ((dd = readdir(dir)) != NULL) {
        if (dd->d_name[0] == '.') {
            continue;
        }
        (*files)[len++] = (*dd).d_name;     
    }
    return len;
}

void sort_files(char **arr, int len, int sort, char *dir) {
    char *tmp;
	struct stat st_1;
	struct stat st_2;
    switch (sort) {
        case 1:{
            for (int i = 0; i < len - 1; i++){
                for (int j = i + 1; j < len; j++) {
					stat(createPath(dir, arr[i]), &st_1);
					stat(createPath(dir, arr[j]), &st_2);
                    if (st_1.st_size > st_2.st_size) {
                        tmp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = tmp;
                    }
                }
            }
            break;
        }
        case 2:{
            qsort(arr, len, sizeof(char *), file_comparator_lex);
            break;
        }
    }
}

int write_files(char **arr, int len, char *to, char *from) {
    FILE *file_in, *file_out;
    char *file_name_in, *file_name_out;  
	struct stat st_1;  
    for (int i = 0; i < len; i++) {
        file_name_in = createPath(from, arr[i]);
        file_name_out = createPath(to, arr[i]);
        file_in = fopen(file_name_in, "r");
        file_out = fopen(file_name_out, "w");
		int *buffer = malloc(1000 * sizeof(int));
        while(fread(buffer, sizeof(int), 1000, file_in)){
			fwrite(buffer, sizeof(int), 1000, file_out);
		}
        fclose(file_in);
        fclose(file_out);
	stat(createPath(from, arr[i]), &st_1);
	
        printf("%s %s - %li byte\n",
                file_name_out,
                arr[i],
                st_1.st_size);
    }
    return 0;
} 
 
int main(int argc, char *argv[]){
    char *from = argv[1];
    int key = atoi(argv[2]);
    char *to = argv[3];
    char **files;
    int result = get_files(from, &files);

	if (result > 0) {
        sort_files(files, result, key, from);
    }
	write_files(files, result, to, from);

    return 0;
}
