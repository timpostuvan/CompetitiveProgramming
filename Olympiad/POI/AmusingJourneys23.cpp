#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 28)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 500111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<pii> deg;
vector<vector<int> > comp;
vector<int> adj[maxn], art_adj[maxn], st;
int low[maxn], num[maxn], cur_deg[maxn], cnt;
int max_sz, min_sz;
bool art[maxn], here[maxn];
bool brak, nie;
ll ways;

void DFS(int x, int p){
	num[x] = low[x] = ++cnt;
	st.pb(x);

	for(int v : adj[x]){
		if(v == p)
			continue;

		if(!num[v]){
			DFS(v, x);

			low[x] = min(low[x], low[v]);

			if(num[x] <= low[v]){
				art[x] = (num[x] > 1 || num[v] > 2);
				comp.pb({x});

				while(comp.back().back() != v){
					comp.back().pb(st.back());
					st.pop_back();
				}

			}
		}
		else
			low[x] = min(low[x], num[v]);
	}
}

int calc(int x, int p, int end){
	if(x == end)
		return 0;

	for(int v : adj[x]){
		if(v == p || !here[v])
			continue;

		return (1 + calc(v, x, end));
	}
}

void addDeg(pii x){
	if(x.fi >= deg[0].fi){
		deg[2] = deg[1];
		deg[1] = deg[0];
		deg[0] = x;
		return;
	}

	if(x.fi >= deg[1].fi){
		deg[2] = deg[1];
		deg[1] = x;
		return;
	}

	if(x.fi >= deg[2].fi){
		deg[2] = x;
		return;
	}
}

void solve(vector<int> &v){
	int edges = 0, n = v.size(); 
	if(n < 3)
		return;

	deg.resize(3);
	for(int i = 0; i < 3; i++)
		deg[i] = mp(-1, 0);

	for(int x : v){
		cur_deg[x] = 0;
		here[x] = 1;
	}

	for(int x : v){
		if(art[x])
			continue;

		for(int u : adj[x]){
			if(here[u] && (art[u] || x > u)){
				cur_deg[x]++;
				cur_deg[u]++;
				edges++;
			}
		}
	}

	for(int x : v){
		if(art[x]){
			for(int u : art_adj[x]){
				if(here[u] && x > u){
					cur_deg[x]++;
					cur_deg[u]++;
					edges++;
				}
			}
		}
	}

	for(int x : v)
		addDeg(mp(cur_deg[x], x));

	if(edges != n - 1)
		brak = 0;

	if(deg.size() > 2 && deg[2].fi > 2)
		nie = 1;

	if(!nie && deg[0].fi > 2){
		int start = deg[0].se; 
		int end = deg[1].se;
		int r = 0, mini = INF, maxi = -1;

		for(int x : adj[start]){
			if(here[x]){
				int a = 1 + calc(x, start, end);
				mini = min(mini, a);
				maxi = max(maxi, a);
				r++;
			}
		}

		if(mini != maxi)
			nie = 1;

		max_sz = max(max_sz, 2 * mini);
		min_sz = min(min_sz, 2 * mini);

		ways = (ways + 2LL * (2LL * r * (r - 1) / 2LL % MOD)) % MOD;
		ways = (ways + 1LL * (n - 2) * (2LL * (r - 1)) ) % MOD;
	}

	if(deg[0].fi == 2){
		ways = (ways + 2LL * n) % MOD;
		max_sz = max(max_sz, n);
		min_sz = min(min_sz, n);
	}

	for(int x : v)
		here[x] = 0;
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

	brak = 1; nie = 0;
	max_sz = -1; min_sz = INF;
	DFS(1, -1);

	for(int i = 1; i <= n; i++){
		if(art[i]){
			for(int v : adj[i]){
				if(art[v])
					art_adj[i].pb(v);
			}
		}
	}

	ways = 0;
	for(auto v : comp){
		solve(v);
	}

	if(max_sz != min_sz)
		nie = 1;

	if(brak){
		printf("BRAK\n");
		return 0;
	}

	if(nie){
		printf("NIE\n");
		return 0;
	}

	printf("TAK\n");
	printf("%d %lld\n", min_sz, ways);
	return 0;
}