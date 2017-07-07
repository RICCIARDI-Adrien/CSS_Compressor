PATH_INCLUDES = Includes
PATH_SOURCES = Sources

CC = gcc
CCFLAGS = -W -Wall

BINARY = css-compressor
SOURCES = $(PATH_SOURCES)/Step_Remove_Comments.c $(PATH_SOURCES)/Step_Remove_Line_Feeds.c $(PATH_SOURCES)/Main.c

release: CCFLAGS += -DCSS_COMPRESSOR_IS_DEBUG_ENABLED=0
release: all

debug: CCFLAGS += -DCSS_COMPRESSOR_IS_DEBUG_ENABLED=1
debug: all

all:
	$(CC) $(CCFLAGS) $(SOURCES) -I$(PATH_INCLUDES) -o $(BINARY)

clean:
	rm -f $(BINARY)
