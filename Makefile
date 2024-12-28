cc := gcc

build:
	$(cc) src/main.c -I/opt/homebrew/Cellar/raylib/5.5/include -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib -Wall -Wextra -O3 -o bin/editor.exe
