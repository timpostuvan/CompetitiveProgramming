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
int ans;

int DFS(int x, int p){
	int cur = 0;	
	for(int v : adj[x]){
		if(v == p)
			continue;

		int tren = DFS(v, x);
		ans += (1 - tren);
		cur += tren;
	}
	if(cur & 1)
		return 0;

	return 1;
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

	ans = 0;
	bool ok = 1 - DFS(1, -1);

	if(!ok){
		printf("-1\n");
		return 0;
	}

	printf("%d\n", ans);
	return 0;
}