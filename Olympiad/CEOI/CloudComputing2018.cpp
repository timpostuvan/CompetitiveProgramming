/*
Idea:
- https://ceoi2018.pl/wp-content/uploads/2018/08/solutions_day1.pdf (Cloud Computing)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 2001
#define maxc 50

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

ll dp[maxn * maxc];
vector<vector<int> > v;

int main(){
	int n, m;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int c, f, val;
		scanf("%d%d%d", &c, &f, &val);
		v.pb({f, c, -val});
	}

	scanf("%d", &m);
	for(int i = 0; i < m; i++){
		int c, f, val;
		scanf("%d%d%d", &c, &f, &val);
		v.pb({f, -c, val});
	}

	stable_sort(v.begin(), v.end());

	for(int i = 0; i < maxn * maxc; i++)
		dp[i] = -INF;

	dp[0] = 0;
	for(int i = v.size() - 1; i >= 0; i--){
		if(v[i][1] > 0){
			for(int j = maxn * maxc - 1; j >= 0; j--){
				if(dp[j] == -INF || (j + v[i][1] >= maxn * maxc))
					continue;

				dp[j + v[i][1]] = max(dp[j + v[i][1]], dp[j] + v[i][2]);
			}
		}

		else{
			for(int j = 0; j < maxn * maxc; j++){
				if(dp[j] == -INF || (j + v[i][1] < 0))
					continue;

				dp[j + v[i][1]] = max(dp[j + v[i][1]], dp[j] + v[i][2]);
			}
		}
	}

	ll ans = -INF;
	for(int j = 0; j < maxn * maxc; j++)
		ans = max(ans, dp[j]);

	printf("%lld\n", ans);
	return 0;
}