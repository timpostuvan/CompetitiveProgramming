#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (int) (2 * 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 2111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

int pos[maxn], large[maxn], small[maxn];
int dp[maxn][maxn];
int n, p, q;

int f(int x, int big){
	if(big > q)
		return INF;

	if(x == n){
		if(big <= q)
			return 0;

		return INF;
	}

	int &cur = dp[x][big];
	if(cur != -1)
		return cur;

	cur = INF;
	cur = min(cur, f(large[x], big + 1));
	cur = min(cur, f(small[x], big) + 1);
	return cur;
}

bool check(int dist){
	if(p + q >= n)
		return 1;
	
	int ind = n;
	for(int i = n - 1; i >= 0; i--){
		while(ind - 1 >= 0 && pos[ind - 1] - pos[i] >= 2 * dist)
			ind--;

		large[i] = ind;
	}

	ind = n;
	for(int i = n - 1; i >= 0; i--){
		while(ind - 1 >= 0 && pos[ind - 1] - pos[i] >= dist)
			ind--;

		small[i] = ind;
	}

	memset(dp, -1, sizeof(dp));
	if(f(0, 0) <= p)
		return 1;

	return 0;
}

int main(){
	scanf("%d%d%d", &n, &p, &q);
	for(int i = 0; i < n; i++)
		scanf("%d", pos + i);

	sort(pos, pos + n);
	pos[n] = INF;

	int l = 1, d = INF, mid, ans = -1;
	while(l <= d){
		mid = (l + d) / 2;
		if(check(mid)){
			ans = mid;
			d = mid - 1;
		}
		else 
			l = mid + 1;
	}

	printf("%d\n", ans);
	return 0;
}