all: geometry


geometry: main.o circle.o
	gcc -Wall -Werror build/src/main.o build/src/circle.o -o bin/geometry
main.o: src/main.c
	gcc -Wall -Werror -c src/main.c -o build/src/main.o
circle.o: src/circle.c
	gcc -Wall -Werror -c src/circle.c -o build/src/circle.o


test: bin/geometry_test

bin/geometry_test: build/test/main.o build/test/functions.o
	gcc -Wall -Werror build/test/main.o build/test/functions.o -o bin/geometry_test -lm

build/test/main.o: test/main.c
	gcc -Wall -Werror -c -I thirdparty -I src test/main.c -o build/test/main.o

build/test/functions.o: src/functions.c src/functions.h
	gcc -Wall -Werror -c -I thirdparty -I src src/functions.c -o build/test/functions.o



.PHONY: clean

clean:
	rm -rf build/src/*.o bin/geometry
	rm -rf build/test/*.o bin/test