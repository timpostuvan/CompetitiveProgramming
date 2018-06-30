/*
Idea:
- http://hsin.hr/coci/archive/2006_2007/ (COI solutions)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((int) 2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111
#define logn 20

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> adj[maxn], tree[maxn];
 
int num[maxn], low[maxn], dep[maxn], in[maxn], out[maxn];
int par[maxn][logn];
int cnt;

void DFS(int x, int p){
	num[x] = low[x] = ++cnt;
	for(int v : adj[x]){
		if(v == p)
			continue;

		if(!num[v]){
			DFS(v, x);

			tree[x].pb(v);
			low[x] = min(low[x], low[v]);
		}
		else
			low[x] = min(low[x], num[v]);
	}
}

void Calc(int x, int p){
	in[x] = ++cnt;
	par[x][0] = p;
	for(int v : tree[x]){
		dep[v] = dep[x] + 1;
		Calc(v, x);
	}
	out[x] = cnt;
}

int LCA(int a, int b){
	if(dep[a] > dep[b])
		swap(a, b);

	int dif = dep[b] - dep[a];
	for(int i = 0; i < logn; i++){
		if((dif >> i) & 1)
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

int parent(int x, int d){
	if(dep[x] < d)
		return -1;

	int dif = dep[x] - d;
	for(int i = 0; i < logn; i++){
		if((dif >> i) & 1)
			x = par[x][i];
	}
	return x;
}

bool isBelow(int x, int y){
	return (in[y] <= in[x] && out[x] <= out[y]); 
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}

	DFS(1, 0);
	cnt = 0;
	Calc(1, 0);	

	for(int j = 1; j < logn; j++){
		for(int i = 1; i <= n; i++)
			par[i][j] = par[par[i][j - 1]][j - 1];
	}

	int q;
	scanf("%d", &q);
	while(q--){
		int t, a, b, c, d, ans = -1;
		scanf("%d%d%d%d", &t, &a, &b, &c);

		if(t == 1){
			scanf("%d", &d);
			if(dep[c] > dep[d])
				swap(c, d);

			if(num[c] < low[d]){
				if((isBelow(a, d) && !isBelow(b, d)) || 
					(!isBelow(a, d) && isBelow(b, d)))
					ans = 0;
				else
					ans = 1;
			}
			else
				ans = 1;
		}

		if(t == 2){
			int lca = LCA(a, b);
			ans = 1;

			int pa = parent(a, dep[c] + 1);
			int pb = parent(b, dep[c] + 1);

			if(isBelow(a, c) && isBelow(b, c)){
				if(lca == c && (low[pa] >= num[c] || low[pb] >= num[c]))
					ans = 0;
			}

			if((isBelow(a, c) && low[pa] >= num[c] && !isBelow(b, c)) ||
				(!isBelow(a, c) && isBelow(b, c) && low[pb] >= num[c]))
				ans = 0;
		}

		printf("%s\n", (ans == 1) ? "yes" : "no");
	}
	return 0;
}