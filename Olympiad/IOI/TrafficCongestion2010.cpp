#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 9)
#define maxn 1000111

typedef long long ll;
typedef long double ld;

vector<int> adj[maxn];
int par[maxn];
int sz[maxn];

void DFS(int x, int p){
	par[x] = p;
	for(int v : adj[x]){
		if(v == p)
			continue;
		DFS(v, x);
		sz[x] += sz[v];
	}
}

int LocateCentre(int n, int *arr, int *a, int *b){
	for(int i = 0; i < n; i++)
		sz[i] = arr[i];

	for(int i = 0; i < n - 1; i++){
		adj[a[i]].pb(b[i]);
		adj[b[i]].pb(a[i]);
	}

	DFS(0, -1);
	int ans = -1, val = 2e9 + 1;
	for(int i = 0; i < n; i++){
		int maks = sz[0] - sz[i];
		for(int x : adj[i]){
			if(x == par[i])
				continue;
			maks = max(maks, sz[x]);
		}
		if(maks < val){
			val = maks;
			ans = i;
		}
	}
	return ans;
}

/*
int arr[maxn];
int a[maxn], b[maxn];

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", arr + i);
	for(int i = 0; i < n - 1; i++){
		scanf("%d%d", a + i, b + i);
	}
	printf("%d\n", LocateCentre(n, arr, a, b));
	return 0;
}
*/