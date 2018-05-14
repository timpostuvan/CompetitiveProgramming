#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 310111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

bool here[maxn];
vector<int> adj[maxn];
ll sz[maxn];
ll n, zac, kon;


void DFS(int x, int p){
	sz[x] = 1;
	here[x] = (x == kon);
	for(int v : adj[x]){
		if(v == p)
			continue;

		DFS(v, x);
		sz[x] += sz[v];
		here[x] |= here[v];
	}
}

int main(){
	scanf("%lld%lld%lld", &n, &zac, &kon);
	for(int i = 0; i < n - 1; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}

	DFS(zac, -1);

	ll num = sz[zac];
	for(int v : adj[zac]){
		if(here[v])
			num -= sz[v];
	}
	
	ll ans = n * (n - 1);
	ans -= num * sz[kon];

	printf("%lld\n", ans);
	return 0;
}