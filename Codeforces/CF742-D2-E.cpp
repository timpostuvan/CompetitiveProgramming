/*
Idea:
- We add edges between 2 * i, 2 * i + 1 and every pair (boyfriend, girlfriend)
- This graph is bipartite so there exist an arrangement
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 20)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200011

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> adj[maxn];
int col[maxn];
int a[maxn], b[maxn];

void DFS(int x, int cur_col){
	col[x] = cur_col;
	for(auto v : adj[x]){
		if(col[v] != 0)
			continue;

		DFS(v, 3 - cur_col);
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d", a + i, b + i);
		adj[a[i]].pb(b[i]);
		adj[b[i]].pb(a[i]);
	}

	for(int i = 1; i <= n; i++){
		adj[2 * i].pb(2 * i - 1);
		adj[2 * i - 1].pb(2 * i);
	}

	for(int i = 1; i <= 2 * n; i++){
		if(col[i] == 0)
			DFS(i, 1);
	}

	for(int i = 1; i <= n; i++)
		printf("%d %d\n", col[a[i]], col[b[i]]);

	return 0;
}  