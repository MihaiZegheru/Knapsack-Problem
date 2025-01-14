// *****************************************************************************
// *                     Dynamic for a small sum of weights                    *
// *****************************************************************************
//
// This dynamic approach works best for a small total weight and for small
// individual weights.
// dp[i] = the maximum possible value of profit for weight i
//
// For each object we do exactly `G - weight` steps by maxing out all
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
// will always be dp[G].
//
// Complexity:
// Time - O(n * G)
// Space - G
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

int N, G;

vector<Object> ReadData(char* fileName) {
	ifstream fin(fileName);

  fin >> N >> G;
	vector<Object> objects(N + 1);
  for (int i = 1; i <= N; i++) {
    fin >> objects[i].weight;
    fin >> objects[i].profit;
  }

	fin.close();
	return objects;
}

long long DynamicForWeights(int n, int g, vector<Object>& objects,
		vector<int>& out) {
 	vector<vector<long long>> dp(n + 1, vector<long long>(g + 1));
	for (long long i = 1; i <= n; ++i) {
		for (long long j = 1; j <= g; ++j) {
			dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			if (j >= objects[i].weight) {
				dp[i][j] = max(dp[i][j],
						dp[i - 1][j - objects[i].weight] + objects[i].profit);
			}
		}
	}

	// Build solution
	for (long long i = n; i >= 1; --i) {
		if (dp[i][g] == dp[i - 1][g]) {
			continue;
		}
		out.push_back(i - 1);
	}
	return dp[n][g];
}

int main(int argc, char** argv) {
	vector<Object> objects = ReadData(argv[1]);
	vector<int> items;
	return DynamicForWeights(N, G, objects, items);
}
