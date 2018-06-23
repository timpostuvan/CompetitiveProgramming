/*
Idea:
- https://img.atcoder.jp/arc099/editorial.pdf
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 711

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int adj[maxn][maxn], col[maxn];
vector<pii> comp;

int n, m, nn, cnt;

bool used[maxn], ok;
bool dp[maxn][maxn];

void DFS(int x, int c){
	col[x] = c;
	used[x] = 1;
	nn++;
	cnt += col[x];

	for(int i = 1; i <= n; i++){
		if(adj[x][i] && used[i] && col[x] == col[i])
			ok = 0;

		if(adj[x][i] == 1 && !used[i])
			DFS(i, 1 - c);
	}
}

void fun(int x, int diff){
	diff = abs(diff);

	if(dp[x][diff] == 1)
		return;

	dp[x][diff] = 1;

	if(x == comp.size())
		return;
	
	int cur = abs(comp[x].fi - comp[x].se);
	fun(x + 1, diff - cur);
	fun(x + 1, diff + cur);
}

int cost(int x){
	return x * (x - 1) / 2;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a][b] = 1;
		adj[b][a] = 1;
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(i == j)
				continue;

			adj[i][j] = 1 - adj[i][j];
		}
	}

	ok = 1;
	for(int i = 1; i <= n; i++){
		if(!used[i]){
			nn = cnt = 0;
			DFS(i, 0);
			comp.pb(mp(nn - cnt, cnt));
		}
	}

	if(!ok){
		printf("-1\n");
		return 0;
	}

	fun(0, 0);

	int ans = INF;
	for(int i = 0; i <= n; i++){
		if(dp[comp.size()][i]){
			int x = (n - i) / 2;
			int y = n - x;
			ans = min(ans, cost(x) + cost(y));
		}
	}

	printf("%d\n", ans);
	return 0;
}