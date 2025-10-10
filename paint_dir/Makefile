paint.out: main.o input_validation.o set_up.o
	gcc -g -Wall -Werror -o paint.out main.o input_validation.o set_up.o

main.o: main.c set_up.h input_validation.h
	gcc -g -Wall -Werror -c main.c
	
set_up.o: set_up.c set_up.h input_validation.h
	gcc -g -Wall -Werror -c set_up.c

input_validation.o: input_validation.c input_validation.h
	gcc -g -Wall -Werror -c input_validation.c

clean:
	rm -fr *.o *.out
