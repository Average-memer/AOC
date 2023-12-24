output: knapsack.o
	clear
	g++ knapsack.o -o knapsack

knapsack.o: knapsack.cpp
	clear
	g++ -c knapsack.cpp

debug: knapsack.cpp
	g++ knapsack.cpp -o knapsack -ggdb

clean:
	rm *.o knapsack