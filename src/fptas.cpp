// *****************************************************************************
// *                 Fully polynomial time approximation scheme                *
// *****************************************************************************
//
// This approach makes use of the Dynamic on profits approach, but it first
// compresses the profits. This results in a loss of precision denoted by:
// approximated_profit >= (1 - eps) * optimal_profit
// eps is a variable (0, 1] that we can pick based on the dataset that we have
// and some internally developed heursistics.
//
// Intuitively, we need to make some kind of scaling factor K for upper
// bounding the profits by scaling them, therefore increasing efficiency both in
// space and time. Lets say that we kind of normalise the profits by taking the
// maximum profit and dividing it by the number of objects. Then, by multiplying
// the result with eps we specify its contribution (keep in mind that this is
// an inverse contribution because of the next step).
// Now we have our scaling factor K = eps * biggestProfit / n
//
// Further we want to scale all our objects with the inverse of K.
// So vi' = [vi / K], where we take the integer part since our actual processing
// algorithm takes ints (Dynamic on profits). We then pass these new objects
// with scaled profits to our algorithm and multiply the result with K,
// reversing the scaling.
//
// The computed solution is correct within of factor of (1 - eps) of the best
// solution.
//
// Complexity:
// Time - O(n + n * maxProfit / K), where K = eps * biggestProfit / n, so the time
// complexity becomes O(n + maxProfit / (eps * biggestProfit))
// Space - O(maxProfit / (eps * biggestProfit))
//
// Cons:
// This is just an approximation and can vary quite drasticly for outliers.
//
// Algorithm from (Wikipedia)[https://en.wikipedia.org/wiki/Knapsack_problem#Fully_polynomial_time_approximation_scheme]
//
// *****************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdlib.h>
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

long long DynamicForProfits(int n, int g, vector<Object>& objects, vector<int>& out) {
	long long maxProfitSum = 0;
	for (long long i = 0; i < objects.size(); i++) {
		maxProfitSum = max(maxProfitSum, maxProfitSum + objects[i].profit);
	}
 	vector<vector<long long>> dp(n + 1, vector<long long>(maxProfitSum + 1, INT64_MAX - g));
	dp[0][0] = 0;

	for (long long i = 1; i <= n; ++i) {
		for (long long j = 0; j <= maxProfitSum; ++j) {
			dp[i][j] = dp[i - 1][j];
			if (j < objects[i].profit) {
				continue;
			}
			dp[i][j] = min(dp[i][j], dp[i - 1][j - objects[i].profit] + objects[i].weight);
		}
	}

	long long ans;
	for (ans = maxProfitSum; ans >= 0; --ans) {
		if (dp[n][ans] <= G) {
			break;
		}
	}

	// Build solution
	long long searchAns = ans;
	for (long long i = n; i >= 1; --i) {
		if (dp[i][searchAns] == dp[i - 1][searchAns]) {
			continue;
		}
		out.push_back(i - 1);
		searchAns -= objects[i].profit;
	}
	return ans;
}

long long FPTAS(int n, int g, vector<Object>& objects, double eps, vector<int>& out) {
	long long maxProfit = 0;
	for (int i = 1; i < objects.size(); i++) {
		maxProfit = max(maxProfit, objects[i].profit);
	}
	double scalingFactor = eps * maxProfit / objects.size();
	vector<Object> scaledObjects(objects.size());
	for (int i = 1; i < objects.size(); i++) {
		scaledObjects[i] = {
			objects[i].weight,
			(long long)(objects[i].profit / scalingFactor)};
	}
	return (double)DynamicForProfits(n, g, scaledObjects, out) * scalingFactor;
}

int main(int argc, char** argv) {
	vector<Object> objects = ReadData(argv[1]);
	vector<int> items;
	return FPTAS(N, G, objects, atof(argv[2]), items);
}
