CC=g++
CFLAGS=-Wall -ansi -O2

TARGET=ranker
HEADERS=rank.h ranksystem.h
SOURCES=main.cpp rank.cpp ranksystem.cpp

all:	$(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
