#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]){

    write(1,"Hello, World!\n",15);


    return EXIT_SUCCESS;
}
