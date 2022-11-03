#!/bin/bash -x

echo"basic functionality"
echo "format: \n
.\mine
\n unix"

./head file1.txt
head file1.txt

./head file1.txt file2.txt
head file1.txt file2.txt

./head -n 5 file1.txt
head -n 5 file1.txt

./head -n 5 file1.txt file2.txt
head -n 5 file1.txt file2.txt

./head -c 3 file1.txt
head -c 3 file1.txt

./head -c 3 file1.txt file2.txt
head -c 3 file1.txt file2.txt

./tail file1.txt
tail file1.txt

./tail file1.txt file2.txt
tail file1.txt file2.txt

./tail -n 5 file1.txt
tail -n 5 file1.txt

./tail -n 5 file1.txt file2.txt
tail -n 5 file1.txt file2.txt

./tail -c 3 file1.txt
tail -c 3 file1.txt

./tail -c 3 file1.txt file2.txt
tail -c 3 file1.txt file2.txt

./wc file1.txt
wc file1.txt

./wc file1.txt file2.txt
wc file1.txt file2.txt

./wc -c file1.txt file2.txt
wc -c file1.txt file2.txt

./wc -lc file1.txt file2.txt
wc -lc file1.txt file2.txt

./wc -cl file1.txt file2.txt
wc -cl file1.txt file2.txt

./wc -cwl file1.txt file2.txt
wc -cwl file1.txt file2.txt

./wc -w -l file1.txt file2.txt
wc -w -l file1.txt file2.txt

./wc -l -cw file1.txt file2.txt
wc -l -cw file1.txt file2.txt

./true
true

./false
false

 ./env
 env
