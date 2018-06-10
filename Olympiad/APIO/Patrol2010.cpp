/*
Idea:
- http://apio-olympiad.org/2010/solutions.pdf
- dp1[x] - the best path
- dp15[x] - the best path + path which ends at node x (x is the node with the lowest depth)
- dp2[x] - the two best paths
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
typedef pair<int, int> pii;

vector<int> adj[maxn];
int dep[maxn], max_dep[maxn], dp1[maxn], dp15[maxn], dp2[maxn];

void DFS(int x, int p){
	max_dep[x] = dep[x];

	vector<pii> cur, two;
	for(int v: adj[x]){
		if(v == p)
			continue;

		dep[v] = dep[x] + 1;
		DFS(v, x);

		max_dep[x] = max(max_dep[x], max_dep[v]);
		dp1[x] = max(dp1[x], dp1[v]);
		dp15[x] = max(dp15[x], dp15[v]);
		dp2[x] = max(dp2[x], dp2[v]);

		cur.pb(mp(max_dep[v], v));
		two.pb(mp(dp1[v], v));
	}

	sort(cur.begin(), cur.end());
	reverse(cur.begin(), cur.end());

	sort(two.begin(), two.end());
	reverse(two.begin(), two.end());

	if(cur.size() >= 2){
		dp1[x] = max(dp1[x], cur[0].fi + cur[1].fi - 2 * dep[x]);
		dp2[x] = max(dp2[x], two[0].fi + two[1].fi);

		for(int v : adj[x]){
			if(v == p)
				continue;

			int add15 = (cur[0].se == v) ? cur[1].fi : cur[0].fi;
			dp15[x] = max(dp15[x], dp1[v] + add15);

			dp2[x] = max(dp2[x], dp15[v] + add15 - 2 * dep[x]);

            if(cur.size() >= 3){
                int add2 = cur[0].fi + cur[1].fi;
                if(cur[0].se == v)
                    add2 += cur[2].fi - cur[0].fi;

                if(cur[1].se == v)
                    add2 += cur[2].fi - cur[1].fi;

                dp2[x] = max(dp2[x], dp1[v] + add2 - 2 * dep[x]);
            }
		}
	}

	if(cur.size() >= 3)
		dp15[x] = max(dp15[x], cur[0].fi + cur[1].fi + cur[2].fi - 2 * dep[x]);

	if(cur.size() >= 4)
		dp2[x] = max(dp2[x], cur[0].fi + cur[1].fi + cur[2].fi + cur[3].fi - 4 * dep[x]);
}

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n - 1; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}

	dep[1] = 0;
	DFS(1, -1);

	if(k == 1)
		printf("%d\n", 2 * (n - 1) - dp1[1] + k);

	if(k == 2)
		printf("%d\n", 2 * (n - 1) - dp2[1] + k);

	return 0;
}