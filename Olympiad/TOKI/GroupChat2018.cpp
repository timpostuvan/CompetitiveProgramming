/*
Idea:
- We transform Manhattan distance into Chebysehv distance (x, y) -> (x + y, x - y) and distance is now max(abs(x1 - x2), abs(y1 - y2))
- Answer can be found using binary search 
- For a fixed maximum distance we find out that a number of points on the left can form a group and the same goes for the right side (sorted accoring to first "new" coordinate)
- These two intervals can intersect and now we have 3 intervals (points that can be only in the left group, in both groups or only in the right group)
- The only thing left is to distribute the middle interval between other two
- It is optimal to give first k points (sorted accoring to second "new" coordinate) to one group and the rest to other (we try all possible ks and take best)
*/

#include "group.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 34)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

int n;
pll p[maxn], zac;

ll get_max(pll a, pll b, pll c, pll d){
	ll ret1 = max(max(a.se, c.se) - min(a.fi, c.fi), max(b.se, d.se) - min(b.fi, d.fi));
	ll ret2 = max(max(a.se, d.se) - min(a.fi, d.fi), max(b.se, c.se) - min(b.fi, c.fi));

	return min(ret1, ret2);
}

bool check(ll dist){
	pll meja1 = zac, meja2 = zac, meja3 = zac;
	int ind1 = 0;
	int ind2 = n - 1;

	while(ind1 < n && p[ind1].fi - p[0].fi <= dist)
		ind1++;
	ind1--;

	while(ind2 >= 0 && p[n - 1].fi - p[ind2].fi <= dist)
		ind2--;
	ind2++;


	if(ind1 + 1 < ind2)		// not all elements
		return 0;


	if(ind1 + 1 == ind2){
		for(int i = 0; i <= ind1; i++){
			meja1.fi = min(meja1.fi, p[i].se);
			meja1.se = max(meja1.se, p[i].se);
		}

		for(int i = ind2; i < n; i++){
			meja2.fi = min(meja2.fi, p[i].se);
			meja2.se = max(meja2.se, p[i].se);
		}

		ll cur_dist = max(meja1.se - meja1.fi, meja2.se - meja2.fi);

		return (cur_dist <= dist);
	}

	else{
		for(int i = 0; i < ind2; i++){
			meja1.fi = min(meja1.fi, p[i].se);
			meja1.se = max(meja1.se, p[i].se);
		}

		for(int i = ind1 + 1; i < n; i++){
			meja2.fi = min(meja2.fi, p[i].se);
			meja2.se = max(meja2.se, p[i].se);
		}

		vector<ll> v;
		for(int i = ind2; i <= ind1; i++)
			v.pb(p[i].se);

		sort(v.begin(), v.end());

		ll cur_dist = INF + 10;

		cur_dist = min(cur_dist, get_max(meja1, meja2, mp(v[0], v.back()), zac));
		for(int i = 0; i + 1 < v.size(); i++){
			pll c = mp(v[0], v[i]);
			pll d = mp(v[i + 1], v.back());
			cur_dist = min(cur_dist, get_max(meja1, meja2, c, d));
		}

		return (cur_dist <= dist);
	}
}


int getMinimumDelay(int N, vector<int> X, vector<int> Y){
	n = N;
	zac = mp(INF, -INF);
	for(int i = 0; i < n; i++)
		p[i] = mp(X[i] + Y[i], X[i] - Y[i]);

	sort(p, p + n);

	ll l = 0, d = INF, mid, ans = 0;
	while(l <= d){
		mid = (l + d) / 2;
		if(check(mid)){
			ans = mid;
			d = mid - 1;
		}
		else
			l = mid + 1;
	}
	return ans;
}