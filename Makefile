CC = gcc
CCFLAGS = -W -Wall

BINARY = css-compressor
SOURCES = CSS_Compressor.c

all:
	$(CC) $(CCFLAGS) $(SOURCES) -o $(BINARY)

clean:
	rm -f $(BINARY)
