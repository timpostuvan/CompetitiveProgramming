#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define maxn 5111

typedef long long ll;

int used[maxn];
int lev[maxn];
int w[maxn];
vector<int> adj[maxn];
vector<int> adj1[maxn];
queue<int> q;

int ret, n;

void DFS(int x){
	w[x] = 1;
	for(int v : adj1[x]){
		DFS(v);
		w[x] += w[v];		
	}
	ret += w[x];
}

ll check(int x){
	ret = 0;
	memset(used, 0, sizeof(used));
	memset(lev, 0, sizeof(lev));
	memset(w, 0, sizeof(w));
	for(int i = 0; i < maxn; i++)
		adj1[i].clear();
	

	lev[x] = 1;
	q.push(x);
	used[x] = 1;

	while(!q.empty()){
		int cur = q.front();
		q.pop();

		for(int v : adj[cur]){
			if(!used[v]){
				adj1[cur].pb(v);
				used[v] = 1;
				lev[v] = lev[cur] + 1;
				q.push(v);
			}
		}
	}
	for(int i = 1; i <= n; i++){
		if(!used[i])
			return INF;
	}
	
	DFS(x);
	return ret;
}

int main(){
	ll ans = INF;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int k;
		scanf("%d", &k);
		while(k--){
			int a;
			scanf("%d", &a);
			adj[a].pb(i);
		}
	}

	for(int i = 1; i <= n; i++)
		ans = min(ans, check(i));

	printf("%lld\n", ans);
	return 0;
}