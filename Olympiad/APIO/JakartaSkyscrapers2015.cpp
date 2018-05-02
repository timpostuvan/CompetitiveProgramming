#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 30111
#define SQRT 150

typedef long long ll;
typedef long double ld;

vector<pair<pair<int, int>, int> > adj[maxn][SQRT + 10];
vector<int> doge[maxn];
ll d[maxn][SQRT + 10];

priority_queue<pair<int, pair<int, int> > > pq;

int main(){
	for(int i = 0; i < maxn; i++)
		for(int j = 0; j < SQRT; j++)
			d[i][j] = INF;


	int n, m, z, k;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++){
		int b, p;
		scanf("%d%d", &b, &p);

		if(i == 0)
			z = b;
	
		if(i == 1)
			k = b;

		if(p < SQRT)
			adj[b][0].pb(mp(mp(b, p), 0));

		if(p >= SQRT)
			doge[b].pb(p);
	}

	if(m == 1){
		printf("-1\n");
		return 0;
	}

	d[z][0] = 0;
	pq.push(mp(0, mp(z, 0)));
	while(!pq.empty()){
		int x = pq.top().se.fi;
		int y = pq.top().se.se;
		int val = -pq.top().fi;
		pq.pop();

		if(val > d[x][y])
			continue;

		if(x == k)
			break;

		if(x + y < n){
			if(d[x + y][y] > d[x][y] + 1){
				d[x + y][y] = d[x][y] + 1;
				pq.push(mp(-d[x + y][y], mp(x + y, y)));
			}

			if(d[x + y][0] > d[x][y] + 1){
				d[x + y][0] = d[x][y] + 1;
				pq.push(mp(-d[x + y][0], mp(x + y, 0)));
			}
		}

		if(x - y >= 0){
			if(d[x - y][y] > d[x][y] + 1){
				d[x - y][y] = d[x][y] + 1;
				pq.push(mp(-d[x - y][y], mp(x - y, y)));
			}

			if(d[x - y][0] > d[x][y] + 1){
				d[x - y][0] = d[x][y] + 1;
				pq.push(mp(-d[x - y][0], mp(x - y, 0)));
			}
		}

		for(auto v : adj[x][y]){
			int a = v.fi.fi;
			int b = v.fi.se;
			int t = v.se;

			if(d[a][b] > d[x][y] + t){
				d[a][b] = d[x][y] + t;
				pq.push(mp(-d[a][b], mp(a, b)));
			}
		}

		if(y == 0){
			for(int v : doge[x]){
				int p = v;

				for(int j = 1; x + j * p < n; j++){
					int a = x + j * p;

					if(d[a][0] > d[x][y] + j){
						d[a][0] = d[x][y] + j;
						pq.push(mp(-d[a][0], mp(a, 0)));
					}
				}

				for(int j = 1; x - j * p >= 0; j++){
					int a = x - j * p;

					if(d[a][0] > d[x][y] + j){
						d[a][0] = d[x][y] + j;
						pq.push(mp(-d[a][0], mp(a, 0)));
					}
				}
			}
		}
	}

	if(d[k][0] == INF)
		d[k][0] = -1;

	printf("%lld\n", d[k][0]);	
	return 0;
}