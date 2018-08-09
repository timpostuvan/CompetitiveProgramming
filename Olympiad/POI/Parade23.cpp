#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> adj[maxn];
int dp[maxn];
int ans;

void DFS(int x, int p){
	dp[x] = adj[x].size() - 1;
	for(int v : adj[x]){
		if(v == p)
			continue;

		DFS(v, x);
	}

	vector<int> cur;
	for(int v : adj[x]){
		if(v == p)
			continue;
		cur.pb(dp[v]);
	}

	sort(cur.begin(), cur.end());
	reverse(cur.begin(), cur.end());

	if(cur.size() >= 1){
		dp[x] = max(dp[x], cur[0] + (int) adj[x].size() - 2);
		ans = max(ans, cur[0] + (int) adj[x].size() - 1);
	}

	if(cur.size() >= 2)
		ans = max(ans, cur[0] + cur[1] + (int) adj[x].size() - 2);
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n - 1; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}

	DFS(1, -1);

	printf("%d\n", ans);
	return 0;
}