CXXFLAGS += -g
CC := g++

main : main.o App.o Csv.o
	$(CC) $(CXXFLAGS) $^ -o $@

App.o : App.cpp App.h

Csv.o : Csv.h Csv.cpp