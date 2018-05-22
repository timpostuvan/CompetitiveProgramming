#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 20)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> adj[maxn], cyc, path, possible;
int h[maxn], hh[maxn], highest[maxn], vis[maxn];
bool cyc_found;


void DFS(int x){
	vis[x] = 1;
	path.pb(x);
	hh[x] = h[x];
	highest[x] = x;
	for(int v : adj[x]){
		if(vis[v] == 0){
			h[v] = h[x] + 1;
			DFS(v);

			if(hh[v] < hh[x]){
				hh[x] = hh[v];
				highest[x] = highest[v];
			}
			continue;
		}

		if(vis[v] == 1){
			if(!cyc_found){
				cyc.assign(path.begin() + h[v], path.end());
				possible.assign(cyc.size() + 1, 0);
				cyc_found = 1;
			}
			else{
				int l = 0, d = cyc.size(), mid;
				while(l < d){
					mid = (l + d) / 2;
					if(vis[cyc[mid]] == 1)
						l = mid + 1;
					else
						d = mid;
				}

				cyc.resize(d);
				l = 0; d = cyc.size();
				while(l < d){
					mid = (l + d) / 2;
					if(h[cyc[mid]] < h[v])
						l = mid + 1;
					else
						d = mid;
				}
				possible[0]--;
				possible[d]++;
			}

			if(h[v] < hh[x]){
				hh[x] = h[v];
				highest[x] = v;
			}
			continue;
		}

		if(vis[v] == 2){
			if(vis[highest[v]] == 1){
				int l = 0, d = cyc.size(), mid;
				while(l < d){
					mid = (l + d) / 2;
					if(vis[cyc[mid]] == 1)
						l = mid + 1;
					else
						d = mid;
				}

				possible[d]--;

				l = 0; d = cyc.size();
				while(l < d){
					mid = (l + d) / 2;
					if(h[cyc[mid]] < h[v])
						l = mid + 1;
					else
						d = mid;
				}
				possible[d]++;

				if(hh[v] < hh[x]){
					hh[x] = hh[v];
					highest[x] = highest[v];
				}
			}
			continue;
		}
	}
	path.pop_back();
	vis[x] = 2;
}


int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
	}

	for(int i = 1; i <= n; i++){
		if(!vis[i])
			DFS(i);
	}

	int sum = 0;
	for(int i = 0; i < cyc.size(); i++){
		sum += possible[i];
		if(sum >= 0){
			printf("%d\n", cyc[i]);
			return 0;
		}
	}

	printf("-1\n");
	return 0;
}