.PHONY: clean

test/ut_main: test/ut_main.cpp src/ut_shape.h src/ut_sort.h src/circle.h src/rectangle.h src/triangle.h src/shape.h src/sort.h
		g++ -std=c++11 test/ut_main.cpp -o bin/hw2 -lgtest -lpthread

clean:
		rm bin/hw2
