CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = pseudo-shell
OBJS = main.o command.o string_parser.o

.PHONY: all clean valgrind

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c command.h string_parser.h
	$(CC) $(CFLAGS) -c main.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

string_parser.o: string_parser.c string_parser.h
	$(CC) $(CFLAGS) -c string_parser.c

clean:
	rm -f *.o $(TARGET) output.txt

valgrind: $(TARGET)
	valgrind ./$(TARGET)
