main:
	g++ -g -c seegee.cpp
	ar rvs seegee.a seegee.o
	g++ -g test.cpp seegee.a -o test -lGL -lGLEW -lglfw

run:
	./test
