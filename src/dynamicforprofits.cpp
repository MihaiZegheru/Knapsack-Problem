// *****************************************************************************
// *                     Dynamic for a small sum of profits                    *
// *****************************************************************************
//
// This dynamic approach works best for a small total profit and for small
// individual profits.
// dp[i] = the minimum possible value of weight for achieving profit i
//
// For each object, in the worst case, we do maxProfit steps by minimising out
// all the possible "starting points" for our next objetcs, just as the dynamic
// for weights.
// Basically we build up all the possible configurations through overlapping and
// choosing the best outcome through the formula:
// dp[j] = min(dp[j], dp[j - objects[i].profit] + objects[i].weight)
//
// Here all we do is say that for object i, the best weight for a total profit
// of j is achieved by choosing either the already existing weight (which means
// not picking the object) or by getting our weight for the
// j - objects[i].profit profit and adding our new weight (which means we pick
// this item).
//
// This algorithm also works for solving the problem online. The best answer
// needs to be computed by iterating from the sum of all profits, that being
// maxProfit, until finding a position that has a value smaller tham maxWeight
// i.e. a position with a profit that could have been achieved by not surpassing
// the weight limit.
// For this approach we risk doing maxProfit steps for each iteration which is
// far away from ideal.
//
// Complexity:
// Time - O(n * maxProfit)
// Space - maxProfit
//
// Cons:
// This dynamic approach on weight is very sensitive to big profits and
// maxProfits, for both time and space wise.
//
// Solution by SPyofgame (CodeForces)[https://codeforces.com/blog/entry/88660#other]
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

int main(int argc, char** argv) {
	vector<Object> objects = ReadData(argv[1]);
	return DynamicForProfits(objects);
}
