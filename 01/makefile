CC=g++
CFLAGS=-g -std=c++11 -Wall

LIBS=-lGL -lGLU -lGLEW -lglut
INCLUDE = -I../include/

SOURCES=$(shell ls *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=main

all: compile run

compile: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $? -o $@ $()

clean:
	rm $(OBJECTS) $(EXEC)

optirun:
	optirun ./$(EXEC)

run:
	./$(EXEC)
