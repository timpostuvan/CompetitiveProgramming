#include "railroad.h"
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF (1e9)

typedef long long ll;

int root[211111];

int rooting(int x){
	if(root[x] == x)
		return x;
	return (root[x] = rooting(root[x]));
}

bool mergeDSU(int a, int b){
	int ra = rooting(a);
	int rb = rooting(b);
	root[ra] = rb;
	return (ra != rb);
}

ll plan_roller_coaster(vector<int> s, vector<int> t) {
	int n = s.size();
	vector<pair<int, pair<int, int> > > e, edge;

	for(int i = 0; i < n; i++){		// kind of sweep line algorithm
		e.pb(mp(s[i], mp(1, i)));
		e.pb(mp(t[i], mp(-1, i)));
	}

	e.pb(mp(INF, mp(1, n)));
	e.pb(mp(1, mp(-1, n)));
	n++;

	sort(e.begin(), e.end());

	for(int i = 0; i < n; i++)
		root[i] = i;

	ll balance = 0;
	ll ans = 0;
	for(int i = 0; i + 1 < e.size(); i++){
		balance += e[i].se.fi;
		ans += max(0LL, balance) * (ll) (e[i + 1].fi - e[i].fi);
		edge.pb(mp(e[i + 1].fi - e[i].fi, mp(e[i].se.se, e[i + 1].se.se)));
		if(e[i].fi == e[i + 1].fi || balance != 0)
			mergeDSU(e[i].se.se, e[i + 1].se.se);
	}

	sort(edge.begin(), edge.end());

	for(int i = 0; i < edge.size(); i++){
		if(mergeDSU(edge[i].se.fi, edge[i].se.se))
			ans += edge[i].fi;
	}
	return ans;   
}


/*

//BEGIN CUT

int main() {
	int n, need_answer;
	scanf("%d", &n);
	std::vector<int> s(n), t(n);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &s[i], &t[i]);
	long long ans = plan_roller_coaster(s, t);
	
	// BEGIN SECRET
	puts("14e047d7a2907b9034950b074822b302");
	// END SECRET
	
	printf("%lld\n", ans);
	
	return 0;
}

//END CUT
*/