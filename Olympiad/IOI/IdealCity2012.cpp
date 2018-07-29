/*
Idea:
- http://www.ioi2012.org/hints-for-tasks-of-day-2/index.html (Ideal city)
- http://blog.brucemerry.org.za/2012/09/ioi-2012-day-2-analysis.html (Ideal City)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((int) 1e9)
#define MOD (1000 * 1000 * 1000)
#define maxn 100111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

struct node{
	int ind, l, d, num;
	vector<int> adj;

	node(){
		ind = l = d = -1;
	}
} nodes[maxn + 2];

int n;
ll ans;

int sz[maxn];
vector<int> here[maxn + 2], cur[maxn + 2];

void DFS(int x, int p){
	sz[x] = nodes[x].num;
	for(int v : nodes[x].adj){
		if(v == p)
			continue;

		DFS(v, x);
		sz[x] += sz[v]; 
	}

	for(int v : nodes[x].adj){
		if(v == p)
			continue;

		ans = (ans + 1LL * sz[v] * (n - sz[v])) % MOD; 
	}
}

bool intersect(int x, int y){
	int zac = max(nodes[x].l, nodes[y].l);
	int kon = min(nodes[x].d, nodes[y].d);
	return (zac <= kon);
}

void solve(vector<pii> &v){
	for(int i = 0; i < maxn; i++){
		nodes[i] = node();
		here[i].clear();
		cur[i].clear();
		sz[i] = 0;
	}

	int cnt = 0;
	sort(v.begin(), v.end());
	for(int i = 0; i < v.size(); i++)
		here[v[i].fi].pb(v[i].se);

	for(int i = 0; i < maxn; i++){
		for(int j = 0; j < here[i].size(); j++){
			int k = j;
			while(k < here[i].size() && (here[i][k] - here[i][j] == k - j))
				k++;

			k--;
			nodes[++cnt].l = here[i][j];
			nodes[cnt].d = here[i][k];
			nodes[cnt].num = k - j + 1;
			cur[i].pb(cnt);

			j = k;
		}
	}

	for(int i = 0; i < maxn; i++){
		int ind = 0;
		for(int j = 0; j < cur[i].size(); j++){
			ind = max(ind, 0);
			while(ind < cur[i + 1].size() && nodes[cur[i + 1][ind]].d < nodes[cur[i][j]].l)
				ind++;

			while(ind < cur[i + 1].size() && intersect(cur[i][j], cur[i + 1][ind])){
				int x = cur[i][j];
				int y = cur[i + 1][ind];
				nodes[x].adj.pb(y);
				nodes[y].adj.pb(x);
				ind++;
			}
			ind -= 2;
		}
	}

	DFS(1, -1);
}

vector<int> mx, my;
vector<pii> v;

int DistanceSum(int N, int *X, int *Y) {
	n = N;
	for(int i = 0; i < n; i++){
		mx.pb(X[i]);
		my.pb(Y[i]);
	}

	sort(mx.begin(), mx.end());
	mx.resize(distance(mx.begin(), unique(mx.begin(), mx.end())));
	sort(my.begin(), my.end());
	my.resize(distance(my.begin(), unique(my.begin(), my.end())));

	for(int i = 0; i < n; i++){
		int x = lower_bound(mx.begin(), mx.end(), X[i]) - mx.begin();
		int y = lower_bound(my.begin(), my.end(), Y[i]) - my.begin();	
		v.pb(mp(x, y));
	}

	ans = 0;
	solve(v);

	for(int i = 0; i < n; i++)
		swap(v[i].fi, v[i].se);

	solve(v);

	return (int) ans;
}