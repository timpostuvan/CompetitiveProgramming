/*
Idea:
- http://codeforces.com/blog/entry/57637?#comment-413356 (Problem 3)
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 30)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 3111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

char str[maxn][maxn];
int dp[maxn][maxn][3];
int n, m;

bool can(int x, int y, char c){
	if(x < 1 || x > n || y < 1 || y > m)
		return 0;

	return (str[x][y] == c);
}

int fun(int x, int y, int t){ 		// 0 - nothing, 1 - horizontal, 2 - vertical
	if(x < 1 || x > n || y < 1 || y > m)
		return 0;

	int &cur = dp[x][y][t];
	if(cur != -1)
		return cur;

	int add = 0;
	if(t == 1 && can(x, y - 1, 'R') && can(x, y, 'G') && can(x, y + 1, 'W'))
		add = 1;

	if(t == 2 && can(x - 1, y, 'R') && can(x, y, 'G') && can(x + 1, y, 'W'))
		add = 1;

	if(t != 0 && add == 0)
		return 0;
	
	cur = 0;
	for(int i = 0; i < 3; i++){
		if(t + i == 3)
			continue;

		cur = max(cur, fun(x - 1, y + 1, i) + add);
	} 
	return cur;
}

int main(){
	scanf("%d%d", &n, &m);
	memset(dp, -1, sizeof(dp));

	for(int i = 1; i <= n; i++)
		scanf("%s", str[i] + 1);

	int ans = 0;
	for(int i = 1; i <= n; i++)
		ans += max(fun(i, 1, 0), max(fun(i, 1, 1), fun(i, 1, 2)));

	for(int i = 2; i <= m; i++)
		ans += max(fun(n, i, 0), max(fun(n, i, 1), fun(n, i, 2)));

	printf("%d\n", ans);
	return 0;
}