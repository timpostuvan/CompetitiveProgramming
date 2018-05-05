/*
Idea:
- If all subarrays of length 2 and 3 respect the constraints, whole array does as well (crucial observation)
- We do dp[i][j][k] - first i elements; j and k are in range [0, 1] -> 0 - positive, 1 - negative;
j is sign of (i - 1)th element, k is sign of (i - 2)th element 
- nxt keeps track of transitions so we can reconstruct the answer (backtracking) 
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 101111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

ll arr[maxn];
ll dp[maxn][2][2];
pii nxt[maxn][2][2];

int n;

ll fun(int x, int sign_1, int sign_2){
	if(x == n + 2)
		return 0;

	ll &cur = dp[x][sign_1][sign_2];
	if(cur != INF)
		return cur;

	ll val_prev_1 = arr[x - 1] * (sign_1 == 1 ? -1 : 1);
	ll val_prev_2 = arr[x - 2] * (sign_2 == 1 ? -1 : 1);

	if((val_prev_1 + arr[x] <= 0) || (val_prev_1 + val_prev_2 + arr[x] <= 0))
		return INF;

	if((val_prev_1 + arr[x] > 0) || (val_prev_1 + val_prev_2 + arr[x] > 0)){
		ll val = fun(x + 1, 0, sign_1);
		if(cur > val + arr[x]){
			cur = val + arr[x];
			nxt[x][sign_1][sign_2] = mp(0, sign_1);
		}
	}

	if((val_prev_1 - arr[x] > 0) && (val_prev_1 + val_prev_2 - arr[x] > 0)){
		ll val = fun(x + 1, 1, sign_1);
		if(cur > val - arr[x]){
			cur = val - arr[x];
			nxt[x][sign_1][sign_2] = mp(1, sign_1);
		}
	}

	return cur;
}

void solve(){
	scanf("%d", &n);
	arr[0] = arr[1] = INF;
	for(int i = 2; i <= n + 1; i++)
		scanf("%lld", arr + i);

	for(int i = 0; i <= n + 100; i++){
		dp[i][0][0] = dp[i][0][1] = INF;
		dp[i][1][0] = dp[i][1][1] = INF;
	}

	fun(2, 0, 0);

	pii pos = mp(0, 0);
	for(int i = 2; i <= n + 1; i++){
		int sign = nxt[i][pos.fi][pos.se].fi;
		printf("%lld ", arr[i] * (sign == 1 ? -1 : 1));
		pos = nxt[i][pos.fi][pos.se];
	}
	printf("\n");
}


int main(){
	int t;
	scanf("%d", &t);
	while(t--)
		solve();

	return 0;
}  