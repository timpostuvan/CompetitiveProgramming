#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111
#define SQRT 350

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> adj[maxn], from[maxn];
vector<pii> d[maxn];
int in[maxn], in1[maxn], dep[maxn];
bool here[maxn], used[maxn];

vector<int> v;
vector<pii> ret;

vector<pii> merge(vector<pii> &a, vector<pii> &b){
	ret.clear();

	int inda = 0, indb = 0;
	while(inda < a.size() && indb < b.size()){
		pii l = a[inda];
		pii d = mp(b[indb].fi + 1, b[indb].se);
		if(d.se == -1)
			d.fi = -1;

		if(l >= d){
			ret.pb(l);
			inda++;
			continue;
		}

		if(l < d){
			ret.pb(d);
			indb++;
			continue;
		}
	}

	while(inda < a.size()){
		pii l = a[inda];
		ret.pb(l);
		inda++;
	}

	while(indb < b.size()){
		pii d = mp(b[indb].fi + 1, b[indb].se);
		if(d.se == -1)
			d.fi = -1;

		ret.pb(d);
		indb++;
	}

	int pos = 0;
	int sz = ret.size();

	for(int i = 0; i < sz; i++){
		int num = ret[i].se;
		if(!here[num]){
			here[num] = 1;
			ret[pos++] = ret[i];
		}
	}

	for(int i = 0; i < pos; i++){
		int num = ret[i].se;
		here[num] = 0;
	}

	while(ret.size() >= pos)
		ret.pop_back(); 

	ret.resize(SQRT + 5, mp(-1, -1));
	return ret;
}

void DFS(int x){
	used[x] = 1;
	for(int v : from[x]){
		in[v]++;
		if(!used[v])
			DFS(v);
	}
}


int main(){
	int n, m,  q;
	scanf("%d%d%d", &n,  &m, &q);
	for(int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		in[b]++;
		from[b].pb(a);
	}

	queue<int> qq;
	for(int i = 1; i <= n; i++){
		d[i].resize(SQRT + 5, mp(-1, -1));
		d[i][0] = mp(0, i);
		if(in[i] == 0)
			qq.push(i);
	}

	while(!qq.empty()){
		int x = qq.front();
		qq.pop();

		for(int v : adj[x]){
			in[v]--;
			if(in[v] == 0)
				qq.push(v);
		}

		for(int v : from[x]){
			d[x] = merge(d[x], d[v]);
		}
	}

	while(q--){
		v.clear();

		int x, num;
		scanf("%d%d", &x, &num);
		for(int i = 0; i < num; i++){
			int a;
			scanf("%d", &a);
			v.pb(a);
			here[a] = 1;
		}

		if(num < SQRT){
			for(int i = 0; i < SQRT + 5; i++){
				int num = d[x][i].se;
				if(!here[num]){
					printf("%d\n", d[x][i].fi);
					break;
				}
			}
		} 
		if(num >= SQRT){	
			int ans = -1;
			queue<int> que;
			que.push(x);

			memset(in, 0, sizeof(in));
			memset(used, 0, sizeof(used));

			DFS(x);
			
			memset(dep, 0, sizeof(dep));

			while(que.size()){
				int u = que.front();
				que.pop();

				for(int v : from[u]){
					in[v]--;
					if(in[v] == 0)
						que.push(v);
				}

				for(int v : adj[u])
					dep[u] = max(dep[u], dep[v] + 1);	

				if(u == x)
					dep[u] = 0;				

				if(!here[u])
					ans = max(ans, dep[u]);
			}

			printf("%d\n", ans);
		} 

		for(int i : v)
			here[i] = 0;
	}

	return 0;
}