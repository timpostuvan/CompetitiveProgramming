/*
Idea:
- http://codeforces.com/blog/entry/60701?#comment-446462 (Exact Walks)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 59)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int adj[maxn][maxn], val[maxn];
bool can[maxn];

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a][b] = adj[b][a] = 1;
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			for(int k = 1; k <= n; k++){
				if(i == j || j == k || i == k)
					continue;

				if(adj[i][j] && adj[j][k] && adj[k][i])
					can[i] = 1;
			}
		}
	}

	bool ans = 0;
	for(int i = 1; i <= n; i++){
		if(can[i])
			continue;

		ans = 1;
		for(int j = 1; j <= n; j++){
			if(adj[i][j])
				val[j] = 2;
			else
				val[j] = 1;
		}
		break;
	}

	if(ans){
		printf("YES\n");
		for(int i = 1; i <= n; i++)
			printf("%d ", val[i]);
	}
	else
		printf("NO\n");

		
	return 0;
}