#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>

#define true 1
#define false 0
#define BUFFSIZE 514
int main(int argc, char* argv[]) {
    int readFile = 0;
    int c = 0,n = 10;
    int byteNum = false,  lineNum = true;
    int opt;
    //opt parses arguments,
    while((opt = getopt(argc,argv, ":n:c:")) != -1) {
        switch(opt) {
        case 'n': {
            lineNum = true;
            printf("\n\n%ls", optarg);
            //ensure non-negative input
            if (!(atoi(optarg)>0)) {
                errno = EINVAL;
                perror(argv[0]);
            } else if (!(isdidgit(atoi(optarg)))) {
                fprintf(stderr, "invalid number of lines");
            }
                else {
                n = atoi(optarg);
            } //if
            break;
        } //case n
        case 'c': {
            byteNum = true;
            lineNum = false;

            //ensure valid input
            if (!(atoi(optarg)>0)) {
                errno = EINVAL;
                perror(argv[0]);
            } else {
                c = atoi(optarg);
            } //if
            break;
        } //c

            //not throwing error if file name present
        case ':': {
            if (lineNum) {
                errno = EINVAL;
                perror(argv[0]);
            } // lineNum
            if (byteNum) {
                //error msg
            }
                break;
        } // ':'
        } //switch
    } //while
    int i = 0;
    //print number of bytes
    if (byteNum) {
        //start after command line arguments
        //loop through all provided file names
        for( i ; optind  < argc; optind++,  i++) {
            char * fileName = argv[optind];
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
    if (lineNum) {
        for( i ; optind < argc; optind++, i++) {
                char * fileName = argv[optind];
                int file = open(fileName, O_RDONLY);
                char buffer[BUFFSIZE];
                if (file == -1) perror("open");
                //read file and print it until lines exceed n
                readFile = read(file, buffer, BUFFSIZE);
                if(readFile == -1) perror("read");
                int lineNum = 0;
                int j = 0;
                char buffer2[BUFFSIZE];
                //read for new line characters and initialize everything up
                //to there into buff2 to be read
                for( j;  j < readFile && lineNum < n; j++) {
                    buffer2[j] = buffer[j];
                    //check for new line characters
                    if(buffer[j] == '\n') {
                        lineNum++;
                        //printf("%d", lineNum);
                    } //if
                } //for j
                //write only buffer2 with the specified number of lines
                write(STDOUT_FILENO, buffer2, readFile);
            } //for

        } //if n
} //main
