/*
Idea:
- For a fixed starting point the placement of tiles is always the same
- Because of that we can use binary lifting on number of tiles added 
- par[x][i] is the index of first tile that is not covered if we start at tile x and use 2 ^ i tiles
*/

#include "tile.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 300111
#define logn 33

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<pii> v;
int par[maxn][logn], m;

void init(int N, int K, int Q, int M, vector<int> A){
	m = M;

	for(int i = 0; i < M; i++)
		v.pb(mp(A[i], i));

	v.pb(mp(2 * N, M));

	for(int i = 0; i < M; i++){
		auto it = upper_bound(v.begin(), v.end(), mp(A[i] + K, -1));
		par[i][0] = it -> se;
	}

	par[M][0] = M;

	for(int j = 1; j < logn; j++){
		for(int i = 0; i <= M; i++){
			par[i][j] = par[par[i][j - 1]][j - 1];
		}
	}
}

int getNumberOfSpecialTiles(int L, int R){
	int st = upper_bound(v.begin(), v.end(), mp(L, -1)) - v.begin();
	int en = upper_bound(v.begin(), v.end(), mp(R + 1, -1)) - v.begin();

	if(st == en)
		return 0;

	int ans = 0, cur = st;
	for(int i = logn - 1; i >= 0; i--){
		if(cur != INF && par[cur][i] < en){
			ans += (1 << i);
			cur = par[cur][i];
		}
	}

	return ans + 1;
}