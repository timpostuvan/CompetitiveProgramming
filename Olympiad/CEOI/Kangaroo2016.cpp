#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 2111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

ll dp[maxn][maxn];	// dp[first x elements already distributed][number of groups]

int main(){
	int n, s, e;
	scanf("%d%d%d", &n, &s, &e);

	int cnt = 0;
	dp[0][0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(i == e || i == s){		// merge with first/last group + add a new group
				dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
			}
			else{						// add a new group between 2 groups (x + 1 free spaces - start/end positions) + join two groups (x - 1 free spaces between)
				dp[i][j] = (dp[i - 1][j - 1] * ((j - 1) + 1 - cnt) + dp[i - 1][j + 1] * ((j + 1) - 1)) % MOD;
			}
		}
		if(i == e || i == s)
			cnt++;
	}

	printf("%lld\n", dp[n][1]);
	return 0;
}