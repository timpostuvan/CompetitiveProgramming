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


// 2D SEGMENT TREE - 63 POINTS (DOESN'T CONTAIN PRUNING)


long long gcd2(long long X, long long Y) {
    long long tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

int r, c;

struct nodey{
	nodey() : l(NULL), r(NULL), val(0LL) {}
	nodey *l, *r;
	ll val;
};

struct nodex{
	nodex() : l(NULL), r(NULL), ny(NULL) {}
	nodex *l, *r;
	nodey *ny;
} *root;

void updatey(nodey * x, int s, int e, int vy, ll val){
	if(s == e){
		x -> val = val;
		return;
	}

	int mid = (s + e) / 2;
	if(vy <= mid){
		if(!x -> l)
			x -> l = new nodey();
		updatey(x -> l, s, mid, vy, val);
		ll cur = x -> l -> val;
		if(x -> r)
			cur = gcd2(cur, x -> r -> val);
		x -> val = cur;
	}

	if(vy > mid){
		if(!x -> r)
			x -> r = new nodey();
		updatey(x -> r, mid + 1, e, vy, val);
		ll cur = x -> r -> val;
		if(x -> l)
			cur = gcd2(cur, x -> l -> val);
		x -> val = cur;
	}
}

ll queryy(nodey *x, int s, int e, int ly, int dy){
	if(dy < s || e < ly)
		return 0;
	if(ly <= s && e <= dy)
		return x -> val;

	int mid = (s + e) / 2;
	ll ret = 0;
	if(x -> l)
		ret = gcd2(ret, queryy(x -> l, s, mid, ly, dy));
	if(x -> r)
		ret = gcd2(ret, queryy(x -> r, mid + 1, e, ly, dy));
	return ret;
}

void updatex(nodex *x, int s, int e, int vx, int vy, ll val){
	if(s == e){
		if(!x -> ny)
			x -> ny = new nodey();
		updatey(x -> ny, 1, c, vy, val);
		return;
	}

	int mid = (s + e) / 2;
	if(vx <= mid){
		if(!x -> l)
			x -> l = new nodex();
		updatex(x -> l, s, mid, vx, vy, val);
		ll cur = queryy(x -> l -> ny, 1, c, vy, vy);
		if(x -> r)
			cur = gcd2(cur, queryy(x -> r -> ny, 1, c, vy, vy));
		if(!x -> ny)
			x -> ny = new nodey();
		updatey(x -> ny, 1, c, vy, cur);
	}

	if(vx > mid){
		if(!x -> r)
			x -> r = new nodex();
		updatex(x -> r, mid + 1, e, vx, vy, val);
		ll cur = queryy(x -> r -> ny, 1, c, vy, vy);
		if(x -> l)
			cur = gcd2(cur, queryy(x -> l -> ny, 1, c, vy, vy));
		if(!x -> ny)
			x -> ny = new nodey();
		updatey(x -> ny, 1, c, vy, cur);
	}
}

ll queryx(nodex *x, int s, int e, int lx, int dx, int ly, int dy){
	if(lx > e || dx < s)
		return 0;
	if(lx <= s && e <= dx){
		if(!x -> ny)
			return 0;
		return queryy(x -> ny, 1, c, ly, dy);
	}

	int mid = (s + e) / 2;
	long long ret = 0;
	if(x -> l)
		ret = gcd2(ret, queryx(x -> l, s, mid, lx, dx, ly, dy));
	if(x -> r)
		ret = gcd2(ret, queryx(x -> r, mid + 1, e, lx, dx, ly, dy));
	return ret;
}

void init(int R, int C){
	root = new nodex();
    r = R;
    c = C;
}

void update(int P, int Q, long long K){
    updatex(root, 1, r, P + 1, Q + 1, K);
}

long long calculate(int P, int Q, int U, int V){
    return queryx(root, 1, r, P + 1, U + 1, Q + 1, V + 1);
}