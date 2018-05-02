#include "horses.h"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <cmath>

using namespace std;

#define maxn 511111

const long long MOD = 1e9 + 7;

struct node{
	long double logmaxi;
	long double loglazy;
	long long maxi;
	long long lazy;
	bool b;
};

long double logx[maxn], logy[maxn];
long long x1[maxn], y[maxn], n;
node seg[4 * maxn];

long long fpow(long long base, long long x){
	long long res = 1LL;
	while(x){
		if(x % 2) res = (res * base) % MOD;
		base = (base * base) % MOD;
		x /= 2LL;
	}
	return (res % MOD);
}

void relax(long long x, long long l, long long d){
	if(seg[x].b == 0) return;
	if(l != d){
		seg[2 * x + 1].b = 1;
		seg[2 * x].b = 1;
		seg[2 * x + 1].loglazy += seg[x].loglazy;
		seg[2 * x].loglazy += seg[x].loglazy;
		seg[2 * x + 1].lazy = (seg[2 * x + 1].lazy * seg[x].lazy) % MOD;
		seg[2 * x].lazy = (seg[2 * x].lazy * seg[x].lazy) % MOD;
	}

	seg[x].maxi = (seg[x].maxi * seg[x].lazy) % MOD; 
	seg[x].logmaxi += seg[x].loglazy;

	seg[x].loglazy = 0LL;
	seg[x].lazy = 1LL; 
	seg[x].b = 0;
}

void build(long long x, long long l, long long d){
	if(l > d) return;
	if(l == d){
		seg[x].logmaxi = logx[l] + logy[l];
		seg[x].maxi = (1LL * x1[l] * y[l]) % MOD;
		seg[x].lazy = 1LL;
		seg[x].loglazy = 0LL;
		seg[x].b = 0;
		return;
	}

	long long mid = (l + d) / 2;
	build(2 * x, l, mid);
	build(2 * x + 1, mid + 1, d);

	long long nas = 2 * x + 1;
	if(seg[2 * x].logmaxi > seg[2 * x + 1].logmaxi) nas = 2 * x;

	seg[x].logmaxi = seg[nas].logmaxi;
	seg[x].maxi = seg[nas].maxi;
	seg[x].b = 0;
	seg[x].loglazy = 0;
	seg[x].lazy = 1LL;
}

void updatey(long long x, long long l, long long d, long long ll, long long dd, long long val, long double logval){
	relax(x, l, d);
	if(l > d || d < ll || l > dd) return;
	if(ll <= l && d <= dd && l == d){
		seg[x].logmaxi += logval;
		seg[x].maxi = (seg[x].maxi * val) % MOD;
		return;
	}

	long long mid = (l + d) / 2LL;
	updatey(2 * x, l, mid, ll, dd, val, logval);
	updatey(2 * x + 1, mid + 1, d, ll, dd, val, logval);

	long long nas = 2 * x + 1;
	if(seg[2 * x].logmaxi > seg[2 * x + 1].logmaxi) nas = 2 * x;
	
	seg[x].logmaxi = seg[nas].logmaxi;
	seg[x].maxi = seg[nas].maxi;
}

void updatex(long long x, long long l, long long d, long long ll, long long dd, long long val, long double logval){
	relax(x, l, d);
	if(l > d || d < ll || l > dd) return;
	if(ll <= l && d <= dd){
		seg[x].logmaxi += logval;
		seg[x].maxi = (seg[x].maxi * val) % MOD;

		seg[2 * x].b = 1;
		seg[2 * x + 1].b = 1;
		seg[2 * x].loglazy += logval;
		seg[2 * x].lazy = (seg[2 * x].lazy * val) % MOD;
		seg[2 * x + 1].loglazy += logval;
		seg[2 * x + 1].lazy = (seg[2 * x + 1].lazy * val) % MOD;
		return;
	}

	long long mid = (l + d) / 2LL;
	updatex(2 * x, l, mid, ll, dd, val, logval);
	updatex(2 * x + 1, mid + 1, d, ll, dd, val, logval);

	long long nas = 2 * x + 1;
	if(seg[2 * x].logmaxi > seg[2 * x + 1].logmaxi) nas = 2 * x;
	
	seg[x].logmaxi = seg[nas].logmaxi;
	seg[x].maxi = seg[nas].maxi;
}


int init(int N, int X[], int Y[]) {
	n = N;
	x1[0] = 1;
	for(long long i = 1; i <= n; i++){
		logx[i] = log10(X[i - 1]);
		logx[i] = logx[i] + logx[i - 1];
		x1[i] = X[i - 1] * 1LL;
		x1[i] = (x1[i] * x1[i - 1]) % MOD;
		logy[i] = log10(Y[i - 1]);
		y[i] = Y[i - 1] * 1LL;
	}

	build(1, 1, n);
	
	for(long long i = 1; i <= n; i++) {
		x1[i] = X[i - 1] * 1LL;
		logx[i] = log10(X[i - 1]);
	}
	return (int) seg[1].maxi;
}

int updateX(int pos, int val) {	
	pos++;
	long double logval = log10(val) - logx[pos];
	long long val1 = (1LL * val * fpow(x1[pos], MOD - 2)) % MOD;
	updatex(1, 1, n, pos, n, val1, logval);

	logx[pos] = log10(val);
	x1[pos] = val;	
	return (int) seg[1].maxi;
}

int updateY(int pos, int val) {
	pos++;
	long double logval = log10(val) - logy[pos];
	long long val1 = (1LL * val * fpow(y[pos], MOD - 2)) % MOD;
	updatey(1, 1, n, pos, pos, val1, logval);

	logy[pos] = log10(val);
	y[pos] = val;
	return (int) seg[1].maxi;
}