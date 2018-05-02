#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 9)
#define maxn 100111

typedef long long ll;
typedef long double ld;

vector<pair<int, int> > v;
int zac[maxn];

int valid(int n, int inputSeq[]){
	for(int i = 0; i < n; i++)
		v.pb(mp(inputSeq[i], i));

	sort(v.begin(), v.end());

	int val = v[0].se;
	for(int i = 0; i < n; i++)
		v[i].se = (v[i].se - val + n) % n;

	for(int i = 1; i < n; i++){
		if(v[i].fi == v[i - 1].fi)
			return 0;

		int raz = v[i].fi - v[i - 1].fi;
		if(v[i].fi <= n && (v[i - 1].se + raz != v[i].se))
			return 0;
	}
	return 1;
}

//----------------------

int replacement(int n, int gondolaSeq[], int replacementSeq[]){
	//return -1;
	int cnt = 0;
	int cur = n + 1;
	for(int i = 0; i < n; i++)
		v.pb(mp(gondolaSeq[i], i));

	sort(v.begin(), v.end());

	int val = v[0].se;
	for(int i = 0; i < n; i++){
		v[i].se = (v[i].se - val + n) % n;
		zac[i] = (v[0].fi - 1 + i) % n + 1;
	}

	for(int i = 0; i < n; i++){
		int ind = v[i].se;
		while(zac[ind] < v[i].fi){
			replacementSeq[cnt] = zac[ind];
			zac[ind] = cur;
			cur++;
			cnt++;
		}
	}
	return cnt;
}

//----------------------

ll fastpow(ll x, ll y){
	ll cur = 1;
	while(y > 0){
		if(y & 1)
			cur = (cur * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return cur % MOD;
}

int countReplacement(int n, int inputSeq[]){
	int cur = n + 1;
	ll ans = 1;
	if(!valid(n, inputSeq))
		return 0;

	v.clear();
	for(int i = 0; i < n; i++)
		v.pb(mp(inputSeq[i], i));

	sort(v.begin(), v.end());

	int val = v[0].se;
	for(int i = 0; i < n; i++)
		v[i].se = (v[i].se - val + n) % n;

	bool more = (v[0].fi > n);

	for(int i = 0; i < n; i++){
		if(v[i].fi <= n)
			continue;

		ll raz = v[i].fi - cur;
		cur = v[i].fi + 1;
		ans = (ans * fastpow(1LL * (n - i), 1LL * raz)) % MOD;
	}

	if(more)
		ans = (ans * n) % MOD;

	return ans;	
}