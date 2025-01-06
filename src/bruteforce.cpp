// *****************************************************************************
// *                               Brute Force                                 *
// *****************************************************************************
//
// Brute force is solved quite intuitively. For each object we choose wether
// to pick it or not. This of course gives us a complexity of 2^n. In order
// to optimise this a bit and cut off the branches whenever we are sure that
// they are going to lead to a fail we check for the weight if it has surpassed
// the maximum weight.
//
// For a small number of objects this could be optimised into a dynamic on
// configurations.
//
// Complexity:
// Time - O(2^n)
// Space - n : since it basically is a DFS 
//
// Cons:
// This brute force is very sensitive to the maximum weight value. In this
// approach we filter whenever the current weight surpasses the maximum weight.
// Not to mention the insane exponantial time.
//
// *****************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

struct Object {
    long long weight;
    long long profit;
};

int maxWeight;

vector<Object> ReadData(char* fileName) {
	ifstream fin(fileName);

	int n;
  fin >> n >> maxWeight;
	vector<Object> objects(n);
  for (int i = 0; i < n; i++) {
    fin >> objects[i].weight;
    fin >> objects[i].profit;
  }

	fin.close();
	return objects;
}

long long RecursiveBruteForce(vector<Object>& objects, Object aggregate,
		long long index) {
	if (index >= objects.size()) {
		return aggregate.profit;
	}

	Object newAggregate = {
		aggregate.weight + objects[index].weight,
		aggregate.profit + objects[index].profit
	};

	long long profit = INT64_MIN;
	if (newAggregate.weight <= maxWeight) {
		profit = RecursiveBruteForce(objects, newAggregate, index + 1);
	}
	return max(profit, RecursiveBruteForce(objects, aggregate, index + 1));
}

long long BruteForce(vector<Object>& objects) {
	return RecursiveBruteForce(objects, {0, 0}, 0);
}

int main(int argc, char** argv) {
	vector<Object> objects = ReadData(argv[1]);
	BruteForce(objects);
	return 0;
}
