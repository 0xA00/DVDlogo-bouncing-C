CXX = gcc
SRC = Wsnake.c

build:
	$(CXX) -o Wsnake $(SRC) -lncurses


run: build
	./Wsnake

