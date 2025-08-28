#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define INDEX_FILE "index.html"

char *parse_get(char *get_request, size_t req_length){

    char *start, *end;

    //man ascii 32? 40? ' ' -> 32(int) 20 hex

    for(start = get_request; start[0] != ' '; start++){
        if (start[0] == '\0') {
            return NULL;
        }
    }

    start++;

    for(end = start; end[0] != ' '; end++){
        if(end[0] == '\0'){
            return NULL;
        }
    }

    if(end[-1] != '/'){
        end[0] = '/';
        end++;
    }

    //malformed GET Request
    if(end + strlen(INDEX_FILE) > get_request + req_length){
        return NULL;
    }

    memcpy(end,INDEX_FILE,strlen(INDEX_FILE)+1);

    return start+1;
}

void printFile(char *path){

    //File Descriptor
    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat metadata;

    // Get file metadata using file descriptor
    if (fstat(fd, &metadata) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // for study only this is my first encounter to this library
    printf("File: %s\n", path);
    printf("Size: %lld bytes\n", metadata.st_size);
    printf("Mode: %o\n", metadata.st_mode & 0777);
    printf("Links: %d\n", metadata.st_nlink);
    printf("UID: %d\n", metadata.st_uid);
    printf("GID: %d\n", metadata.st_gid);
    printf("Last accessed: %s", ctime(&metadata.st_atime));
    printf("Last modified: %s", ctime(&metadata.st_mtime));
    printf("Last status change: %s", ctime(&metadata.st_ctime));

    // Check file type
    if (S_ISREG(metadata.st_mode)) {
        printf("Type: Regular file\n");
    } else if (S_ISDIR(metadata.st_mode)) {
        printf("Type: Directory\n");
    } else if (S_ISLNK(metadata.st_mode)) {
        printf("Type: Symbolic link\n");
    }

    //allocate memory
    // metadata.st_size + \0

    char *buffer = malloc(metadata.st_size + 1);

    if(buffer == NULL){
        perror("Error MemoryAlloc!");
        close(fd);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes = read(fd, buffer, metadata.st_size);
    if(bytes == -1){
        perror("Error reading file");
        close(fd);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    buffer[bytes] = '\0';
    printf("FILE CONTENTS:%s\n",buffer);


    close(fd);
    free(buffer);

}

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]){

    // char *header = "HTTP/1.1 200 OK";
    // write(1,header,strlen(header));

    char request[] = "GET / HTTP/1.1\nHost: example.com";

    printf("%s\n", parse_get(request, strlen(request)));

    printFile(INDEX_FILE);


    return EXIT_SUCCESS;
}
