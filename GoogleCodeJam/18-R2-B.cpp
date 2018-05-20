#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 40

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int dp[maxn][511][511];
int ans[511][511];

int fun(int x, int r, int b){
	if(x == maxn || r < 0 || b < 0)
		return -INF;

	int &cur = dp[x][r][b];
	if(cur != -1)
		return cur;

	cur = 0;
	int cur_r = 0, cur_b = 0;
	for(int i = 0; i < maxn; i++){
		cur_b += x;
		cur_r += i;

		if(r - cur_r < 0)
			break;

		if(b - cur_b < 0)
			break;

		cur = max(cur, fun(x + 1, r - cur_r, b - cur_b) + (i + 1));
	}
	return cur;
}

void preprocess(){
	memset(dp, -1, sizeof(dp));
	for(int j = 0; j < 511; j++){
		for(int k = 0; k < 511; k++)
			fun(0, j, k);
	}

	for(int i = 0; i < 511; i++){
		for(int j = 0; j < 511; j++){
			for(int k = 0; k < maxn; k++)
				ans[i][j] = max(ans[i][j], dp[k][i][j]);
		}
	}
}


int solve(){
	int r, b;
	scanf("%d%d", &r, &b);
	return (ans[r][b] - 1);
}

int main(){
	preprocess();

	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; i++)
		printf("Case #%d: %d\n", i, solve());

	return 0;
}