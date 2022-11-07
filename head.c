#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>

#define true 1
#define false 0
#define BUFFSIZE 1048576


int main(int argc, char* argv[]) {
    int readFile = 0;
    int c = 0,n = 10;
    int byteNum = false,  lineNum = true;
    int opt;

    setbuf(stdout,NULL);
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
                /*FIX*/ //make perror
                fprintf(stderr, "%s: %s:invalid number of bytes\n", argv[0], argv[2]);
                return EXIT_SUCCESS;
            } else {
                c = atoi(optarg);
            } //if
            break;
        } //c
        } //switch
    } //while
    /* temporary */

    int i = 0;
    //print number of bytes
    if (byteNum) {

        //stdin case no args
        if (optind == argc) {
            char buffer[c];
            int bytesPrinted = c;
            while (bytesPrinted > 0) {
                readFile = read(STDIN_FILENO, buffer, bytesPrinted);
                write(STDOUT_FILENO, buffer, bytesPrinted);

                bytesPrinted = bytesPrinted - readFile;
            }//while
        } //if
        //start after command line arguments
        //loop through all provided file names
        for( i ; optind  < argc; optind++,  i++) {
            char * fileName = argv[optind];
            //set buffer to size c

            if (*fileName == '-') {
                char buffer[c];
                int bytesPrinted = c;
                while (bytesPrinted > 0) {
                    readFile = read(STDIN_FILENO, buffer, bytesPrinted);
                    write(STDOUT_FILENO, buffer, bytesPrinted);
                    bytesPrinted = bytesPrinted - readFile;
                } // while
            } else {

                char buffer[c];
                int file = open(fileName, O_RDONLY);
                if (file == -1)
                {
                    perror("open");
                    return EXIT_SUCCESS;
                } //if
                //read from file at argv[i] for only c bytes and print to std output
                readFile = read(file, buffer, c);
                 if(readFile == -1)
                {
                    perror("read");
                    return EXIT_SUCCESS;
                } //if
                printf("\n===>%s<===\n", fileName);
                write(STDOUT_FILENO, buffer, c);

                } //else
        } //for
    } //if


    // print num lines
    if (lineNum) {
        if (optind == argc) {
            int linesPrinted = 0;

            while (linesPrinted < n) {
                char buffer[BUFFSIZE];
                char buffer2[BUFFSIZE];

                int m = 0;
                readFile = read(STDIN_FILENO, buffer, BUFFSIZE);

                for (m; m < BUFFSIZE && linesPrinted < n ; m++) {
                    buffer2[m] = buffer[m];
                    if(buffer[m] == '\n') linesPrinted++;
                } //for
                 write(STDOUT_FILENO, buffer2, BUFFSIZE);

            } //while

        } //if
        for( i ; optind < argc; optind++, i++) {
            //cycle through leftover arguments from optind to ensure not reading -n or -c as files
            char * fileName = argv[optind];

            if (*fileName == '-') {
                int linesPrinted = 0;

                while (linesPrinted < n) {
                    char buffer[BUFFSIZE];
                    char buffer2[BUFFSIZE];

                    int m = 0;
                    readFile = read(STDIN_FILENO, buffer, BUFFSIZE);
                    for (m; m < BUFFSIZE && linesPrinted < n ; m++) {
                        buffer2[m] = buffer[m];
                        if(buffer[m] == '\n') linesPrinted++;
                    } //for
                     write(STDOUT_FILENO, buffer2, BUFFSIZE);
                } //while

            } else {
                int file = open(fileName, O_RDONLY);

                if (file == -1) {
                    perror("open");
                    return EXIT_SUCCESS;
                } //if
                //stores original read file
                char buffer[BUFFSIZE];
                //read file and print it until lines exceed n
                readFile = read(file, buffer, BUFFSIZE);
                if(readFile == -1) {
                    perror("read");
                    return EXIT_SUCCESS;
                } //if
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
                printf("\n===>%s<===\n", fileName);
                //write only buffer2 with the specified number of lines
                write(STDOUT_FILENO, buffer2, readFile);

            } //else

        } //for

    } //if n
} // main
