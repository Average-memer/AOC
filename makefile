output: day1.o
	clear
	g++ day1.o -o day1

day1.o: day1.cpp
	clear
	g++ -c day1.cpp

debug: day1.cpp
	g++ day1.cpp -o day1 -ggdb

clean:
	rm *.o day1