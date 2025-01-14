// *****************************************************************************
// *                     Dynamic for a small sum of weights                    *
// *****************************************************************************
//
// This dynamic approach works best for a small total weight and for small
// individual weights.
// dp[i] = the maximum possible value of profit for weight i
//
// For each object we do exactly `maxWeight - weight` steps by maxing out all
// the possible "starting points" for our next objetcs. Basically we build up
// all the possible configurations through overlapping and choosing the best
// outcome through the formula:
// dp[j] = max(dp[j], dp[j - objects[i].weight] + objects[i].profit)

// Here all we do is say that for object i, the best profit for a total weight
// of j is achieved by choosing either the already existing profit (which means
// not picking the object) or by getting our profit for the
// j - objects[i].weight weight and adding our new profit (which means we pick
// this item).
//
// This algorithm also works for solving the problem online. The best answer
// will always be dp[maxWeight].
//
// Complexity:
// Time - O(n * maxWeight)
// Space - maxWeight
//
// Cons:
// This dynamic approach on weight is very sensitive to big weights and
// maxWeights, for both time and space wise.
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

long long DynamicForWeights(vector<Object>& objects) {
 	vector<long long> dp(maxWeight + 5, 0);
	for (long long i = 0; i < objects.size(); i++) {
		for (long long j = maxWeight; j >= objects[i].weight; j--) {
			dp[j] = max(dp[j], dp[j - objects[i].weight] + objects[i].profit);
		}
	}
	return dp[maxWeight];
}

int main(int argc, char** argv) {
	vector<Object> objects = ReadData(argv[1]);
	return DynamicForWeights(objects);
}
