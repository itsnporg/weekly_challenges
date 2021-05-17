CC=clang++
CFLAGS=-Wall -Wextra

all: main

main: main.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf main

run: clean all
	clear
	./main data.csv
