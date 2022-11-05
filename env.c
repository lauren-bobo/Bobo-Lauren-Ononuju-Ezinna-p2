#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>

#define true 1
#define false 0
#define BUFFSIZE 514
int main(int argc, char* argv[], char* env[] ) {
    setbuf(stdout, NULL);

    int i = 0;
    for ( i ; env[i] != NULL; i++) printf("%s\n", env[i]);
} //main
