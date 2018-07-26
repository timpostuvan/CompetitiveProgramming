/*
Idea:
- We create graph with edges (a, b) if there are 2 different numbers at the same position
- Minimum length of sequence is number of connections - number of cycles
- Number of ways is affected only by number of nodes in connected component
- Number of ways within a connected component is (n * (n - 1)) * ((n - 1) * (n - 2)) * ... 
- At the end we can mix sequences of different connected components, so we need to multiply by C(minimum length, size_1) * C(minimum length - size_1, size_2) * ...
(size_x is size of x-th connected component)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 101111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

set<pii> s;
vector<int> adj[maxn], v;
ll fakt[maxn], pw2[maxn], inv[maxn], a[maxn], b[maxn], cyc_ways[maxn];
int used[maxn], cnt, cyc_num;

ll fastpow(ll x, ll y){
	ll ret = 1;
	while(y){
		if(y & 1)
			ret = (ret * x) % MOD;

		x = (x * x) % MOD;
		y >>= 1;
	}
	return ret;
}

ll C(ll x, ll y){
	return fakt[x] * inv[y] % MOD * inv[x - y] % MOD;
}

vector<int> st;

void DFS(int x, int p){
	st.pb(x);
	used[x] = 1;
	cnt++;

	for(int v : adj[x]){
		if(v == p)
			continue;

		if(used[v] == 1)
			cyc_num++;

		if(used[v] == 0)
			DFS(v, x);
	}

	used[x] = 2;
	st.pop_back();
}

void solve(){
	s.clear();
	v.clear();
	cyc_num = 0;
	memset(used, 0, sizeof(used));
	for(int i = 0; i < maxn; i++)
		adj[i].clear();

	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; i++)
		scanf("%lld", a + i);

	for(int i = 0; i < n; i++)
		scanf("%lld", b + i);

	for(int i = 0; i < n; i++){
		if(a[i] == b[i])
			continue;

		s.insert(mp(min(a[i], b[i]), max(a[i], b[i])));
	}

	for(auto it = s.begin(); it != s.end(); it++){
		adj[it -> fi].pb(it -> se);
		adj[it -> se].pb(it -> fi);
	}


	for(int i = 1; i <= n; i++){
		if(used[i] == 0){
			st.clear();
			cnt = 0;
			DFS(i, -1);
			v.pb(cnt);
		}
	}

	ll all = s.size() - cyc_num;
	ll sz = all;
	ll ways = 1LL;

	for(int i : v){
		ways = (ways * cyc_ways[i]) % MOD;
		ways = (ways * C(sz, i - 1)) % MOD;
		sz -= i - 1;
	}  
 
	if(k == 1)
		printf("%lld\n", all);
 
	if(k == 2)
		printf("%lld %lld\n", all, ways);
}

void preprocess(){
	fakt[0] = pw2[0] = inv[0] = 1;
	for(int i = 1; i < maxn; i++){
		fakt[i] = (1LL * i * fakt[i - 1]) % MOD;
		inv[i] = fastpow(fakt[i], MOD - 2);
		pw2[i] = (2LL * pw2[i - 1]) % MOD;
	}

	cyc_ways[0] = cyc_ways[1] = 1;
	cyc_ways[2] = 2;
	for(int i = 3; i < maxn; i++)
		cyc_ways[i] = ((1LL * i * (i - 1)) % MOD * cyc_ways[i - 1]) % MOD; 
}

int main(){
	preprocess();

	int t;
	scanf("%d", &t);
	while(t--)
		solve();

	return 0;
}