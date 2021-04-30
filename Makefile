CFLAGS+= -mssse3 -g -O1 -Wall -Werror -std=c99
LIBS+= -lm
HW=spaceship
ZIP=zip

$(HW): gate.o main.c game.o spaceship.o
	$(CC) $(CFLAGS) main.c gate.o game.o spaceship.o -o $(HW) $(LIBS)

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c -o game.o

spaceship.o: spaceship.c spaceship.h
	$(CC) $(CFLAGS) -c spaceship.c -o spaceship.o


gate.o: gate.h gate.c
	$(CC) $(CFLAGS) -c gate.c -o gate.o

zip:
	$(ZIP) $(HW)-brute.zip main.c

clean:
	rm -f *.o

.PHONY: clean zip
