.PHONY: clean

src/main: test/ut_main.cpp src/ut_shape.h src/ut_sort.h src/circle.h src/rectangle.h src/triangle.h src/shape.h src/sort.h src/main.cpp
		g++ -std=c++11 src/main.cpp -o bin/hw3 -lgtest -lpthread

clean:
		rm hw3
