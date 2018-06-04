/*
Idea:
- We can use at most one white cell from every column and every row
- The goal is to use as many cells as possible and for that we can use maximum bipartite matching
- In bipartite graph we add an edge between row x and column y if there is a white cell with coordiantes (x, y) 
- If there are not any black cells the answer is 2 * (n - 1) but for every white cell answer is decreased by 1 (note that answer can't be less than n - 1)
*/

#include "tour.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 311

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> adj[2 * maxn];
int match[2 * maxn];
bool used[2 * maxn];

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

int getShortestTour(int N, vector<string> S){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(S[i][j] == '.'){
				adj[i].pb(N + j);
				adj[N + j].pb(i);
			}
		}
	}

	int max_matching = 0;

	memset(match, -1, sizeof(match));
	for(int i = N - 1; i >= 0; i--){
		memset(used, 0, sizeof(used));
		max_matching += AUG(i);
	}

	int ans = max(2 * (N - 1) - max_matching, N - 1);
	return ans;
}