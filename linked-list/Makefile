build:
	clang -g -o bin/ll linked_list.c
run: build
	./bin/ll
leaks: build
	leaks --atExit -- ./bin/ll
