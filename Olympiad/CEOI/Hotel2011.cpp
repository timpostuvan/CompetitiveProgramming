#include <bits/stdc++.h>

using namespace std;

#define maxn 500111

multiset<pair<long long, long long> > s;
pair<long long, long long> pon[maxn], sob[maxn];
vector<long long> v;

int main(){
	long long n, m, o, ans = 0LL;
	scanf("%lld%lld%lld", &n, &m, &o);
	for(long long i = 0; i < n; i++){
		scanf("%lld%lld", &sob[i].second, &sob[i].first);
		s.insert(sob[i]);
	}

	for(long long i = 0; i < m; i++)
		scanf("%lld%lld", &pon[i].first, &pon[i].second);

	sort(pon, pon + m);
	reverse(pon, pon + m);

	for(long long i = 0; i < m; i++){
		set<pair<long long, long long> >::iterator it = s.lower_bound(make_pair(pon[i].second, -1));
		if(it == s.end()) continue;
		v.push_back(pon[i].first - it -> second);
		s.erase(it);
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());

	for(long long i = 0; i < min((long long) v.size(), o); i++){
		if(v[i] >= 0)
			ans += v[i];
	}
	printf("%lld\n", ans);
	return 0;	
}