CC=gcc
CFLAGS= -Wall -Wextra

all:
	$(CC) $(CFLAGS) autoshut.c -o autoshut
	
clean:
	rm autoshut
	
install: all
	install autoshut /usr/local/bin
