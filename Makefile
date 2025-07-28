CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -g -Iinclude `pkg-config --cflags --libs gtk4`
BIN = nimedextract

all: build/sort.o build/write.o build/GUIcode.o build/GUI_init.o build/main.o
	$(CC) -o $(BIN) build/sort.o build/write.o build/GUIcode.o build/GUI_init.o build/main.o $(CFLAGS)

build/sort.o: src/sort.c include/sort.h
	mkdir -p build
	$(CC) -c src/sort.c -o build/sort.o $(CFLAGS)

build/write.o: src/write.c include/write.h
	mkdir -p build
	$(CC) -c src/write.c -o build/write.o $(CFLAGS)

build/GUIcode.o: src/GUIcode.c include/GUIcode.h
	mkdir -p build
	$(CC) -c src/GUIcode.c -o build/GUIcode.o $(CFLAGS)

build/GUI_init.o: src/GUI_init.c include/GUI_init.h
	mkdir -p build
	$(CC) -c src/GUI_init.c -o build/GUI_init.o $(CFLAGS)

build/main.o: src/main.c include/main.h
	mkdir -p build
	$(CC) -c src/main.c -o build/main.o $(CFLAGS)

.PHONY: clean
clean:
	rm -rf build $(BIN)
