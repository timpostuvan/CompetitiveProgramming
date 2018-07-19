/*
Idea:
- http://codeforces.com/blog/entry/57637?#comment-413356 (Problem 4)
*/

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
typedef pair<ll, ll> pii;

ll len[maxn], d1[maxn], d2[maxn], min1[maxn], min2[maxn];
bool mark[maxn];
vector<pii> adj[maxn], here;

void find_path(int zac, ll d[]){	
	priority_queue<pii> pq;
	for(int i = 0; i < maxn; i++)
		d[i] = INF;

	d[zac] = 0;
	pq.push(mp(0, zac));

	while(!pq.empty()){
		int x = pq.top().se;
		ll val = -pq.top().fi;
		pq.pop();

		if(val > d[x])
			continue;

		for(pii v : adj[x]){
			if(d[v.fi] > d[x] + v.se){
				d[v.fi] = d[x] + v.se;
				pq.push(mp(-d[v.fi], v.fi));
			}
		}
	}
}

void on_shortest_path(int s, int t, ll d[]){
	queue<int> q;
	q.push(t);
	mark[t] = 1;

	while(!q.empty()){
		int x = q.front();
		q.pop();
		here.pb(mp(d[x], x));

		for(pii v : adj[x]){
			if(!mark[v.fi] && d[x] == d[v.fi] + v.se){
				mark[v.fi] = 1;
				q.push(v.fi);
			}
		}
	}
}

int main(){
	int n, m, s, t, u, v;
	scanf("%d%d%d%d%d%d", &n, &m, &s, &t, &u, &v);
	for(int i = 0; i < m; i++){
		int a, b; ll c;
		scanf("%d%d%lld", &a, &b, &c);
		adj[a].pb(mp(b, c));
		adj[b].pb(mp(a, c));
	}

	find_path(s, len);
	find_path(u, d1);
	find_path(v, d2);

	on_shortest_path(s, t, len);

	sort(here.begin(), here.end());
	memset(mark, 0, sizeof(mark));

	ll ans = d1[v];
	for(int i = 0; i < here.size(); i++){
		int x = here[i].se;
		mark[x] = 1;
		min1[x] = d1[x];
		min2[x] = d2[x];

		for(pii cur : adj[x]){
			if(mark[cur.fi]){
				min1[x] = min(min1[x], min1[cur.fi]);
				min2[x] = min(min2[x], min2[cur.fi]);
			}
		}

		ans = min(ans, d1[x] + min2[x]);
		ans = min(ans, d2[x] + min1[x]);
	}

	printf("%lld\n", ans);
	return 0;
}