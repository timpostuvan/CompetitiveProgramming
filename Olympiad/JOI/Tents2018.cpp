#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 3111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

ll dp[maxn][maxn];

ll fun(int x, int y){
	if(x < 0 || y < 0)
		return 0;

	if(x == 0 || y == 0)
		return 1;

	ll &cur = dp[x][y];
	if(cur != -1)
		return cur;

	cur = 0;
	cur = (cur + 1LL * fun(x - 1, y)) % MOD; 									// izpustimo eno vrstico
	cur = (cur + 4 * y * fun(x - 1, y - 1)) % MOD;								// < v vse 4 smeri

	cur = (cur + 1LL * y * (x - 1) * fun(x - 2, y - 1)) % MOD;					// < > vertikalno
	cur = (cur + 1LL * y * (y - 1) / 2LL * fun(x - 1, y - 2)) % MOD;			// < > horizontalno
	return cur;
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);

	ll ans = 0;

	memset(dp, -1, sizeof(dp));

	printf("%lld\n", (fun(n, m) + MOD - 1) % MOD);
	return 0;
}