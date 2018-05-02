#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 30)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<pii> adj[maxn];
int group[maxn];
int par[maxn];
pair<ll, ll> r[maxn];

bool leaf[maxn];

pair<ll, ll> add(pair<ll, ll> x, ll num){
	pair<ll, ll> ret;
	ret.fi = x.fi * num;
	ret.se = x.se * num + (num - 1);
	if(ret.fi > INF)
		ret.fi = INF;

	if(ret.se > INF)
		ret.se = INF;

	return ret;
}

void DFS(int x, int p, int pedge){
	if(adj[x].size() == 1)
		leaf[x] = 1;

	for(pii a : adj[x]){
		int v = a.fi;
		int ind = a.se;

		if(v == p || ind == 1)
			continue;

		par[v] = ind;
		r[ind] = add(r[pedge], adj[x].size() - 1);
		DFS(v, x, ind);
	}
}



int main(){
	int n, g, k;
	ll ans = 0;
	scanf("%d%d%d", &n, &g, &k);
	for(int i = 0; i < g; i++)
		scanf("%d", group + i);

	sort(group, group + g);

	int s1, s2;
	for(int i = 1; i <= n - 1; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		if(i == 1){
			s1 = a;
			s2 = b;
		}

		adj[a].pb(mp(b, i));
		adj[b].pb(mp(a, i));
	}

	r[1] = mp(k, k);
	par[s1] = par[s2] = 1;

	DFS(s1, -1, 1);
	DFS(s2, -1, 1);

	for(int i = 1; i <= n; i++){
	//	printf("%d:  %lld   %lld\n", i, r[par[i]].fi, r[par[i]].se);
		if(leaf[i]){
			int x = par[i];

			int num = upper_bound(group, group + g, r[x].se) - lower_bound(group, group + g, r[x].fi);;
			ans += 1LL * num * k;
		}
	}

	printf("%lld\n", ans);
	return 0;
}