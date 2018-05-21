/*
Idea:
- In manager's subtree it is optimal to take as many ninjas as possible -> we take ninjas with lowest salary (as long as their sum is less than m)
- To get ninjas with lowest cost we need to store set with all ninjas available at that point
- Set is just current ninja + ninjas from all immediate childer (we must be careful when merging and use smaller to larger trick)
- We set every ninja as a manager and output best 
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
multiset<ll> s[maxn];
ll sum[maxn], l[maxn], c[maxn];
ll n, m, ans;

void DFS(int x){
	int big = -1;
	for(int v : adj[x]){
		DFS(v);

		sum[x] += sum[v];
		if(big == -1 || s[v].size() > s[big].size())
			big = v;
	}

	if(big != -1){
		swap(s[x], s[big]);
		for(int v : adj[x]){
			if(v == big)
				continue;

			for(ll j : s[v])
				s[x].insert(j);
		}
	}

	s[x].insert(c[x]);
	sum[x] += c[x];

	while(sum[x] > m){
		auto it = (--s[x].end());
		sum[x] -= *it;
		s[x].erase(it);
	}

	ans = max(ans, l[x] * (ll) s[x].size());
}


int main(){
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++){
		int par;
		scanf("%d%lld%lld", &par, c + i, l + i);
		adj[par].pb(i);
	}

	ans = 0;
	DFS(1);

	printf("%lld\n", ans);
	return 0;
}