#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

#define true 1
#define false 0
#define BUFFSIZE 514
int main(int argc, char* argv[]) {
    int readFile = 0;
    int c,n = 10;
    int indexOfFileStart = 1;
    int opt;
    while((opt = getopt(argc,argv, ":n:c:")) != -1) {
        switch(opt) {
        case 'n': {
            n = atoi(optarg);
            indexOfFileStart = 3;
            break;
        } //case n
        case 'c': {
            c = atoi(optarg);
            indexOfFileStart = 3;
            n = 0;
            break;
        } //case c
        } //switch
    } //while
    //set variables for file read
    int i = indexOfFileStart;
    //print number of bytes
    if (c > 0) {
        //start after command line arguments
        //loop through all provided file names
        for( i ; i < argc; i++) {
            char * fileName = argv[i];
            int file = open(fileName, O_RDONLY);
            //set buffer to size c
            char buffer[c];
            if (file == -1) perror("open");
        //read from file at argv[i] for only c bytes and print to std output
            readFile = read(file, buffer, c);
            //printf("readfile = %d", readFile);
            write(STDOUT_FILENO, buffer, readFile);
            if(readFile == -1) perror("read");
        } //for
    } //if


    // print num lines
        if (n > 0) {
            int i = indexOfFileStart;
            for( i ; i < argc; i++) {
                char * fileName = argv[i];
                int file = open(fileName, O_RDONLY);
                char buffer[BUFFSIZE];
                if (file == -1) perror("open");
                //read file and print it until lines exceed n
                readFile = read(file, buffer, BUFFSIZE);
                if(readFile == -1) perror("read");
                int lineNum = 0;
                int j = 0;
                char buffer2[BUFFSIZE];
                for( j;  j < readFile && lineNum < n; j++) {
                    buffer2[j] = buffer[j];
                    if(buffer[j] == '\n') {
                        lineNum++;
                        //printf("%d", lineNum);
                    } //if
                } //for j
                write(STDOUT_FILENO, buffer2, readFile);
            } //for

        } //if n
} //main
