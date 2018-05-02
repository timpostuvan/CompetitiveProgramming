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
ll t[maxn], dp[maxn], cur[maxn];
int sz[maxn];

ll ans = 0;

bool comp(pair<ll, int> a, pair<ll, int> b){
	return a.fi * b.se < b.fi * a.se;
}

void DFS(int x){
	sz[x] = 1;
	dp[x] = t[x];

	vector<pair<ll, int> > here;
	here.pb(mp(1, 0));
	for(int v : adj[x]){
		DFS(v);
		sz[x] += sz[v];
		here.pb(mp(dp[v], sz[v]));
	}


	for(int i = 0; i < here.size(); i++)
		dp[x] += here[i].fi;

	ans += dp[x];

	if(here.size() == 1)
		return;


	sort(here.begin() + 1, here.end(), comp);

	ll cost = 0;
	cur[here.size() - 1] = 0;
	
	for(int i = here.size() - 2; i >= 0; i--)
		cur[i] = cur[i + 1] + here[i + 1].se;

	for(int i = 0; i < here.size(); i++)
		cost += cur[i] * here[i].fi;

	ans += cost;
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld", t + i);
		int m;
		scanf("%d", &m);
		while(m--){
			int x;
			scanf("%d", &x);
			adj[i].pb(x);
		}	
	}

	DFS(1);

	printf("%lld\n", ans);
	return 0;
}