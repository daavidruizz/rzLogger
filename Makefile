# Makefile para rzLogger

CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS =

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
TARGET = rzLogger
INCLUDES = -Iinclude
CFLAGS += $(INCLUDES)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean