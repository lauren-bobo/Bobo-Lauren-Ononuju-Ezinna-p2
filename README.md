# Bobo-Lauren-Ononuju-Ezinna-p2
    Lauren Bobo (811232648)
    Ezinna Ononuju (811145142)

    Compilation:
            ~ To compile the code, use the | $ make | command. This will create an executabe for each asset of the project. Here is a list of all the executables:
    ./head
    ./tail
    ./wc
    ./env
    ./true
    ./false

        ~ To run the code, use the executable's name
        with a './' in front of it | $ ./env | true, false, and env require no further input, however head and tail do.
       - head and tail and wc:
            - if followed by no command line arguments or any instance of a '-', will do standard input functions similar to the linux functions with assumed -n 10 argument
            - if followed by |-c #| or |-n #|, the head tail functions will print # bytes for c and # lines for n
            - for wc, if followed by a -c it will count bytes, -l it will count lines, or -w it will count words.
            - if followed by any file name, functions will do the specified line word or byte function on that file.
        ~ To remove these  resultant executables, use the |$ make clean| commands to remove all of them at once

    Member Contributions:
    Lauren:
    - head function
    - tail function
    - .4 wc
    - .5 stdin on all functions
    - getopt on allfunctions
    - code commenting
    - makefile and readme
    - github
    - test scripts

    Ezi:
    - true
    - false
    - env
    - setbuf()
    - .6 wc
    - .5 stdin on all functions
    - code cleaning
    - debugging and error checking on all functions
    - testing and tweaking on all functions
    - github merge
