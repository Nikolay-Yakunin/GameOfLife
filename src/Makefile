CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = game_of_life
SRC = game_of_life.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

./bin/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) ./bin/$(TARGET)

.PHONY: all clean