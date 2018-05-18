/*
Idea:
- The order of cuts doesn't matter (only positions are important)
- dp[i][j] - best answer if we did j cuts and last cut was made after position i
- dp[i][j] = max (k < i)(dp[k][j - 1] + sum(k + 1, i) * (i + 1, n))
		   = max (k < i)(dp[k][j - 1] + (sum(1, i) - sum(1, k)) * (sum(1, n) - sum(1, i)))

- If we take the right parts of formula above together, convex hull trick can be applied
- Because memory limit is tight, we can store only last 2 layers of dp  
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
#define maxk 211

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;


ll k[maxn], n[maxn];
int ind[maxn];
int best_ind, top, bot;

ll dp[maxn][2], pre[maxn], arr[maxn];
int from[maxn][maxk];

bool bad(int l1, int l2, int l3){
	return (n[l3] - n[l1]) * (k[l1] - k[l2]) <= (n[l2] - n[l1]) * (k[l1] - k[l3]);
}

void add(ll cur_k, ll cur_n, int cur_ind){
	if(top - bot > 0 && k[top - 1] == cur_k){
		if(cur_n > n[top - 1])
			top--;
		else
			return;
	}

	k[top] = cur_k;
	n[top] = cur_n;
	ind[top] = cur_ind;

	while(top - bot >= 3 && bad(top - 2, top - 1, top)){
		k[top - 1] = k[top];
		n[top - 1] = n[top];
		ind[top - 1] = ind[top];
		top--;
	}
	top++;
}

inline ll val(int ind, ll x){
	return k[ind] * x + n[ind];
}

pair<ll, int> query(ll x){
	if(best_ind >= top)
		best_ind = top - 1;

	while(best_ind + 1 < top && val(best_ind, x) <= val(best_ind + 1, x))
		best_ind++;

	return mp(val(best_ind, x), ind[best_ind]);
}

ll sum(int i, int j){
	if(i > j)
		return 0LL;

	return pre[j] - pre[i - 1];
}

int main(){
	int N, K;
	scanf("%d%d", &N, &K);
	for(int i = 1; i <= N; i++){
		scanf("%lld", arr + i);
		pre[i] = pre[i - 1] + arr[i];
	}

	for(int i = 0; i <= N; i++){
		for(int j = 0; j < 2; j++)
			dp[i][j] = -INF;
	}

	for(int i = 1; i <= N - 1; i++)
		dp[i][1] = sum(1, i) * sum(i + 1, N);

	for(int j = 2; j <= K; j++){
		top = bot = 0;
		best_ind = 0;

		int jj = j % 2;
		int prev = 1 - jj;

		for(int i = j; i <= N - 1; i++){
			add(sum(1, i - 1), dp[i - 1][prev] - sum(1, i - 1) * sum(1, N), i - 1);
			
			pair<ll, int> cur = query(sum(1, i));
			dp[i][jj] = cur.fi + sum(i + 1, N) * sum(1, i);
			from[i][j] = cur.se;
		}
	}

	int ans = 0;
	for(int i = 1; i <= N - 1; i++){
		if(dp[i][K % 2] > dp[ans][K % 2])
			ans = i;
	}

	printf("%lld\n", dp[ans][K % 2]);
	for(int i = K; i >= 1; i--){
		printf("%d ", ans);
		ans = from[ans][i];
	}

	return 0;
}