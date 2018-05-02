#include "Boblib.h"
#include <cassert>
#include <cstdio>
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
vector<pii> edge;
vector<int> ord;
int id[maxn], in[maxn];


void Bob(int V, int U, int C[], int D[]){
	for(int i = 0; i < U; i++){
		adj[C[i]].pb(D[i]);
		in[D[i]]++;
	}

	queue<int> q;
	for(int i = 0; i < V; i++){
		if(in[i] == 0)
			q.push(i);
	}

	int cnt = 0;
	while(!q.empty()){
		int x = q.front();
		q.pop();

		id[x] = cnt++;
		ord.pb(x);

		for(int v : adj[x]){
			in[v]--;
			if(in[v] == 0)
				q.push(v);
		}
	}

	for(int i = 0; i < V - 1; i++){
		int x = ord[i];
		auto it = find(adj[x].begin(), adj[x].end(), ord[V - 1]);
		bool tonxt = 1;
		if(it != adj[x].end())
			tonxt = 0;

		for(int v : adj[x]){
			if(!tonxt && v == ord[i + 1])
				continue;

			if(v == ord[V - 1])
				continue;

			edge.pb(mp(id[x], id[v]));
		}
	}

	InitMap(V - 1, edge.size());
	for(pii i : edge)
		MakeMap(i.fi, i.se);
}