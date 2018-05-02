#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 300111
#define maxk 5

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;


vector<int> adj[maxn];
vector<int> v[maxk + 2];

ll dp[maxn][1 << maxk];
int col[maxn];

void preprocess(int k){
	for(int i = 0; i < (1 << k); i++){
		int num = __builtin_popcount(i);
		v[num].pb(i);
	}
}

int main(){
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++){
		scanf("%d", col + i);
		col[i]--;
		dp[i][(1 << col[i])] = 1;
	}

	while(m--){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	
	preprocess(k);

	for(int cnt = 1; cnt < k; cnt++){
		for(int i = 1; i <= n; i++){
			for(int bitmask : v[cnt]){
				if((bitmask & (1 << col[i])) == (1 << col[i]))		// already contains this color
					continue;

				int new_bitmask = bitmask ^ (1 << col[i]);
				for(int u : adj[i])
					dp[i][new_bitmask] += dp[u][bitmask];
			}
		}
	}

	ll ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < (1 << k); j++)
			ans += dp[i][j];
	}

	printf("%lld\n", ans - n);

	return 0;
}