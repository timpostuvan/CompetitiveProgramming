#include <bits/stdc++.h>

using namespace std;

#define maxn 100111

long long arr[maxn], a[maxn];
long long n, d, m;

bool check(long long mid){
	memcpy(a, arr, sizeof(arr));
	long long cur = 0;
	for(long long i = 0; i < n; i++){
		long long left = mid;
		while(cur <= i && left){
			long long st = min(a[cur], left);
			left -= st;
			a[cur] -= st;
			if(a[cur] == 0) cur++;
		}
		//cout << mid << "  " << i <<  "  " << cur << endl;
		if(cur + d - 1 < i) return 0;
	}
	if(cur == n) return 1;
}

int main(){
	scanf("%lld%lld%lld", &n, &d, &m);
	for(long long i = 0; i < m; i++){
		long long a;
		scanf("%lld", &a);
		arr[a - 1]++;
	}

	long long l = 0, d = m, mid, ans = -1; 
	while(l <= d){
		mid = (l + d) / 2;
		if(check(mid)){
			ans = mid;
			d = mid - 1;
		}
		else l = mid + 1;
	}
	printf("%lld\n", ans);
	return 0;
}