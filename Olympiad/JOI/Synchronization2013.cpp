/*
Idea:
- All nodes within the same connected component have equal size
- When we add a connection, we add difference in size of currect vertex to the lowest reachable ancestor
- When we remove a connection, size of current vertex is the same as size of the lowest reachable ancestor (as stated in the first line)
- This can be easily maintained using segment tree
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

vector<int> adj[maxn];
pii edge[maxn];
int in[maxn], out[maxn], pos[maxn], dep[maxn], last[maxn], sz[maxn];
int seg[4 * maxn];
bool state[maxn];
int cnt;

void DFS(int x, int p){
	in[x] = ++cnt;
	pos[cnt] = x;
	for(int v : adj[x]){
		if(v == p)
			continue;

		dep[v] = dep[x] + 1;
		DFS(v, x);
	}
	out[x] = cnt;
}

void build(int x, int l, int d){
	if(l > d)
		return;

	if(l == d){
		seg[x] = out[pos[l]];
		return;
	}

	int mid = (l + d) / 2;
	build(2 * x, l, mid);
	build(2 * x + 1, mid + 1, d);
	seg[x] = max(seg[2 * x], seg[2 * x + 1]);
}

void update(int x, int l, int d, int i, int val){
	if(l > d || i < l || i > d)
		return;

	if(l == d && l == i){
		seg[x] = val;
		return;
	}

	int mid = (l + d) / 2;
	update(2 * x, l, mid, i, val);
	update(2 * x + 1, mid + 1, d, i, val);
	seg[x] = max(seg[2 * x], seg[2 * x + 1]);
}

int findAncestor(int x, int l, int d, int i, int j){
	if(l > d || l > i || seg[x] < j)
		return -1;

	if(l == d)
		return pos[l];

	int mid = (l + d) / 2;
	int ret = findAncestor(2 * x + 1, mid + 1, d, i, j);
	if(ret == -1)
		ret = findAncestor(2 * x, l, mid, i, j);

	return ret;
}

int main(){
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n - 1; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
		edge[i] = mp(a, b);
	}

	DFS(1, -1);

	for(int i = 1; i <= n; i++){
		last[i] = 0;
		sz[i] = 1;
	}

	for(int i = 1; i <= n - 1; i++){
		state[i] = 0;
		if(dep[edge[i].fi] > dep[edge[i].se])
			swap(edge[i].fi, edge[i].se);		
	}

	build(1, 1, n);

	while(m--){
		int ind;
		scanf("%d", &ind);

		int from = edge[ind].fi;
		int to = edge[ind].se;
		int anc = findAncestor(1, 1, n, in[from], out[from]);

		if(!state[ind]){
			sz[anc] += sz[to] - last[to];
			update(1, 1, n, in[to], 0);
		}
		else{
			sz[to] = last[to] = sz[anc];
			update(1, 1, n, in[to], out[to]);
		}

		state[ind] ^= 1;
	}

	while(q--){
		int x;
		scanf("%d", &x);
		int anc = findAncestor(1, 1, n, in[x], out[x]);
		printf("%d\n", sz[anc]);
	}

	return 0;
}