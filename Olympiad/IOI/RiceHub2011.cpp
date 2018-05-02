#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iostream>

using namespace std;

#define maxn 100111

long long arr[maxn], dp[maxn];
long long r, l, b;

long long val(long long ll, long long dd){
	long long med = (ll + dd) / 2;
	long long manj = (arr[med] * (med - ll + 1)) - (dp[med] - dp[ll - 1]);
	long long vec = (dp[dd] - dp[med - 1]) - (arr[med] * (dd - med + 1));
	return (manj + vec);
}

bool check(long long x){
	long long ans = (1LL << 59);
	for(long long i = 1; i <= r - x + 1; i++) ans = min(ans, val(i, i + x - 1));
	if(ans <= b) return 1;
	else return 0;
}

long long solve(){
	long long ll, dd, mid, ans = -1; 
	ll = 0; dd = r;

	while(ll <= dd){
		mid = (ll + dd) / 2;
		if(check(mid)){
			ll = mid + 1;
			ans = mid;  
		}
		else dd = mid - 1;
	}

	return ans;
}


int main(){
	scanf("%lld%lld%lld", &r, &l, &b);
	for(long long i = 1; i <= r; i++){
		scanf("%lld", arr + i);
		dp[i] = arr[i] + dp[i - 1];
	}
	printf("%lld", solve());
	return 0;
}