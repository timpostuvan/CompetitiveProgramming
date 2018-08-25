/*
Idea:
- http://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2017/2017-open-amusement_park-sol-en.pdf
*/

#include "Ioi.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 10011

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;


vector<int> adj1[maxn], tree1[maxn], one1, two1, v1;
int col1[maxn], par1[maxn], dep1[maxn], max_dep1, max_ind1, cnt1;
bool used1[maxn];

void DFS1(int x){
	used1[x] = 1;
	if(max_dep1 < dep1[x]){
		max_dep1 = dep1[x];
		max_ind1 = x;
	}

	for(int u : adj1[x]){
		if(!used1[u]){
			tree1[x].pb(u);
			dep1[u] = dep1[x] + 1;
			par1[u] = x;
			DFS1(u);
		}
	}
}

void getSmall(int x){
	v1.pb(x);

	int last = -1;
	for(int u : tree1[x]){
		if(used1[u]){
			last = u;
			continue;
		}

		if(cnt1 <= 0)
			continue;

		cnt1--;
		col1[u] = Move(u);
		getSmall(u);
		col1[x] = Move(x);
	}

	if(last != -1){
		col1[last] = Move(last);
		getSmall(last);
	}
}


long long Ioi(int N, int M, int A[], int B[], int P, int V, int T){
	ll ans = 0;
	memset(col1, 0, sizeof(col1));
	for(int i = 0; i < M; i++){
		adj1[A[i]].pb(B[i]);
		adj1[B[i]].pb(A[i]);
	}

	par1[0] = -1;
	dep1[0] = 0;
	max_dep1 = -1;
	DFS1(0);

	memset(used1, 0, sizeof(used1));
	int cur = max_ind1;
	while(cur != -1){
		one1.pb(cur);
		used1[cur] = 1;
		cur = par1[cur];
	}

	reverse(one1.begin(), one1.end());

	if(max_dep1 >= 59){
		if(dep1[P] >= 59){	// just go up
			int cur = P;
			int pos = dep1[cur] % 60;
			int val = V;

			ans += (1LL << pos) * val;
			for(int i = 1; i < 60; i++){
				cur = par1[cur];
				val = Move(cur);
				pos = dep1[cur] % 60;
				ans += (1LL << pos) * val;
			}
		}
		else{
			cur = par1[P];	// go to 1 and then down
			while(cur != -1){
				V = Move(cur);
				cur = par1[cur];
			}

			int cur = 0;
			int pos = dep1[cur] % 60;
			int val = V;
			ans += (1LL << pos) * val;
			for(int i = 1; i < 60; i++){
				cur = one1[i];
				val = Move(cur);
				pos = dep1[cur] % 60;
				ans += (1LL << pos) * val;
			}
		}
	}
	else{
		int cur = par1[P];	// Move to 1 and then do DFS traversal
		while(cur != -1){
			V = Move(cur);
			cur = par1[cur];
		}

		cnt1 = 60 - one1.size();
		col1[0] = V; 
		getSmall(0);

		sort(v1.begin(), v1.end());
		for(int i = 0; i < v1.size(); i++)
			ans += col1[v1[i]] * (1LL << i);
	}
	return ans;
}