
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define maxn 5111

typedef long long ll;

vector<int> find_subset(int l, int u, vector<int> w){
	vector<int> ret;
	vector<pair<int, int> > tren;
	int n = w.size();
	ll cur = 0;
	int dd = 0;

	for(int i = 0; i < n; i++)
		tren.pb(mp(w[i], i));

	sort(tren.begin(), tren.end());

	for(int ll = 0; ll < n; ll++){
		while(dd < n && cur < l){
			cur += tren[dd].fi;
			dd++;
		}			

		if(l <= cur && cur <= u){
			for(int i = ll; i < dd; i++)
				ret.pb(tren[i].se);
			sort(ret.begin(), ret.end());
			return ret;
		}
		cur -= tren[ll].fi;
	}

	return ret;
}