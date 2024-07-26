MAKEFLAGS += --no-print-directory --always-make
COMPILER = g++

LINK_SFML_LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all:
	make main

main: main.cpp
	$(COMPILER) -c main.cpp
	$(COMPILER) -o main main.o $(LINK_SFML_LIBS)

clear:
	rm *.o

