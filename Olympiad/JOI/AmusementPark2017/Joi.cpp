/*
Idea:
- http://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2017/2017-open-amusement_park-sol-en.pdf
*/

#include "Joi.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 10111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> adj[maxn], tree[maxn], one, two, v;
int col[maxn], par[maxn], dep[maxn], max_dep, max_ind, cnt;
bool used[maxn];

void DFS(int x){
	used[x] = 1;
	if(max_dep < dep[x]){
		max_dep = dep[x];
		max_ind = x;
	}

	for(int u : adj[x]){
		if(!used[u]){
			tree[x].pb(u);
			dep[u] = dep[x] + 1;
			par[u] = x;
			DFS(u);
		}
	}
}

void colorBig(int x, ll num){
	int pos = dep[x] % 60;
	int val = (num >> pos) & 1;
	col[x] = val;

	for(int u : tree[x])
		colorBig(u, num);
}

void colorSmall(int x){
	v.pb(x);

	int last = -1;
	for(int u : tree[x]){
		if(used[u]){
			last = u;
			continue;
		}

		if(cnt <= 0)
			continue;
		
		cnt--;
		colorSmall(u);
	}

	if(last != -1)
		colorSmall(last);
}

void Joi(int N, int M, int A[], int B[], long long X, int T){
	memset(col, 0, sizeof(col));
	for(int i = 0; i < M; i++){
		adj[A[i]].pb(B[i]);
		adj[B[i]].pb(A[i]);
	}

	par[0] = -1;
	dep[0] = 0;
	max_dep = -1;
	DFS(0);

	if(max_dep >= 59)
		colorBig(0, X);
	else{
		memset(used, 0, sizeof(used));
		int cur = max_ind;
		while(cur != -1){
			one.pb(cur);
			used[cur] = 1;
 			cur = par[cur];
		}

		cnt = 60 - one.size();
		colorSmall(0);

		sort(v.begin(), v.end());

		for(int i = 0; i < v.size(); i++)
			col[v[i]] = (X >> i) & 1;
	}

	for(int i = 0; i < N; i++)
		MessageBoard(i, col[i]);
}