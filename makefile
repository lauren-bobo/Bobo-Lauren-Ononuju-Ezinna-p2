NAME = lab03
FLAGS = -Wall -pedantic-errors

cl: main.o arrayutil.o
	gcc -o $(NAME) main.o arrayutil.o

main.o: main.c arrayutil.h
	gcc -c $(FLAGS) main.c

arrayutil.o: arrayutil.h arrayutil.c
	gcc -c $(FLAGS) arrayutil.c

run: cl
	./$(NAME)

clean:
	rm -f $(NAME) *.o
