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
    int c, w, l;
    int indexOfFileNameStart = 1;
    //parse input
    /* needs to be fixxed to better parse file names*/
    while((opt = getopt(argc,argv, ":clw")) != -1) {
        switch (opt) {
        case 'c': {
            c = true;
            break;
        } //if
        case 'l':{
            l = true;
            break;
        } //if
        case 'w': {
            w = true;
            break;
        } //if
        case '?': {
            break;
        }
        } //switch
    } //while
    // printf("%ld", sizeof(fileNames));
    int j = 0;

    int totalC, totalL, totalW, i = 0;
    for ( i ; optind  < argc ; optind++,  i++) {
        printf("\n");
        char * fileName = argv[optind];
        //standard input
        if (*fileName == '-') {
            printf("standard input is not implemented yet :(");
        } //if
        int file = open(fileName, O_RDONLY);
        if (file == -1) perror("open");
        char buffer[BUFFSIZE];
        int readFile = read(file, buffer, BUFFSIZE);
        //print c specified
        if (c) {
        off_t size = lseek(file, 0, SEEK_END);
        printf("%ld ", size);
        //some condition to only add to total if more than 1 file name
        totalC += size;
        } //if c
        //print l if specified
        if (l) {
            int k = 0, lineNum = 0;
            for ( k ; k < readFile; k++) {
                if(buffer[k] == '\n') {
                    lineNum++;
                } //if
            } //for
            printf("%d ", lineNum);

            totalL += lineNum;
        } //if l
        //print w if specified
        if (w) {
            int k = 0, wordNum = 0;
            for ( k ; k < readFile; k++) {
                if(buffer[k] == ' ') {
                    wordNum++;
                } //if
            } //for
            printf("%d ", wordNum);

            totalW += wordNum;
        } //if w
        printf("%s", fileName);
    } //for
    //print totals
} //main
