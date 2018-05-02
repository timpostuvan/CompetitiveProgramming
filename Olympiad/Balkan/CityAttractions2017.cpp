#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 300111

typedef long long ll;
typedef long double ld;

int arr[maxn], disc[maxn];
vector<pair<int, pair<int, int> > > adj[maxn];


pair<int, int> DFS(int x, int p){
	pair<int, int> cur = mp(arr[x], x);
	if(p == -1)
		cur = mp(-2e9, -1);

	for(int i = 0; i < adj[x].size(); i++){
		if(adj[x][i].fi == p)
			continue;

		if(adj[x][i].se.se == -1){
			adj[x][i].se = DFS(adj[x][i].fi, x);
			adj[x][i].se.fi -= 1;
		}
		if(cur.fi < adj[x][i].se.fi || (cur.fi == adj[x][i].se.fi && cur.se > adj[x][i].se.se))
			cur = adj[x][i].se;
	}
	return cur;
}

int main(){
	int n, cnt = 1;
	ll k;
	scanf("%d%lld", &n, &k);

	for(int i = 1; i <= n; i++)
		scanf("%d", arr + i);

	for(int i = 0; i < n - 1; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(mp(b, mp(-1e9, -1)));
		adj[b].pb(mp(a, mp(-1e9, -1)));
	}

	int x = 1;
	while(k--){
		if(disc[x] != 0)
			k %= (cnt - disc[x]);
		else
			disc[x] = cnt++;

		pair<int, int> a = DFS(x, -1);
		x = a.se;
	}
	printf("%d\n", x);
	return 0;
}