CC=gcc
CFLAGS=-W -Wall -pedantic -std=c17
LDFLAGS=
EXEC=geoip
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

geoip: geoip.o validip.o ./validip/validip.h csv.o ./csv/csv.h ./csv/config.h
	@$(CC) -o $@ $^ $(LDFLAGS)

csv.o: ./csv/csv.c ./csv/csv.h ./csv/config.h
	@$(CC) -o $@ -c $< $(CFLAGS)

geoip.o: geoip.c
	@$(CC) -o $@ -c $< $(CFLAGS)

validip.o: ./validip/validip.c ./validip/validip.h
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o *.out

mrproper: clean
	@rm -rf $(EXEC)