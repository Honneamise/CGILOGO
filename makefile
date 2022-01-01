CC 			= gcc
CFLAGS		= -Wall
LDFLAGS    	= -lm

all: clean logo

clean:
	rm -f *.bin

logo:
	$(CC) $(CFLAGS) PAGES/logo.c SRC/*.c $(LDFLAGS) -o $@.bin
