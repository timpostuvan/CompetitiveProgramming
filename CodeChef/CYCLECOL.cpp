/*
Idea:
- https://discuss.codechef.com/questions/130200/invitation-for-ioi-training-camp-ioitc-replay-contest-1/130293
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int used[maxn], col_tree[maxn], col_bi[maxn], dep[maxn], root[maxn], par[maxn];
vector<int> adj[maxn], tree[maxn], cycle;
bool found_cyc;

int rooting(int x){
	if(root[x] == x)
		return x;
	return root[x] = rooting(root[x]);
}

void find_cycle(int x, int p){
	if(found_cyc)
		return;

	used[x] = 1;
	par[x] = p;

	for(int v : adj[x]){
		if(v == p || found_cyc)
			continue;

		if(used[v]){
			if((dep[x] % 2) == (dep[v] % 2)){
				found_cyc = 1;
				int cur = x;
				while(cur != v){
					cycle.pb(cur);
					cur = par[cur];
				}
				cycle.pb(v);
				return;
			}
		}

		if(!used[v]){
			col_bi[v] = 1 ^ col_bi[x];
			dep[v] = dep[x] + 1;
			find_cycle(v, x);
		}
	}
}

void DFS(int x, int p){
	for(int v : tree[x]){
		if(v == p)
			continue;

		col_tree[v] = 1 ^ col_tree[x]; 
		DFS(v, x);
	}
}


void solve(){
	memset(used, 0, sizeof(used));
	memset(col_bi, 0, sizeof(col_bi));
	memset(col_tree, 0, sizeof(col_tree));
	memset(par, 0, sizeof(par));
	memset(dep, 0, sizeof(dep));
	cycle.clear();
	found_cyc = 0;
	for(int i = 0; i < maxn; i++){
		adj[i].clear();
		tree[i].clear();
		root[i] = i;
	}

	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		int ra = rooting(a);
		int rb = rooting(b);
		if(ra != rb){
			tree[a].pb(b);
			tree[b].pb(a);
			root[ra] = rb;
		}
		else{
			adj[a].pb(b);
			adj[b].pb(a);
		}
	}

	DFS(1, 0);

	for(int i = 1; i <= n; i++){
		if(!used[i])
			find_cycle(i, 0);
	}

	if(!found_cyc){
		printf("1\n");
		for(int i = 1; i <= n; i++)
			printf("%d%c", 2 * col_tree[i] + col_bi[i] + 1, (i == n) ? '\n' : ' ');	
	}
	else{
		printf("2\n");
		printf("%d", (int) cycle.size());
		for(int v : cycle)
			printf(" %d", v);
		printf("\n");
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--)
		solve();

	return 0;
}