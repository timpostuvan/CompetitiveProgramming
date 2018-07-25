/*
Idea:
- http://ioi2017.org/tasks/editorial/train.pdf
*/

#include "train.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 5111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

vector<int> adj[maxn], ch, start;
bool used[maxn];

int deg[maxn], cur_deg[maxn], mark[maxn];
int owner[maxn];

queue<int> q;

void BFS(int n, int col){
	for(int i = 0; i < n; i++){
		mark[i] = 0;
		cur_deg[i] = (owner[i] == col) ? 1 : deg[i];
	}

	for(int v : start){
		mark[v] = 1;
		q.push(v);
	}

	while(!q.empty()){
		int x = q.front();
		q.pop();

		for(int v : adj[x]){
			if(used[v] || mark[v])
				continue;

			cur_deg[v]--;
			if(cur_deg[v] == 0){
				mark[v] = 1;
				q.push(v);
			}
		}
	}
}


vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v){
	int n = a.size();
	for(int i = 0; i < n; i++)
		owner[i] = a[i];

	for(int i = 0; i < n; i++){
		if(r[i])
			ch.pb(i);
	}

	for(int i = 0; i < u.size(); i++){
		adj[v[i]].pb(u[i]);
		deg[u[i]]++;
	}

	while(1){
		start.clear();
		for(int i = 0; i < ch.size(); i++){
			if(!used[ch[i]])
				start.pb(ch[i]);
		}

		BFS(n, 1);

		start.clear();
		for(int i = 0; i < n; i++){
			if(!used[i] && !mark[i])
				start.pb(i);
		}

		BFS(n, 0);

		bool done = 1;
		for(int i = 0; i < n; i++){
			if(!used[i] && mark[i]){
				used[i] = 1;
				done = 0;
				for(int v : adj[i])
					deg[v]--;
			}
		}

		if(done)
			break;
	}

	vector<int> ans;
	for(int i = 0; i < n; i++)
		ans.pb(!used[i]);

	return ans;
}