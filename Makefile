CC=gcc
CFLAGS= -g -Wall -Werror 
CPPFLAGS= `xml2-config --cflags`
LDFLAGS= `xml2-config --libs`
SDLFLAG= `sdl2-config --cflags --libs`

TARGET=street_map
HFILES=$(wildcard *.h)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)



all:$(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS) $(LDFLAGS) $(SDLFLAG)

%.o: %.c %.h
	$(CC) $(SRC) -o $(TARGET) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) $(SDLFLAG)