/*
Idea:
- http://www.ioi2012.org/hints-for-tasks-of-day-1/index.html (Parachute rings)
- http://blog.brucemerry.org.za/2012/09/ioi-2012-day-1-analysis.html (Parachute Rings)
*/

#include "grader.h"
#include <bits/stdc++.h>

using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

bool is_end;

struct DSU{
	bool over;
	int n, owner, max_degree, type;
	set<int> cycles;
	int deg[maxn];
	int sz[maxn];
	int root[maxn];

	int rooting(int x){
		if(root[x] == x)
			return x;
		return root[x] = rooting(root[x]);
	}

	void addEdge(int a, int b){
		if(a == owner || b == owner || over == 1)
			return;

		int ra = rooting(a);
		int rb = rooting(b);
		deg[a]++; deg[a] = min(deg[a], 3);
		deg[b]++; deg[b] = min(deg[b], 3);

		max_degree = max(max_degree, max(deg[a], deg[b]));

		if(ra != rb){
			root[rb] = ra;
			sz[ra] += sz[rb];
		} 

		if(ra == rb)
			cycles.insert(ra);

		if(max_degree == 3 || cycles.size() > 1){
			over = 1;
			if(type == 4)
				is_end = 1;
		}

		if(type >= 3 && cycles.size() == 1){
			over = 1;
			if(type == 4)
				is_end = 1;
		}
	}

	void init(int nn, int x, int t, vector<pii> &edge){
		n = nn;
		owner = x;
		max_degree = over = 0;
		type = t;
		cycles.clear();
		for(int i = 0; i < maxn; i++){
			root[i] = i;
			deg[i] = 0;
			sz[i] = 1;
		}

		for(pii v : edge)
			addEdge(v.fi, v.se);
	}

	int getAns(){
		if(over)
			return 0;

		if(type == 2){
			if(max_degree <= 1)
				return n;

			if(max_degree == 2){
				if(cycles.size() == 0)
					return n;

				if(cycles.size() == 1)
					return sz[*cycles.begin()];
			}
		}

		if(type == 3 || type == 4)
			return 1;	
	}
} dsu[4];
 

bool start[6];
int deg[maxn], ind[5], n;
vector<pii> edge;
vector<int> adj[maxn];
pii cur_range;
int all_max_degree;


void Init(int N){
	n = N;
	is_end = 0;
	all_max_degree = 0;
	dsu[0].init(n, -1, 2, edge);
	memset(ind, -1, sizeof(ind));
	start[2] = 1;
	cur_range = mp(0, 0);
}
 
void Link(int A, int B){
	if(is_end)
		return;

	adj[A].pb(B);
	adj[B].pb(A);

	deg[A]++; deg[A] = min(deg[A], 4);
	if(ind[deg[A]] == -1)
		ind[deg[A]] = A;

	deg[B]++; deg[B] = min(deg[B], 4);
	if(ind[deg[B]] == -1)
		ind[deg[B]] = B;

	all_max_degree = max(all_max_degree, max(deg[A], deg[B]));

	if(all_max_degree == 3 && !start[3]){
		start[3] = 1;
		cur_range = mp(0, 3);
		int cnt = 0;
		dsu[cnt++].init(n, ind[3], 3, edge);
		for(int v : adj[ind[3]])
			dsu[cnt++].init(n, v, 3, edge);
	}

	if(all_max_degree == 4 && !start[4]){
		start[4] = 1;
		cur_range = mp(0, 0);
		dsu[0].init(n, ind[4], 4, edge);
	}

	edge.pb(mp(A, B));
	for(int i = cur_range.fi; i <= cur_range.se; i++)
		dsu[i].addEdge(A, B);
}
 
int CountCritical(){ 
	int ret = 0;
	for(int i = cur_range.fi; i <= cur_range.se; i++)
		ret += dsu[i].getAns();
	return ret;
}