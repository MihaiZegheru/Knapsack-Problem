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

long long DynamicForProfits(vector<Object>& objects) {
	long long maxProfitSum = 0;
	for (long long i = 0; i < objects.size(); i++) {
		maxProfitSum = max(maxProfitSum, maxProfitSum + objects[i].profit);
	}
 	vector<long long> dp(maxProfitSum + 5, INT64_MAX - maxWeight);
	dp[0] = 0;

 	long long profitSum = 0;
	for (long long i = 0; i < objects.size(); i++) {
		profitSum += objects[i].profit;
		for (long long j = profitSum; j >= objects[i].profit; j--) {
			dp[j] = min(dp[j], dp[j - objects[i].profit] + objects[i].weight);
		}
	}

	for (long long ans = profitSum; ans >= 0; ans--) {
		if (dp[ans] <= maxWeight) {
			return ans;
		}
	}
	return 0;
}

long long FPTAS(vector<Object>& objects, double eps) {
	long long maxProfit = 0;
	for (int i = 0; i < objects.size(); i++) {
		maxProfit = max(maxProfit, objects[i].profit);
	}
	double scalingFactor = eps * maxProfit / objects.size();
	vector<Object> scaledObjects(objects.size());
	for (int i = 0; i < objects.size(); i++) {
		scaledObjects[i] = {
			objects[i].weight,
			(long long)(objects[i].profit / scalingFactor)};
	}
	return (double)DynamicForProfits(scaledObjects) * scalingFactor;
}

int main(int argc, char** argv) {
	vector<Object> objects = ReadData(argv[1]);
	return FPTAS(objects, 0.5);
}
