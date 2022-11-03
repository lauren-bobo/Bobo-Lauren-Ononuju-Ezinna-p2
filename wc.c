#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

#define true 1
#define false 0
#define BUFFSIZE 1048576
int main(int argc, char* argv[]) {
    int opt;
    int c = false, w = false, l = false;
    int indexOfFileNameStart = 1;
    //parse input
    /* needs to be fixxed to better parse file names*/
    while((opt = getopt(argc,argv, "+clw")) != -1) {
        switch (opt) {
        case 'c':
            c = true;
            break;
        case 'l':
            l = true;
            break;
        case 'w':
            w = true;
            break;
        } //switch
    } //while
    if (c == false && w == false && l == false) {
            c = true;
            w = true;
            l = true;
    } // if

    printf("\n");

    int totalC = 0, totalL = 0, totalW = 0, i = 0, printTotals= false;
    for ( i ; optind  < argc ; optind++,  i++) {

        if (i >= 1) {
            printTotals = true;
        } //if
        int file;
        char * fileName = argv[optind];
        //standard input
        if (*fileName == '-') {
            file = STDIN_FILENO;

        } else {
            file = open(fileName, O_RDONLY);

        } // if

        if (file == -1) {
                perror("open");
                return 1;
        } // if

        char buffer[BUFFSIZE];

        int readFile;

        if (*fileName == '-') {
            int lineNum = 0;
            int wordNum = 0;
            int size = 0;

            while ((readFile = read(file, buffer, BUFFSIZE)) > 0) {

                //print l (number of newlines) if specified
                if (l == 1) {
                        int k = 0;
                        for ( k ; k < readFile; k++) {
                                if(buffer[k] == '\n') {
                                        lineNum++;
                                } //if
                        } //for
                } //if l

                //print w (number of words) if specified
                if (w == 1) {
                        int k = 0;
                        for ( k ; k < readFile; k++) {
                                if(buffer[k] == ' ' ||
                                buffer[k] == '\n' ||
                                buffer[k] == '\t' ||
                                buffer[k] == '\r' ||
                                buffer[k] == '\v' ||
                                buffer[k] == '\f' ||
                                buffer[k] == '\0') {
                                        wordNum++;
                                } //if
                        } //for

                } //if w

                //print c (number of bytes) if specified
                if (c == 1) {
                        size += readFile;
                } //if c

            } // while

            printf("\t%d ", lineNum);
            totalL += lineNum;

            printf("\t%d ", wordNum);
            totalW += wordNum;

            printf("\t%ld ", size);
            totalC += size;

            printf("\t%s\n", fileName);

        } else {
            readFile = read(file, buffer, BUFFSIZE);

            //print l (number of newlines) if specified
            if (l == 1) {
                    int k = 0, lineNum = 0;
                    for ( k ; k < readFile; k++) {
                            if(buffer[k] == '\n') {
                                    lineNum++;
                            } //if
                    } //for
                    printf("\t%d ", lineNum);
                    totalL += lineNum;
            } //if l

            //print w (number of words) if specified
            if (w == 1) {
                    int k = 0, wordNum = 0;
                    for ( k ; k < readFile; k++) {
                        if((!(buffer[k] == ' ' ||
                            buffer[k] == '\n' ||
                            buffer[k] == '\t' ||
                            buffer[k] == '\r' ||
                            buffer[k] == '\v' ||
                            buffer[k] == '\f' ||
                        buffer[k] == '\0') )
                        && (buffer[k-1] == ' ' ||
                            buffer[k-1] == '\n' ||
                            buffer[k-1] == '\t' ||
                            buffer[k-1] == '\r' ||
                            buffer[k-1] == '\v' ||
                            buffer[k-1] == '\f' ||
                        buffer[k-1] == '\0')  ){
                                    wordNum++;
                            } //if
                    } //for
                    printf("\t%d ", wordNum);

                    totalW += wordNum;

            } //if w

            //print c (number of bytes) if specified
            if (c == 1) {
                    if (file == STDIN_FILENO) {
                            int size = readFile;
                            printf("\t%d ", size);
                            totalC += size;

                    } else {
                            off_t size = lseek(file, 0, SEEK_END);
                            printf("\t%ld ", size);
                            totalC += size;

                    } // else
            } //if c

            printf("\t%s\n", fileName);

        } // if

    } //for

    if (printTotals) {
        if(l) {
            printf("\t%d ", totalL);
        } //if l
        if(w) {
            printf("\t%d ", totalW);
        } // if
        if(c) {
            printf("\t%d ", totalC) ;
        } //if c
        printf("\ttotal\n");
    } //if
} //main
