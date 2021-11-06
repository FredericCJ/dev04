CC=gcc
CFLAGS=-W -Wall -pedantic -std=c17
LDFLAGS=-g
EXEC=geoip
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

geoip: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.h

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o *.out

mrproper: clean
	@rm -rf $(EXEC)