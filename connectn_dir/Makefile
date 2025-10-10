CC = emcc
CFLAGS = -g -Wall -Werror
OUT = ../static/connectn.js
RM = del /Q

$(OUT): input_validation.o main.o play_game.o set_up_game.o
	$(CC) $(CFLAGS) -o $(OUT) input_validation.o main.o play_game.o set_up_game.o\
	    -s EXPORTED_FUNCTIONS='["_main"]' \
	    -s EXPORTED_RUNTIME_METHODS='["cwrap","ccall"]' \
	    -s FORCE_FILESYSTEM=1 \
		-s EXIT_RUNTIME=1 \
		-s ALLOW_MEMORY_GROWTH=1

main.o: main.c set_up_game.h play_game.h
	$(CC) $(CFLAGS) -c main.c

input_validation.o: input_validation.c input_validation.h
	$(CC) $(CFLAGS) -c input_validation.c

play_game.o: play_game.c play_game.h input_validation.h
	$(CC) $(CFLAGS) -c play_game.c

set_up_game.o: set_up_game.c set_up_game.h
	$(CC) $(CFLAGS) -c set_up_game.c	
	
clean:
	-$(RM) *.o *.out ..\static\connectn.js ..\static\connectn.wasm