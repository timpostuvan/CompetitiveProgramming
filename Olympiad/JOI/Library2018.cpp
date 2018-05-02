#include "library.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> here;

int find_first(int n){
	vector<int> q(n, 1);

	for(int i = 0; i < n; i++){
		q[i] = 0;
		int num = Query(q);
		if(num == 1){
			here.erase(find(here.begin(), here.end(), i));
			return i;
		}
		q[i] = 1;
	}
}

bool ask(int n, int l, int d, int last){
	vector<int> q(n, 0);
	for(int i = l; i <= d; i++)
		q[here[i]] = 1;

	int alone = Query(q);

	q[last] = 1; 
	int together = Query(q);

	if(alone == together)		// next is in range [l, d]
		return 1;
	
	return 0;
}

int find_next(int n, int last){
	int l = 0, d = here.size() - 1, ans = -1, mid;
	while(l <= d){
		if(l == d){
			ans = l;
			break;
		}

		mid = (l + d) / 2;
		if(ask(n, l, mid, last))
			d = mid;
		else
			l = mid + 1;
	}

	int ret = here[ans];
	here.erase(find(here.begin(), here.end(), ret));
	return ret;
}

void Solve(int n){
	vector<int> ans;

	if(n == 1){
		ans.pb(1);
		Answer(ans);
		return;
	}

	for(int i = 0; i < n; i++)
		here.pb(i);

	int last = find_first(n);
	ans.pb(last);

	while(here.size() > 1){
		int nxt = find_next(n, last);
		ans.pb(nxt);
		last = nxt;
	}

	ans.pb(here[0]);
	
	for(int i = 0; i < n; i++)
		ans[i]++;

	Answer(ans);
}