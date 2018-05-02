#include "messy.h"
#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF (1e9)
#define maxn 130

typedef long long ll;

int n, ans[maxn];


void solve(int l, int d){
	if(l == d)
		return;

	int mid = (l + d) / 2;
	string str;
	for(int i = 0; i < n; i++)
		str.pb('0');

	for(int i = l; i <= d; i++)
		str[i] = '1';

	for(int i = mid + 1; i <= d; i++){
		str[i] = '0';
		add_element(str);
		str[i] = '1';
	}

	solve(l, mid);
	solve(mid + 1, d);
}

void solve2(int l, int d, vector<int> pos){
	if(l == d){
		ans[pos[0]] = l;
		return;
	}

	int mid = (l + d) / 2;
	string str;
	for(int i = 0; i < n; i++)
		str.pb('0');

	for(int i : pos)
		str[i] = '1';

	vector<int> lpos, dpos;

	for(int i : pos){
		str[i] = '0';
		if(check_element(str))
			dpos.pb(i);
		else
			lpos.pb(i);
		str[i] = '1';
	}
	solve2(l, mid, lpos);
	solve2(mid + 1, d, dpos);	
}

vector<int> restore_permutation(int _n, int w, int r) {
	n = _n;
	solve(0, n - 1);
	compile_set();
	vector<int> v;
	for(int i = 0; i < n; i++)
		v.pb(i);
	
	solve2(0, n - 1, v);

	vector<int> ret;
	for(int i = 0; i < n; i++)
		ret.pb(ans[i]);
	return ret;
}