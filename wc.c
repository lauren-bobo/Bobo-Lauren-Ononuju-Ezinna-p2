#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

#define true 1
#define false 0
#define BUFFSIZE 514
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
    } //if
    // printf("%ld", sizeof(fileNames));
    printf("\n");
    int totalC = 0, totalL = 0, totalW = 0, i = 0, printTotals= false;
    for ( i ; optind  < argc ; optind++,  i++) {
        //printf("%s", argv[optind]);
        if (i >= 1) {
            printTotals = true;
        } //if
        int file;
        char * fileName = argv[optind];

        //standard input
        if (*fileName == '-') {
            file = STDIN_FILENO;
            //printf("standard input is not implemented yet :(");
        } else {
             file = open(fileName, O_RDONLY);

        } //// if

        if (file == -1) perror("open");
        char buffer[BUFFSIZE];

        int readFile = read(file, buffer, BUFFSIZE);

        //print c (number of bytes) if specified
        if (c) {
            off_t size = lseek(file, 0, SEEK_END);
            printf("%ld ", size);
            //some condition to only add to total if more than 1 file name
            totalC = totalC + size;
        } //if c

        //print l (number of newlines) if specified
        if (l) {
            int k = 0, lineNum = 0;
            for ( k ; k < readFile; k++) {
                if(buffer[k] == '\n') {
                    lineNum++;
                } //if
            } //for
            printf("%d ", lineNum);
            totalL = totalL + lineNum;
        } //if l

        //print w (number of words) if specified
        if (w) {
            int k = 0, wordNum = 0;
            for ( k ; k < readFile; k++) {
                if(buffer[k] == ' ' ||
                    buffer[k] == '\n' ||
                    buffer[k] == '\t' ||
                    buffer[k] == '\r' ||
                    buffer[k] == '\v' ||
                    buffer[k] == '\f') {
                    wordNum++;
                } //if
            } //for
            printf("%d ", wordNum);

            totalW = totalW + wordNum;

        } //if w
        printf("%s\n", fileName);
    } //for

    if (printTotals) {
        if(c) {
            printf("%d ", totalC) ;
        } //if c
        if(l) {
            printf("%d ", totalL);
        } //if l
        if(w) {
            printf("%d ", totalW);
        } // if
        printf("total\n");
    } //if
} //main
