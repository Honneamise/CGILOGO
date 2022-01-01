CC 			= gcc
CFLAGS		= -Wall
LDFLAGS    	= -lm

all: clean logo share

clean:
	rm -f *.bin

logo:
	$(CC) $(CFLAGS) PAGES/logo.c SRC/*.c $(LDFLAGS) -o $@.bin

share:
	$(CC) $(CFLAGS) PAGES/share.c SRC/*.c $(LDFLAGS) -o $@.bin
