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
// maxProfit, until finding a position that has a value smaller tham G
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

int main(int argc, char** argv) {
	vector<Object> objects = ReadData(argv[1]);
	vector<int> items;
	return DynamicForProfits(N, G, objects, items);
}
