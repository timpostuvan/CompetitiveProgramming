#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 30)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

bool check(int x, int a, int b){
	if(x == 0)
		return 0;

	if( (a + x - 1) / x <= b / x)
		return 1;

	return 0;
}

void solve(){
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	int m = sqrt(max(b, d)) + 10;

	int ans = 1;

	for(int i = 2; i <= m; i++){
		if(check(i, a, b) && check(i, c, d))
			ans = max(ans, i);
	}
	

	for(int i = 1; i <= m; i++){
		int cur = b / i;
		if(check(cur, a, b) && check(cur, c, d))
			ans = max(ans, cur);

		cur = d / i;
		if(check(cur, a, b) && check(cur, c, d))
			ans = max(ans, cur);
	}
	printf("%d\n", ans);
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--)
		solve();

	return 0;
}