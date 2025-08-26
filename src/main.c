#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


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

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]){

    // char *header = "HTTP/1.1 200 OK";
    // write(1,header,strlen(header));

    char request[] = "GET / HTTP/1.1\nHost: example.com";

    printf("%s\"\n", parse_get(request, strlen(request)));


    return EXIT_SUCCESS;
}
