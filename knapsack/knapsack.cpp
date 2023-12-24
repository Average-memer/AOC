#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <experimental/random>
#include <random>
#include <limits>
#include <tuple>
#include <vector>
#include <algorithm>

using std::int32_t;


const int POPULATION_SIZE = 32;


//This is an implementation of a genetic algorithm supposed to solver the knapsack problem
//each candidate will be a 16 bit long char? where each byte represents wether an item is in the knapsack or not.
//the optimal solution includes the subset of items with the highest value which still fits into the weight budget.
//each item will be a struct 
struct item
{
	float value;
	float weight;
};

const item ITEMS[] = {{4.9, 7.0},
					{4.0, 7.6},
					{12.4, 0.4},
					{4.5, 4.3},
					{10.6, 5.4},
					{12.6, 8.5},
					{9.6, 1.0},
					{13.8, 8.3},
					{10.7, 0.6},
					{11.7, 9.0},
					{7.2, 4.1},
					{1.6, 1.6},
					{8.5, 1.0},
					{2.1, 5.4},
					{4.5, 2.3},
					{3.7, 1.8},
					{6.9, 0.2},
					{10.3, 6.8},
					{5.0, 9.2},
					{10.9, 0.3},
					{1.2, 3.1},
					{13.6, 0.3},
					{13.1, 6.8},
					{9.0, 6.9},
					{7.9, 1.4},
					{5.8, 8.9},
					{12.9, 4.0},
					{14.8, 1.8},
					{14.5, 9.1},
					{3.2, 3.6},
					{5.2, 3.8},
					{12.7, 5.4}};

int32_t* randomizePopulation(size_t size){
	int32_t* pop = new int32_t[size];
	//initialize RNG
	static std::random_device rd;
	static std::mt19937 gen(rd());	
	std::uniform_int_distribution<int32_t> dis(std::numeric_limits<int32_t>::min(),
                                               std::numeric_limits<int32_t>::max());

	//loop through all members of the population and assign them an int32_t, effectively randomizing their bits.
	for (int i = 0; i < POPULATION_SIZE; ++i)
	{
		pop[i] = dis(gen);
	}
	return pop;
}

//check wether a certain bit is positive
inline bool bit_check(int number, int n) {
    return (number >> n) & (int)1;
}


int mutate(int subject, int fitness){
	//mutate a specimen by inverting a randomly chosen bit
	//mutation chance is dependant on fitness, with a lower fitness leading to more mutations
	//this will introduce entropy and allow more optimal solutions to form
	double probability = 10/(double)fitness;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<>dis(0., 1.);

	double draw = dis(gen);
	if (probability >= draw)
	{
		int position = std::experimental::randint(0, 31);
		//std::cout << position << std::endl;
		subject ^= ((int)1 << position);
	}

	return subject;
}

//calculate the fitness of a given member of the population.
int betterFitness(int32_t configuration, const item master[]){
	int fitness = 0;
	double capacity = 70.;
	double total_weight = 0;
	double total_value = 0;

	for (int i = 0; i < 32; ++i)
	{
		if (bit_check(configuration, i))
		{
			total_weight += master[i].weight;
			total_value += master[i].value;
		}	
	}

	//if our weight exceeds the capacity the chosen configuration is invalid and thus not fit for evolution
	if (total_weight > capacity)
	{
		return fitness = -100;
	}
	
	//we want to maximize value while penalizing empty space
	//subject to change
	fitness = 2*total_value - (capacity - total_weight);	
	return fitness;
}

//"mix" the genes of the parents to create a new, hopefully better, configuration
int32_t crossover(int32_t parent_a, int32_t parent_b){
	//we slice both parents in half at a random point and combine the opposite halves into a new genotype
	//int mask = 0x00000000;
	//initialize RNG
	static std::random_device rd;
	static std::mt19937 gen(rd());	
	static std::uniform_int_distribution<>dis(0, 31);

	int offset = dis(gen);
	int32_t mask = (1 << offset) - 1;

	parent_a |= mask;
	parent_b |= !mask;
	return parent_b & parent_a;
}

void printBits(int32_t genotype){
	std::cout << std::bitset<sizeof(int)*8>(genotype) << " ";
}

//evaluate all members of a population and put them in a list.
//we then sort the list based on performance.
std::vector<std::tuple<int, int32_t>> evaluatePopulation(int32_t pop[]) {
	//we store the genotype in the first slot and its fitness int the second slot
    std::vector<std::tuple<int32_t, int>> result;

    //we also calculate the average score of a population  to see if we are actually getting better
    float average = 0;

    //loop over the population, calculate the fitness and store.
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        // Create a tuple and add it to the vector
        int fitness = betterFitness(pop[i], ITEMS);
        average += (fitness != -100) ? fitness : 0;
        result.push_back(std::make_tuple(pop[i], fitness));
    }

    //sort the result to find the best performers
    //first define a custom comparision function:
    //it will sort my genotypes based on their fitness, which is stored in slot 1.
    auto comparator = [](const auto& a, const auto& b) {
        return std::get<1>(a) > std::get<1>(b);
    };

    std::sort(result.begin(), result.end(), comparator);
    average /= POPULATION_SIZE;
    std::cout << "Average performance of valid configurations: " << average << std::endl;

    return result;
}

int main(int argc, char const *argv[])
{
	//initialize RNG
	std::srand(std::time(nullptr));
	static std::random_device rd;

	//initialize Population
	int size = POPULATION_SIZE;
	int32_t* population = randomizePopulation(size);


	auto eval = evaluatePopulation(population);
	for (const auto& element : eval) {
        std::cout << std::get<1>(element) << " ";
    }
	return 0;

	//TODO: -create next generation based on previous best candidates.
}