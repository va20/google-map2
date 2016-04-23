CC=gcc
CFLAGS= -g -Wall -Werror 
CPPFLAGS= `xml2-config --cflags`
LDFLAGS= `xml2-config --libs`
SDLFLAG= `sdl2-config --cflags --libs` -lSDL2_gfx


TARGET=street_map
HFILES=$(wildcard *.h)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)



all:$(TARGET)


street_map:$(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS) $(LDFLAGS) -lm $(SDLFLAG)

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(CPPFLAGS) $(LDFLAGS) -lm $(SDLFLAG)