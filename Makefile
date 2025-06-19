CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -I include
TARGET=yeep
SRCDIR=src
INCDIR=include
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

test:
	./$(TARGET) examples/test.yeep

.PHONY: all clean install test
