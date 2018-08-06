/*
Idea:
- http://ceoi2014.informatik-olympiade.de/wp-content/uploads/2014/06/007-spoiler.pdf
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 27)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

int da[maxn], db[maxn];
vector<int> adj[maxn];

void BFS(int zac, int d[]){
	for(int i = 0; i < maxn; i++)
		d[i] = INF;

	queue<int> q;
	d[zac] = 0;
	q.push(zac);
	while(!q.empty()){
		int x = q.front();
		q.pop();

		for(int v : adj[x]){
			if(d[x] + 1 < d[v]){
				d[v] = d[x] + 1;
				q.push(v);
			}
		}
	}
}

bool used[maxn];

int find_dist(int x){
	used[x] = 1;
	int ret = 0;
	for(int v : adj[x]){
		if(!used[v] && (da[v] + 1 == da[x]) && (db[v] + 1 == db[x]))
			ret = max(ret, 1 + find_dist(v));
	}
	return ret;
}

int main(){
	int n, m, agent, drnull, a, b;
	scanf("%d%d%d%d%d%d", &n, &m, &agent, &drnull, &a, &b);
	for(int i = 0; i < m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		adj[x].pb(y);
		adj[y].pb(x);
	}

	BFS(a, da);
	BFS(b, db);

	int w1 = da[drnull] - da[agent];
	int w2 = db[drnull] - db[agent];

	int ans;	
	if(min(w1, w2) < 0){
		printf("-1\n");
		return 0;
	}	

	if(abs(w1 - w2) == 1)
		ans = min(w1, w2);

	if(w1 == w2){
		memset(used, 0, sizeof(used));
		int dist_drnull = find_dist(drnull);

		memset(used, 0, sizeof(used));
		int dist_agent = find_dist(agent);

		if(dist_agent >= dist_drnull - w1)
			ans = w1;
		else
			ans = w1 - 1;
	}

	printf("%d\n", ans);
	return 0;
}