all: build run

build:
	gcc -o bin/app src/*.c

run:
	./bin/app