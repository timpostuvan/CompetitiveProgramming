#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include "grader.h"

using namespace std;

struct tree{
	int maks, mini;
};

int ans[2111111];
tree seg[11111111];
int n1;

void mix(int tren, int min1, int max1){
	seg[tren].maks = min(seg[tren].maks, max1);
	seg[tren].maks = max(seg[tren].maks, min1);
	seg[tren].mini = max(seg[tren].mini, min1);
	seg[tren].mini = min(seg[tren].mini, max1);	
}

void update(int tren, int ll, int dd, int l, int d, int val, int oper){
	if(ll > dd || d < ll || l > dd) return;
	if(l <= ll && dd <= d){
		if(oper == 1){
			seg[tren].mini = max(val, seg[tren].mini);
			seg[tren].maks = max(val, seg[tren].maks);
		}

		if(oper == 2){
			seg[tren].maks = min(val, seg[tren].maks);
			seg[tren].mini = min(val, seg[tren].mini);
		}
		return;
	}

	mix(2 * tren, seg[tren].mini, seg[tren].maks);
	mix(2 * tren + 1, seg[tren].mini, seg[tren].maks);

	update(2 * tren, ll, (ll + dd) / 2, l, d, val, oper);
	update(2 * tren + 1, 1 + (ll + dd) / 2, dd, l, d, val, oper);

	seg[tren].mini = min(seg[2 * tren].mini, seg[2 * tren + 1].mini);
	seg[tren].maks = max(seg[2 * tren].maks, seg[2 * tren + 1].maks);
}

void query(int tren, int l, int d){
	if(l > d || l < 0 || d > n1) return;
	mix(2 * tren, seg[tren].mini, seg[tren].maks);
	mix(2 * tren + 1, seg[tren].mini, seg[tren].maks);

	if(l == d) {ans[l] = seg[tren].mini; return;}

	query(2 * tren, l, (l + d) / 2);
	query(2 * tren + 1, 1 + (l + d) / 2, d);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	n1 = n;
	for(int i = 0; i < k; i++){
		update(1, 1, n1, left[i] + 1, right[i] + 1, height[i], op[i]);
	}
	query(1, 1, n1);
	for(int i = 0; i < n1; i++){
		finalHeight[i] = ans[i + 1];
	}
}