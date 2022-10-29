#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFSIZE 16
int main(int argc, char* argv[]) {
    int count;
    for( count = 0; count < argc; count++ )
        printf( "  argv[%d]   %s\n", count, argv[count] );
    int readFile;
     char buffer[BUFFSIZE];
     int c,n;
     int indexOfFileStart = 1;
    //parse values for c and n
     //check if
     char specifier[] = *argv[1];

     if(*specifier[1] == 'c') {
         char charC = *argv[2];
         c = (double)charC;
         indexOfFileStart = 3;
          printf("%c", charC);
     } else if( *specifier[1] == 'n') {
         char charN = *argv[2];
         n = (double)charN;
         indexOfFileStart = 3;
          printf("%c", charN);
     } else {
         n = 10;
             } //if

     int i = indexOfFileStart;
     //if any arguments are provided (i starts at 1)
     for( i ; i < argc; i++) {
         char * fileName = argv[i];
        int file = open(fileName, O_RDONLY);
        if (file == -1) perror("open");
        //if '-' provided as file name
        if(*fileName == '-') {

        //any other valid file name
       } else {
            //read from file at argv[i] and print it to standard output
            while((readFile = read(file, buffer, BUFFSIZE)) > 0) {
                write(STDOUT_FILENO, buffer, readFile);
            } //while
            if(readFile == -1) perror("read");
        } // if
     } //for
 } //main
