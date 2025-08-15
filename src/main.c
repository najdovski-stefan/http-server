#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]){

    char *header = "HTTP/1.1 200 OK";
    write(1,header,strlen(header));


    return EXIT_SUCCESS;
}
