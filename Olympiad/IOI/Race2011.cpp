#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111
#define maxk 1000111

typedef long long ll;
typedef long double ld;

set<pair<int, int> > adj[maxn];

int cenpar[maxn], sz[maxn], t[maxk], val[maxk];
int nn, ans, cnt;
int n, k;

void DFS1(int x, int p){
	sz[x] = 1;
	nn++;
	for(auto it = adj[x].begin(); it != adj[x].end(); it++){
		if(it -> fi == p)
			continue;
		DFS1(it -> fi, x);
		sz[x] += sz[it -> fi];
	}
}

int DFS2(int x, int p){
	for(auto it = adj[x].begin(); it != adj[x].end(); it++){
		if(it -> fi == p)
			continue;
		if(sz[it -> fi] > nn / 2)
			return DFS2(it -> fi, x);
	}
	return x;
}

void calc(int x, int p, int cur, int len, int fill){
	if(cur > k)
		return;

	if(!fill){
		if(t[k - cur] == cnt){
			ans = min(ans, val[k - cur] + len);
		}

		if(cur == k)
			ans = min(ans, len);
	}

	if(fill){
		if(t[cur] < cnt){
			t[cur] = cnt;
			val[cur] = len;
		}

		if(t[cur] == cnt){
			val[cur] = min(val[cur], len);
		}
	}

	for(auto it = adj[x].begin(); it != adj[x].end(); it++){
		if(it -> fi == p)
			continue;
		calc(it -> fi, x, cur + it -> se, len + 1, fill);
	}
}

void decompose(int root, int p){
	nn = 0;
	DFS1(root, root);
	int centroid = DFS2(root, root);
	if(p == -1)
		p = centroid;

	cenpar[centroid] = p;

	cnt++; 			// timestamp so memset is not needed

	for(auto it = adj[centroid].begin(); it != adj[centroid].end(); it++){
		calc(it -> first, centroid, it -> second, 1, 0);
		calc(it -> first, centroid, it -> second, 1, 1);
	}

	for(auto it = adj[centroid].begin(); it != adj[centroid].end(); it++){
		adj[it -> fi].erase(mp(centroid, it -> se));
		decompose(it -> fi, centroid);
	}
}

int main(){
	ans = 1e9;
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n - 1; i++){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		adj[a].insert(mp(b, c));
		adj[b].insert(mp(a, c));
	}

	memset(t, -1, sizeof(t));
	for(int i = 0; i < maxk; i++)
		val[i] = 1e9;

	
	decompose(0, -1);

	if(ans == 1e9)
		ans = -1;
	printf("%d\n", ans);
	return 0;
}