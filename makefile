CC=g++

CFLAGS=-g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -pedantic -lm
IMAGE_FLAGS=-lSDL2_image
MIXER_FLAGS=-lSDL2_mixer
FONTS_FLAGS=-lSDL2_ttf
SFLAGS=-lSDL2
SOURCES=main.cpp functions.cpp global.cpp
OBJECTS=main.o functions.o global.o
BINARIES=main

all: $(BINARIES)

main: main.o functions.o global.o
	$(CC) -o main main.o functions.o global.o $(CFLAGS) $(SFLAGS) $(IMAGE_FLAGS) $(MIXER_FLAGS) $(FONTS_FLAGS)

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS) $(SFLAGS) $(IMAGE_FLAGS) $(MIXER_FLAGS) $(FONTS_FLAGS)

funcoes.o: functions.cpp
	$(CC) -c functions.cpp $(CFLAGS) $(SFLAGS) $(IMAGE_FLAGS) $(MIXER_FLAGS) $(FONTS_FLAGS)

globais.o: global.cpp
	$(CC) -c global.cpp $(CFLAGS) $(SFLAGS) $(IMAGE_FLAGS) $(MIXER_FLAGS) $(FONTS_FLAGS)

clean:
	rm -rf *.o *.exe *.bak *.cpp~ $(BINARIES) core a.out
