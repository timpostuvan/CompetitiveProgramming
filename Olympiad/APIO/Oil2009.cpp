/*
Idea:
- Three squares can always be separated in non-intersectng territories
- We can choose "middle" square (corners (i, j), (i + k - 1, j), (i, j + k - 1) (i + k - 1, j + k - 1))
and than pick two adjacent edges to divide plane (for example division is (i, j) - (i, m) and  (i, j) - (n, j))
- We choose the best square in both territories (this is simple since they do not intersect - 2D prefix sum/maximum)
- We try all possible "middle" squares and all 4 rotations (pairs of edges)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1611

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

ll arr[maxn][maxn];
ll pre[maxn][maxn], dp1[maxn][maxn], dp2[maxn][maxn];
int n, m, k;

ll square(int x1, int y1, int x2, int y2){
	if(x1 <= 0 || y1 <= 0 || x2 <= 0 || y2 <= 0)
		return -INF;

	if(x1 > n || y1 > m || x2 > n || y2 > m)
		return -INF;

	ll ret = pre[x2][y2] - pre[x2][y1 - 1] - pre[x1 - 1][y2] + pre[x1 - 1][y1 - 1];
	return ret;
}

ll get(int x, int y, ll pos[maxn][maxn]){
	if(x <= 0 || y <= 0 || x > n || y > m)
		return -INF;

	return pos[x][y];
}

ll solve_right_down_left_up(){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			dp1[i][j] = square(i, j, i + k - 1, j + k - 1);
			dp2[i][j] = square(i - k + 1, j - k + 1, i, j);
		}
	}

	for(int i = n; i >= 1; i--){
		for(int j = m; j >= 1; j--)
			dp1[i][j] = max(dp1[i][j], max(dp1[i + 1][j], dp1[i][j + 1]));
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++)
			dp2[i][j] = max(dp2[i][j], max(dp2[i - 1][j], dp2[i][j - 1]));
	}

	ll ret = -INF;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			ll cur = square(i, j, i + k - 1, j + k - 1);
			cur += max(get(i, j + k, dp1), get(i + k, j, dp1)) + max(get(i - 1, m, dp2), get(n, j - 1, dp2));
			ret = max(ret, cur);
		}
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			ll cur = square(i, j, i + k - 1, j + k - 1);
			cur += max(get(1, j + k, dp1), get(i + k, 1, dp1)) + max(get(i - 1, j + k - 1, dp2), get(i + k - 1, j - 1, dp2)) ;
			ret = max(ret, cur);
		}
	}

	return ret;
}

ll solve_left_down_right_up(){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			dp1[i][j] = square(i - k + 1, j, i, j + k - 1);
			dp2[i][j] = square(i, j - k + 1, i + k - 1, j);
		}
	}

	for(int i = 1; i <= n; i++){
		for(int j = m; j >= 1; j--)
			dp1[i][j] = max(dp1[i][j], max(dp1[i - 1][j], dp1[i][j + 1]));
	}

	for(int i = n; i >= 1; i--){
		for(int j = 1; j <= m; j++)
			dp2[i][j] = max(dp2[i][j], max(dp2[i + 1][j], dp2[i][j - 1]));
	}

	ll ret = -INF;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			ll cur = square(i - k + 1, j, i, j + k - 1);
			cur += max(get(i, j + k, dp1), get(i - k, j, dp1)) + max(get(i + 1, m, dp2), get(1, j - 1, dp2));
			ret = max(ret, cur);
		}
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			ll cur = square(i - k + 1, j, i, j + k - 1);
			cur += max(get(i - k, 1, dp1), get(n, j + k, dp1)) + max(get(i - k + 1, j - 1, dp2), get(i + 1, j + k - 1, dp2));
			ret = max(ret, cur);
		}
	}
	return ret;
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%lld", arr[i] + j);
			pre[i][j] = arr[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
		}
	}

	ll ans = 0;
	ans = max(ans, solve_right_down_left_up());
	ans = max(ans, solve_left_down_right_up());

	printf("%lld\n", ans);
	return 0;
}