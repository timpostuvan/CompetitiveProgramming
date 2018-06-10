#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define maxn 1000110 

vector<pair<long long, long long> > env;  // lines present in envelope (first represents k and second represents n (y = kx + n))
long long dp[maxn];
long long sum[maxn];
long long arr[maxn];

bool bad(long long l1, long long l2, long long l3){
	return (  ((env[l3].second - env[l1].second) * (env[l1].first - env[l2].first))
	<= ((env[l2].second - env[l1].second) * (env[l1].first - env[l3].first))  );
}


void add(long long x, long long y){
	env.push_back({x, y});
	while(env.size() >= 3 && bad(env.size() - 3, env.size() - 2, env.size() - 1)){
		env.erase(env.end() - 2);
	}
}

long long query(long long x){
	long long l = 0, d = env.size() - 1, ans = env.size() - 1, mid;
	while(l <= d){
		mid = (l + d) / 2;
		if(env[mid].first * x + env[mid].second >= env[mid + 1].first * x + env[mid + 1].second){
			ans = mid;
			d = mid - 1;
		}
		else l = mid + 1;
	}
	return env[ans].first * x + env[ans].second;
}

int main(){
	long long a, b, c, n;
	scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
	for(long long i = 1; i <= n; i++){
		scanf("%lld", &arr[i]);
		sum[i] = sum[i - 1] + arr[i];
	}
	dp[1] = a * sum[1] * sum[1] + b * sum[1] + c;
	add(-2 * a * sum[1], dp[1] + a * sum[1] * sum[1] - b * sum[1]);
	for(long long i = 2; i <= n; i++){
		dp[i] = a * sum[i] * sum[i] + b * sum[i] + c;
		dp[i] = max(dp[i], a * sum[i] * sum[i] + b * sum[i] + c + query(sum[i]));
		add(-2 * a * sum[i], dp[i] + a * sum[i] * sum[i] - b * sum[i]);
	}
	printf("%lld\n", dp[n]);
	return 0;
}