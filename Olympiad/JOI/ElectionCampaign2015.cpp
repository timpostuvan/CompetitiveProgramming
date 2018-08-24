#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111
#define logn 20

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

vector<int> adj[maxn];
vector<vector<int> > query[maxn];

int in[maxn], out[maxn], dep[maxn];
int par[maxn][logn];
ll dp[maxn];
int cnt;

struct BIT{
	ll bit[maxn];

	int query(int x){
		ll ret = 0;
		while(x){
			ret += bit[x];
			x -= (x & -x);
		}
		return ret;
	}

	void update(int x, ll val){
		while(x < maxn){
			bit[x] += val;
			x += (x & -x);
		}
	}
} bit;

void DFS(int x, int p){
	in[x] = ++cnt;
	par[x][0] = p;

	for(int v : adj[x]){
		if(v == p)
			continue;

		dep[v] = dep[x] + 1;
		DFS(v, x);
	}

	out[x] = cnt;
}

int LCA(int a, int b){
	if(dep[a] > dep[b])
		swap(a, b);

	int raz = dep[b] - dep[a];
	for(int i = 0; i < logn; i++){
		if((raz >> i) & 1)
			b = par[b][i]; 
	}

	if(a == b)
		return a;

	for(int i = logn - 1; i >= 0; i--){
		if(par[a][i] != par[b][i]){
			a = par[a][i];
			b = par[b][i];
		}
	}
	return par[a][0];
}

void solve(int x, int p){
	dp[x] = 0;
	ll sum = 0;
	for(int v : adj[x]){
		if(v == p)
			continue;

		solve(v, x);
		sum += dp[v];
	}

	dp[x] = sum;
	for(vector<int> a : query[x]){
		int u = a[0], v = a[1], cost = a[2];
		ll cur = 0;
		if(u != x)
			cur += bit.query(in[u]);
		if(v != x)
			cur += bit.query(in[v]);

		dp[x] = max(dp[x], sum + cur + cost);
	}

	ll cur = sum - dp[x];
	bit.update(in[x], cur);
	bit.update(out[x] + 1, -cur);
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n - 1; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}

	DFS(1, 0);

	for(int j = 1; j < logn; j++)
		for(int i = 1; i <= n; i++)
			par[i][j] = par[par[i][j - 1]][j - 1];

	int m;
	scanf("%d", &m);
	for(int i = 0; i < m; i++){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		int lca = LCA(a, b);
		query[lca].pb({a, b, c});
	}

	solve(1, 0);

	printf("%lld\n", dp[1]);
	return 0;
}