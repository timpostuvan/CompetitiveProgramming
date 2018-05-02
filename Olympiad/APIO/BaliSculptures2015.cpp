#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 2111

typedef long long ll;
typedef long double ld;

int n, a, b;
ll pre[maxn], arr[maxn];
ll dp2[maxn][maxn], dp3[maxn];

ll meja;

bool fun2(int x, int st){
	if(x == n && a <= st && st <= b)
		return 1;
	if(x == n)
		return 0;

	ll &cur = dp2[x][st];
	if(cur != -1)
		return cur;

	cur = 0;
	for(int i = x; i < n; i++){
		if( ((~meja) & (pre[i] - pre[x - 1])) == 0){
			cur |= fun2(i + 1, st + 1);
		}
	}
	return cur;
}

void solve2(){
	meja = (1LL << 50) - 1;
	for(int i = 49; i >= 0; i--){
		memset(dp2, -1, sizeof(dp2));
		meja ^= (1LL << i);
		if(!fun2(0, 0)){
			meja ^= (1LL << i);
		} 
	}
	printf("%lld\n", meja);
}

ll fun3(int x){
	if(x == n)
		return 0;

	ll &cur = dp3[x];
	if(cur != -1)
		return cur;

	cur = INF;
	for(int i = x; i < n; i++){
		if( ((~meja) & (pre[i] - pre[x - 1])) == 0){
			cur = min(cur, 1LL + fun3(i + 1));
		}
	}
	return cur;
}

void solve3(){
	meja = (1LL << 50) - 1;
	for(int i = 49; i >= 0; i--){
		memset(dp3, -1, sizeof(dp3));
		meja ^= (1LL << i);
		if(fun3(0) > b){
			meja ^= (1LL << i);
		} 
	}
	printf("%lld\n", meja);
}

int main(){
	scanf("%d%d%d", &n, &a, &b);
	for(int i = 0; i < n; i++){
		scanf("%lld", arr + i);
		if(i)
			pre[i] = pre[i - 1];
		pre[i] += arr[i];
	}

	if(a != 1)
		solve2();
	else
		solve3();
	return 0;
}