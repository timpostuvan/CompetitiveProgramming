/*
Idea:
- Only the last change in every cell contributes to the answer, so we can reverse queries and paint only cells which weren't painted before
- Once we color row/column, whole row/column is painted so it is pointless to check whether there are any unpainted cells
*/

#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF (1e9)
#define maxn 6011

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > q;
bool row[maxn], col[maxn];
bool used[maxn][maxn];



int main(){
	int n, p;
	scanf("%d%d", &n, &p);
	for(int i = 0; i < p; i++){
		char str[5];
		int v, x;
		scanf("%s%d%d", str, &v, &x);
		q.pb({str[0] == 'R' ? 1 : 2, v, x});
	}

	reverse(q.begin(), q.end());
	ll ans = 0;

	for(int i = 0; i < q.size(); i++){
		int type = q[i][0];
		int v = q[i][1];
		int x = q[i][2];

		ll sz = 0;
		if(type == 1){
			if(row[v])
				continue;

			for(int i = 1; i <= n; i++){
				sz += 1 - used[v][i];
				used[v][i] = 1;
			}

			row[v] = 1;
		}

		if(type == 2){
			if(col[v])
				continue;

			for(int i = 1; i <= n; i++){
				sz += 1 - used[i][v];
				used[i][v] = 1;
			}

			col[v] = 1;
		}

		ans += 1LL * sz * x; 
	}

	printf("%lld\n", ans);

	return 0;
}