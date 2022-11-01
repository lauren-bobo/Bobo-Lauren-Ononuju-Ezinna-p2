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
            //ensure non-negative input
            if (!(atoi(optarg)>0)) {
                //errno = EINVAL;
                //perror(argv[0]);
                fprintf(stderr, "%s: %s: invalid number of lines\n", argv[0], argv[2]);
                return EXIT_SUCCESS;
            } else {
                n = atoi(optarg);
            } //if
            break;
        } //case n

        case 'c': {
            byteNum = true;
            lineNum = false;
            n = 0;
            //ensure valid input
            if (!(atoi(optarg)>0)) {
                //errno = EINVAL;
                //perror(argv[0]);
                fprintf(stderr, "%s: %s:invalid number of bytes\n", argv[0], argv[2]);
                return EXIT_SUCCESS;
            } else {
                c = atoi(optarg);
            } //if
            break;
        }
            //not throwing error if argument not present
        case ':': {
            if (lineNum) {
                errno = EINVAL;
                perror(argv[0]);
            } // lineNum
            if (byteNum) {
                errno = EINVAL;
                perror(argv[0]);
            }
        } // ':'
        } //switch
    } //while
        /* temporary */

    int i = 0;
    //print number of bytes
    if (byteNum) {
        //start after command line arguments
        //loop through all provided file names
        for( i ; optind  < argc; optind++,  i++) {
            char * fileName = argv[optind];
            if (*fileName == '-') {
            } //if
            int file = open(fileName, O_RDONLY);
            if (file == -1) perror("open");
            //set buffer to size c
            char buffer[c];
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
            //cycle through leftover arguments from optind to ensure not reading -n or -c as files
            char * fileName = argv[optind];
            if (*fileName == '-') {
                int * nP;
                *nP = n;
                linesStdIn(nP);
            }
            int file = open(fileName, O_RDONLY);
                if (file == -1) perror("open");
                //stores original read file
                char buffer[BUFFSIZE];
                //read file and print it until lines exceed n
                readFile = read(file, buffer, BUFFSIZE);
                if(readFile == -1) perror("read");
                int lineNum = 0, j = 0;
                //stores only bytes we want written
                char buffer2[BUFFSIZE];
                //read for new line characters and initialize everything up
                //to there into buff2 to be written
                for( j;  j < readFile && lineNum < n; j++) {
                    //copies buff 2 until line limit reached
                    buffer2[j] = buffer[j];
                    //check for new line characters
                    if(buffer[j] == '\n') {
                        lineNum++;
                    } //if
                } //for j
                //write only buffer2 with the specified number of lines
                write(STDOUT_FILENO, buffer2, readFile);
            } //for

        } //if n
} // main

void linesStdIn(int * nP)  {
    int n = *nP;
        int linesPrinted = 0, readFile = 0;
        char buffer[BUFFSIZE];
        char buffer2[BUFFSIZE];
        while(linesPrinted < n) {
            readFile = read(STDIN_FILENO, buffer, BUFFSIZE);
            int i = 0, lineCount = 0;
            for( i = 0; i < BUFFSIZE; i++) {
                //read lines from each standard input
                if(buffer[i] = '\n') {
                    lineCount++;
                } //if
                if(lineCount < n) {
                    buffer[i] = buffer2[i];
                } //if
                linesPrinted += lineCount;
            } //for
            write(STDOUT_FILENO, buffer, readFile);
         } //while
     } //linesStdIn

     void bytesStdIn() {
     } //bytesStdIn
