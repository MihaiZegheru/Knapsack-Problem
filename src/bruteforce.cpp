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

int N, G;
long long bestAns;
vector<int> bestChoice;

vector<Object> ReadData(char* fileName) {
	ifstream fin(fileName);

  fin >> N >> G
;
	vector<Object> objects(N + 1);
  for (int i = 1; i <= N; i++) {
    fin >> objects[i].weight;
    fin >> objects[i].profit;
  }

	fin.close();
	return objects;
}

long long RecursiveBruteForce(int n, int g, vector<Object>& objects, Object aggregate,
		long long index, vector<int>& out, vector<int>& current) {
	if (index >= objects.size()) {
		if (aggregate.profit > bestAns) {
			bestAns = aggregate.profit;
			out.resize(current.size());
			for (int i = 0; i < current.size(); i++) {
				out[i] = current[i];
			}
		}
		return aggregate.profit;
	}

	Object newAggregate = {
		aggregate.weight + objects[index].weight,
		aggregate.profit + objects[index].profit
	};

	long long profit;
	long long forAdded = INT64_MIN;;
	long long forIgnored = RecursiveBruteForce(n, g, objects, aggregate, index + 1, out, current);
	if (newAggregate.weight <= G) {
		current.push_back(index);
		forAdded = RecursiveBruteForce(n, g, objects, newAggregate, index + 1, out, current);
		current.pop_back();
	}
	if (forAdded > forIgnored) {
		profit = forAdded;
	} else {
		profit = forIgnored;
	}
	return profit;
}

long long BruteForce(int n, int g, vector<Object>& objects, vector<int>& out) {
	vector<int> current;
	return RecursiveBruteForce(n, g, objects, {0, 0}, 0, out, current);
}

int main(int argc, char** argv) {
	vector<Object> objects = ReadData(argv[1]);
	vector<int> items;
	return BruteForce(N, G, objects, items);
}
