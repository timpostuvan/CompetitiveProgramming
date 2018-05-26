#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;


vector<int> adj[maxn], edge[maxn], tree[maxn];
int num[maxn], low[maxn];
ll c[maxn], two_path[maxn];
bool new_component[maxn];

int n, nn, cnt, BCC;
ll ans;

void DFS(int x){
	nn++;
	num[x] = low[x] = ++cnt;
	for(int v : adj[x]){
		if(!num[v]){
			DFS(v);
			if(low[v] >= num[x])
				new_component[v] = 1;

			tree[x].pb(v);
			low[x] = min(low[x], low[v]);
		}
		else
			low[x] = min(low[x], num[v]);
	}
}

void Add_Edge(int x, int y){
	edge[x].pb(y);
	edge[y].pb(x);
}

void Make_BBC(int x, int component){
	if(component != 0)
		Add_Edge(x, component);

	for(int v : tree[x]){
		if(new_component[v]){
			BCC++;
			Add_Edge(x, BCC);
			Make_BBC(v, BCC);
		}
		else
			Make_BBC(v, component);
	}
}

void Calc(int x, int par){
	if(x <= n)
		c[x] = 1;

	for(int v : edge[x]){
		if(v == par)
			continue;

		Calc(v, x);
		c[x] += c[v];
	}

	for(int v : edge[x]){
		if(v == par)
			two_path[x] += (nn - c[x]) * (nn - c[x] - 1);
		else
			two_path[x] += c[v] * (c[v] - 1);
	}
}

void Go(int x, int par){
	for(int v : edge[x]){
		if(v == par)
			continue;

		Go(v, x);
	}

	if(x > n)
		return;

	ll all_paths = 1LL * (nn - 1) * (nn - 2);
	ll not_valid = 0;
	for(int v : edge[x]){
		if(v == par)
			not_valid += two_path[v] - c[x] * (c[x] - 1);
		else
			not_valid += two_path[v] - (nn - c[v]) * (nn - c[v] - 1);
	}
	ans += all_paths - not_valid;
}

int main(){
	int m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}

	BCC = n;
	for(int i = 1; i <= n; i++){
		if(!num[i]){
			nn = 0;
			DFS(i);
			Make_BBC(i, 0);
			Calc(i, 0);
			Go(i, 0);
		}
	}
	
	printf("%lld\n", ans);
	return 0;
}