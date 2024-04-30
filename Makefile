cc := gcc

build:
	$(cc) src/main.c -Lbin -lraylib -Wall -Wextra -O3 -o bin/editor.exe
