#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>


int main(int argc, char* argv[]) {
    int * BUFFSIZE;
    int readFile;

    int c,n = 10;
    int indexOfFileStart = 1;
    int opt;
    while((opt = getopt(argc,argv, ":n:c:")) != -1) {
        if (opt == 'n') {
            n = atoi(optarg);
            indexOfFileStart = 3;
        } //if
        if(opt == 'c') {
            c = atoi(optarg);
            indexOfFileStart = 3;
            n = 0;
            BUFFSIZE = (int*)malloc(c);
        } //if
    } //while
    //printf("c = %d n = %d", c, n);
    if (c > 0) {
    int i = indexOfFileStart;
    for( i ; i < argc; i++) {
        char * fileName = argv[i];
        int file = open(fileName, O_RDONLY);
        char buffer[c];
        if (file == -1) perror("open");
        //read from file at argv[i] and print to std output
        readFile = read(file, buffer, c);
        //printf("readfile = %d", readFile);
        write(STDOUT_FILENO, buffer, readFile);
        if(readFile == -1) perror("read");
    } //for
    } //if
} //main
