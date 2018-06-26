/*
Idea:
- https://codeforces.com/blog/entry/44657?#comment-293060
*/

#include "gap.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

set<ll> s;

ll findGap(int T, int N){
	if(T == 1){		
		ll l = 0, d = INF, x, y;
		while(s.size() < N){
			MinMax(l, d, &x, &y);
			if(x != -1)
				s.insert(x);

			if(y != -1)
				s.insert(y);

			l = x + 1;
			d = y - 1;
		}

		ll ans = -1;
		for(auto it = s.begin(); next(it) != s.end(); it++)
			ans = max(ans, *next(it) - *it);

		return ans;
	}

	if(T == 2){
		ll l = 0, d = INF, x, y, a, b;
		MinMax(l, d, &x, &y);

		if(N == 2)
			return y - x;

		ll dist = ((y - x) + (N - 2) - 1) / (N - 2);
		for(ll i = x; i <= y; i += dist){
			MinMax(i, i + dist - 1, &a, &b);
			if(a != -1)
				s.insert(a);

			if(b != -1)
				s.insert(b);
		}

		ll ans = -1;
		for(auto it = s.begin(); next(it) != s.end(); it++)
			ans = max(ans, *next(it) - *it);

		return ans;
	}
}