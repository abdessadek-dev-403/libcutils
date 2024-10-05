CC = gcc

CFLAGS = -Wall -Iinclude

SRC = $(wildcard src/*.c)

HEADER = $(wildcard include/*.h)

OBJ = $(patsubst src/%.c, bin/%.o, $(SRC))

TARGET = libcutils.a

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $^

bin/%.o: src/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean