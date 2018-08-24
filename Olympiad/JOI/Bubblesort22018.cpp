/*
Idea:
- http://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2018/2018-open-bubblesort2-sol-en.pdf
*/

#include "bubblesort2.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (int) (2 * 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

struct segtree{
	int seg[4 * maxn], lazy[4 * maxn];

	void push(int x, int l, int d){
		seg[x] += lazy[x];
		if(l != d){
			lazy[2 * x] += lazy[x];
			lazy[2 * x + 1] += lazy[x];	
		}
		lazy[x] = 0;
	}

	void update(int x, int l, int d, int i, int j, int val){
		push(x, l, d);
		if(l > d || l > j || d < i)
			return;

		if(i <= l && d <= j){
			lazy[x] += val;
			push(x, l, d);
			return;
		}

		int mid = (l + d) / 2;
		update(2 * x, l, mid, i, j, val);
		update(2 * x + 1, mid + 1, d, i, j, val);
		seg[x] = max(seg[2 * x], seg[2 * x + 1]);
	}

	int get(int x, int l, int d){
		push(x, l, d);
		return seg[x];
	}

} seg;

int arr[maxn];
int n;

void remove(int x, int pos){
	seg.update(1, 1, n, x, x, -(INF + pos));
	seg.update(1, 1, n, x + 1, n, 1);
}

void add(int x, int pos){
	seg.update(1, 1, n, x, x, INF + pos);
	seg.update(1, 1, n, x + 1, n, -1);
}

vector<int> countScans(vector<int> A, vector<int> X, vector<int> V){
	vector<int> ans;
	int q = X.size();

	vector<pii> v;
	for(int i = 0; i < A.size(); i++)
		v.pb(mp(A[i], i));

	for(int i = 0; i < q; i++)
		v.pb(mp(V[i], X[i]));

	sort(v.begin(), v.end());
	v.resize(distance(v.begin(), unique(v.begin(), v.end())));

	n = v.size();
	seg.update(1, 1, n, 1, n, -INF);

	for(int i = 0; i < A.size(); i++){
		A[i] = lower_bound(v.begin(), v.end(), mp(A[i], i)) - v.begin() + 1;
		add(A[i], i);
		arr[i] = A[i];
	}

	for(int i = 0; i < q; i++){
		V[i] = lower_bound(v.begin(), v.end(), mp(V[i], X[i])) - v.begin() + 1;
		int pos = X[i];
		remove(arr[pos], pos);
		add(V[i], pos);
		arr[pos] = V[i];
		ans.pb(seg.get(1, 1, n));
	}

	return ans;
}