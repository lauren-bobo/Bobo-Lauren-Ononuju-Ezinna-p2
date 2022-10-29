#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>


int main(int argc, char* argv[]) {

    while((opt = getopt(argc,argv, ":clw")) != -1) {
        if (opt == 'c') {
        } //if
        if (opt == 'l') {
        } //if
        if (opt == 'w') {
        } //if
    } //while
} //main
