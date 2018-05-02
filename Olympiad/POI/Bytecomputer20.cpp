#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111
#define zero 1

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int n;
int arr[maxn];
int dp[maxn][4];

int fun(int x, int s){
	if(x == n - 1)
		return 0;

	int &cur = dp[x][s];
	if(cur != -1)
		return cur;

	cur = INF;
	int state = s - zero;

	if(state == 1){
		cur = min(cur, fun(x + 1, 1 + zero) + abs(1 - arr[x + 1]));
	}

	if(state == 0){
		if(arr[x + 1] < 0)
			cur = INF;
		else
			cur = min(cur, fun(x + 1, arr[x + 1] + zero));
	}

	if(state == -1){
		for(int nxt = -1; nxt <= arr[x + 1]; nxt++){
			cur = min(cur, fun(x + 1, nxt + zero) + abs(nxt - arr[x + 1]));
		}
	}
	return cur;
}


int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", arr + i);

	memset(dp, -1, sizeof(dp));

	int ans = fun(0, arr[0] + zero);

	if(ans == INF)
		printf("BRAK\n");
	else
		printf("%d\n", ans);
	return 0;
}