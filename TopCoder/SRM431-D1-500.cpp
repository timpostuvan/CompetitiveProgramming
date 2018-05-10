/*
Idea:
- If there are more than 9 groups, two groups can be put together (pigeonhole principle) -> answer is 0
- dp[i][j][k][l] - current number has length i; there are j groups; last digit is k; the difference between
last two elements is l (10 means we started a new group and difference hasn't been set yet)
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

class MegaCoolNumbers{ 
	public:

	int dp[maxn][11][11][11];

	int fun(int n, int k, int x, int group, int last_digit, int diff){
		if(group > k)
			return 0;

		if(x == n){
			if(group == k)
				return 1;

			return 0;
		}

		int &cur = dp[x][group][last_digit][diff];
		if(cur != -1)
			return cur;

		cur = 0;
		for(int i = last_digit; i <= 9; i++){
			if(diff == 10){
				cur = (cur + fun(n, k, x + 1, group, i, i - last_digit)) % MOD;
				continue;
			}

			if(last_digit + diff == i){
				cur = (cur + fun(n, k, x + 1, group, i, i - last_digit)) % MOD;
				continue;
			}

			if(diff != 10 && last_digit + diff != i){
				cur = (cur + fun(n, k, x + 1, group + 1, i, 10)) % MOD;
				continue;
			}
		}
		return cur;
	}

	int count(int n, int k){
		if(k > 9)
			return 0;

		memset(dp, -1, sizeof(dp));

		int ans = 0;
		for(int i = 1; i <= 9; i++)
			ans = (ans + fun(n, k, 1, 1, i, 10)) % MOD;

		return ans;
	}
};