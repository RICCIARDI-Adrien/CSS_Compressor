CC = gcc
CCFLAGS = -W -Wall

BINARY = css-compressor
SOURCES = CSS_Compressor.c

release: CCFLAGS += -DCSS_COMPRESSOR_IS_DEBUG_ENABLED=0
release: all

debug: CCFLAGS += -DCSS_COMPRESSOR_IS_DEBUG_ENABLED=1
debug: all

all:
	$(CC) $(CCFLAGS) $(SOURCES) -o $(BINARY)

clean:
	rm -f $(BINARY)
