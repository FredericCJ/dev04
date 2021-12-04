CC=gcc
CFLAGS=-W -Wall -pedantic -std=c17 -g
LDFLAGS=-g
EXEC=geoip
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

geoip: geoip.o validip.o csv.o
	@$(CC) -o $@ $^ $(LDFLAGS)

csv.o: csv.c
	@$(CC) -o $@ -c $< $(CFLAGS)

geoip.o: geoip.c
	@$(CC) -o $@ -c $< $(CFLAGS)

validip.o: validip.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o *.out *.gch

mrproper: clean
	@rm -rf $(EXEC)