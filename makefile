objects = head tail wc true false env
all: $(objects)
FLAGS = -Wall -pedantic-errors

cl: $(objects).c
	gcc -o $(objects) $(FLAGS) $(objects).c

run: cl
	./$(objects)

clean:
	rm -f $(objects)
