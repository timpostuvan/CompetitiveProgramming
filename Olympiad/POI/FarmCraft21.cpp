#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 500111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int c[maxn];
vector<int> adj[maxn];

bool comp(pii a, pii b){
	return a.se - a.fi < b.se - b.fi;
}


pii DFS(int x, int p){
	vector<pii> cur;
	pii ret = mp(0, c[x]);	// <subtree size, maximum installation time>

	for(int v : adj[x]){
		if(v == p)
			continue;

		cur.pb(DFS(v, x));
	} 

	sort(cur.begin(), cur.end(), comp);
	for(int i = cur.size() - 1; i >= 0; i--){
		ret.se = max(ret.se, ret.fi + 1 + cur[i].se);
		ret.fi += cur[i].fi + 2;
	}
	return ret;
}


int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", c + i);

	for(int i = 0; i < n - 1; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}

	printf("%d\n", max(DFS(1, -1).se, c[1] + 2 * (n - 1)));
	return 0;
}