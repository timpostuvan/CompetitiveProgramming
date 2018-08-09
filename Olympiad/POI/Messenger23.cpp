#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 101
#define maxd 52

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

ll good[maxn][maxn][maxd];
ll ways[maxn][maxn][maxd];

ll dp[maxd][2]; // 0 - ends in a, 1 - ends in b

int main(){
	int n, m, mod;
	scanf("%d%d%d", &n, &m, &mod);
	for(int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		ways[a][b][1] = 1;
	}

	for(int i = 1; i <= n; i++)
		ways[i][i][0] = 1;

	for(int d = 2; d < maxd; d++){
		for(int a = 1; a <= n; a++){
			for(int b = 1; b <= n; b++){
				for(int k = 1; k <= n; k++){
					ways[a][b][d] += ways[a][k][d - 1] * ways[k][b][1];
					ways[a][b][d] %= mod;
				}
			}
		}
	}

	for(int a = 1; a <= n; a++){
		for(int b = 1; b <= n; b++){
			for(int d = 1; d < maxd; d++){
				dp[d][0] = ways[a][a][d];
				dp[d][1] = ways[a][b][d];
				
				for(int k = 1; k <= d - 1; k++){
					dp[d][0] -= (dp[k][0] * ways[a][a][d - k]) % mod;
					dp[d][0] = (dp[d][0] + mod) % mod;

					dp[d][0] -= (dp[k][1] * ways[b][a][d - k]) % mod;
					dp[d][0] = (dp[d][0] + mod) % mod;

					dp[d][1] -= (dp[k][0] * ways[a][b][d - k]) % mod;
					dp[d][1] = (dp[d][1] + mod) % mod;

					dp[d][1] -= (dp[k][1] * ways[b][b][d - k]) % mod;
					dp[d][1] = (dp[d][1] + mod) % mod;
				}
			}

			for(int d = 1; d < maxd; d++)
				good[a][b][d] = dp[d][1];
		}
	}

	int q;
	scanf("%d", &q);
	while(q--){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		printf("%lld\n", good[a][b][c]);
	}

	return 0;
}