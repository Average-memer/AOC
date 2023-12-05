#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <iterator>
#include <array>
#include <math.h>
#include <numeric>

using std::vector;
using std::string;
using std::size_t;
using std::cout, std::endl;


template <typename T>
void printVector(const vector<T>& vec, bool newline, char seperator){
	for (auto item : vec)
	{
		std::cout << item << seperator;
	}
	if (newline)
	{
		std::cout << std::endl; 
	}	
}

vector<string> readLines(){
	std::ifstream file("input");
	string line;
	vector<string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

int main(int argc, char const *argv[])
{
	std::cout << "Merry Crisis";
	return 0;
}
