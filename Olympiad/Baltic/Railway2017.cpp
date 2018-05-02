#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define INF (1LL << 55)
#define maxn 100111
#define LOG 20

typedef long long ll;

vector<int> adj[maxn];
int n, m, k, l[maxn], d[maxn];
int num[maxn], lev[maxn], cnt[maxn];
int par[LOG][maxn];
int st;

bool comp(const int &a, const int &b){
	return num[a] < num[b];
}


int LCA(int a, int b){
	if(lev[a] < lev[b])
		swap(a, b);

	int raz = lev[a] - lev[b];
	for(int i = LOG - 1; i >= 0; i--){
		if(raz & (1 << i)){
			a = par[i][a];
		}
	}

	for(int i = LOG - 1; i >= 0; i--){
		if(par[i][a] != par[i][b]){
			a = par[i][a];
			b = par[i][b];
		}
	}

	if(a == b)
		return a;

	return par[0][a];
}


void update(int a, int b){   // prefix sums on tree
	int lca = LCA(a, b);
	cnt[a]++;
	cnt[b]++;
	cnt[lca] -= 2;
}

void DFS1(int x, int p){
	num[x] = ++st;
	for(auto v : adj[x]){
		if(v == p)
			continue;
		lev[v] = lev[x] + 1;
		par[0][v] = x;
		DFS1(v, x);
	}
}

void DFS2(int x, int p){ 	// prefix sums on tree
	for(auto v : adj[x]){
		if(v == p)
			continue;
		DFS2(v, x);
		cnt[x] += cnt[v];
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 0; i < n - 1; i++){
		int a, b;
		scanf("%d%d", l + i, d + i);
		adj[l[i]].push_back(d[i]);
		adj[d[i]].push_back(l[i]);		
	}

	DFS1(1, -1);

	for(int i = 1; i < LOG; i++){
		for(int j = 1; j <= n; j++){
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}

	while(m--){
		int d;
		scanf("%d", &d);
		vector<int> v(d);
		for(int i = 0; i < d; i++)
			scanf("%d", &v[i]);
		
		sort(v.begin(),v.end(), comp);
		for(int i = 0; i < d; i++)
			update(v[i], v[(i + 1) % d]);
	}

	DFS2(1, -1);

	vector<int> ans;

	for(int i = 0; i < n - 1; i++){
		if(num[l[i]] < num[d[i]]) swap(l[i], d[i]);
		if(cnt[l[i]] >= 2 * k)
			ans.push_back(i + 1);
	}
	printf("%d\n", (int) ans.size());
	for(int i : ans)
		printf("%d ", i);

	return 0;
}