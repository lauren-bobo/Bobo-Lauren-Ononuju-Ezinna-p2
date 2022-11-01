#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include<errno.h>

#define BUFFSIZE 514
#define true 1
#define false 0

int main(int argc, char * argv[]) {
    int readFile = 0;
    int c= 0,n = 10;
    int byteNum = false, lineNum = true;
    int opt;
    while((opt = getopt(argc,argv, ":n:c:")) != -1) {

        switch(opt) {

        case 'n': {
             //ensure non-negative input
            if (!(atoi(optarg)>0)) {
                fprintf(stderr, "%s: %s: invalid number of lines\n", argv[0], argv[2]);
                return EXIT_SUCCESS;
            } else {
                n = atoi(optarg);
            } //if
            break;
        } //case n
        case 'c': {
            lineNum = false;
            byteNum = true;
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
            //throwing error if target not present
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
            break;
        } //case c
        } //switch
    } //while

    //print number of bytes
    if (byteNum) {
        int i = 0;
        //loop through all provided file names in optind
        for( i ; optind < argc; optind++, i++) {
            char * fileName = argv[optind];
            int file = open(fileName, O_RDONLY);
            //set buffer to size c
            char buffer[c];
            //find size of entire file n bytes
            off_t size = lseek(file, 0, SEEK_END);
            //make a starting point for the function that is c bytes
            //away from the end of the file
            off_t startingPoint =  size - c;
            //set the file's offset to that new starting point
            lseek(file, startingPoint, SEEK_SET);
            if (size == -1) perror("lseek");
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
            int i = 0;
            for( i ; optind < argc; optind++, i++) {
                char * fileName = argv[optind];
                int file = open(fileName, O_RDONLY);
                if (file == -1) perror("open");
                char buffer[BUFFSIZE];
                //read file and print it until lines exceed n
                readFile = read(file, buffer, BUFFSIZE);
                if(readFile == -1) perror("read");
                int lineNum = 0;
                int k = 0;
                int j = 0;
                //count total number of lines in file
                for ( k ; k < readFile; k++) {
                    if(buffer[k] == '\n') {
                        lineNum++;
                    } //if
                } //for
                //start the translation at the end line minus the number of
                //lines to print
                int startPoint = lineNum - n;
                //make a copy to transfer lines to write
                char buffer2[BUFFSIZE];
                //read for new line characters and initialize everything up
                //to there into buff2 to be read
                lineNum = 0;
                //starts copying at starting point in file
                //(could probably make j equal to starting point but
                for( j; j < readFile; j++) {
                    if (lineNum >= startPoint) {
                        buffer2[j] = buffer[j];
                    } //if
                    if (buffer[j] == '\n') {
                        lineNum++;
                        }//if
                } //for j
                //write only buffer2 with the specified number of lines
                write(STDOUT_FILENO, buffer2, readFile);
            } //for

        } //if n
} //main
