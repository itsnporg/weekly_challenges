CXXFLAGS += -g
CC := g++

main : main.o App.o Csv.o helpers.o
	$(CC) $(CXXFLAGS) $^ -o $@

App.o : App.cpp App.h

Csv.o : Csv.h Csv.cpp

helpers.o : helpers.cpp helpers.h

PHONY : clean

clean : 
	rm -f *.o