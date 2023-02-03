SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: exec

%.o : %.c header.h
	gcc -c $< -o $@

exec: $(OBJ)
	gcc $^ -o $@

clean :
	rm -f *.o
	rm -f *.txt
	rm exec
