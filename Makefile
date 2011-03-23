CC=g++
CFLAGS=-Wall -ansi -O2

TARGET=ranker
HEADERS=rank.hpp ranksystem.hpp rankutils.hpp
SOURCES=main.cpp rank.cpp ranksystem.cpp rankutils.cpp

all:	$(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
