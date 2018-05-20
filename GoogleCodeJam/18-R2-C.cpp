#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> adj[2 * maxn];
int match[2 * maxn];
bool used[2 * maxn];
int arr[maxn][maxn];

void init(){
	for(int i = 0; i < 2 * maxn; i++)
		adj[i].clear();

	memset(match, -1, sizeof(match));
}

int AUG(int x){
	if(used[x])
		return 0;

	used[x] = 1;
	for(int v : adj[x]){
		if(match[v] == -1 || AUG(match[v])){
			match[v] = x;
			return 1;
		}
	}
	return 0;
}

int solve(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			scanf("%d", arr[i] + j);
	}

	int max_matching = 0;
	for(int col = -n; col <= n; col++){
		init();
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(arr[i][j] == col){
					adj[i].pb(n + j);
					adj[n + j].pb(i);
				}
			}
		}

		for(int i = 0; i < n; i++){
			memset(used, 0, sizeof(used));
			max_matching += AUG(i);
		}
	}

	int ans = n * n - max_matching;
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; i++)
		printf("Case #%d: %d\n", i, solve());

	return 0;
}