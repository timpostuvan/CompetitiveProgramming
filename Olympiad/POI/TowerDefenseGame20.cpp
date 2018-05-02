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
typedef pair<ll, ll> pii;

bool used[maxn], guarded[maxn];
vector<int> adj[maxn];
vector<int> ans;

void solve(int x){
	guarded[x] = 1;
	used[x] = 1;

	for(int v : adj[x]){
		guarded[v] = 1;
		if(!used[v]){
			for(int u : adj[v])
				guarded[u] = 1;
		}
		used[v] = 1;
	}
}

int main(){
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}

	for(int i = 1; i <= n; i++){
		if(!guarded[i]){
			ans.pb(i);
			solve(i);
		}
	}

	printf("%d\n", (int) ans.size());
	for(int i : ans)
		printf("%d ", i);
	
	return 0;
}