#include "grader.h"
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

int r, c, h, w, q[3002][3002];
int pre[3002][3002];


bool check(int mid){
	int x, y;
	memset(pre, 0, sizeof(pre));
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			pre[i][j] = 0;
			if(i - 1 >= 0) pre[i][j] += pre[i - 1][j];
			if(j - 1 >= 0) pre[i][j] += pre[i][j - 1];
			if(j - 1 >= 0 && i - 1 >= 0) pre[i][j] -= pre[i - 1][j - 1];
			if(q[i][j] > mid) pre[i][j] -= 1;
			if(q[i][j] < mid) pre[i][j] += 1;
			if(q[i][j] == mid){
				x = i;
				y = j;
			}
		}
	}


	for(int i1 = 0; i1 < r; i1++){
		int i2 = i1 + h - 1;
		if(i2 >= r) break;

		for(int j1 = 0; j1 < c; j1++){
			int j2 = j1 + w - 1;
			if(j2 >= c) break;


			int tren = pre[i2][j2];
			if(i1 - 1 >= 0 && j1 - 1 >= 0) tren += pre[i1 - 1][j1 - 1];
			if(j1 - 1 >= 0) tren -= pre[i2][j1 - 1];
			if(i1 - 1 >= 0) tren -= pre[i1 - 1][j2];
			if(tren >= 0) return 1;
		}
	} 


	return 0;
}


int rectangle(int R, int C, int H, int W, int Q[3001][3001]){
	r = R; c = C; h = H; w = W; 
	for(int i = 0; i < R; i++) for(int j = 0; j < C; j++) q[i][j] = Q[i][j];

	int l, d, mid, ans;
	l = 1; d = r * c;

	while(l <= d){
		mid = (l + d) / 2;
		if(check(mid)){
			ans = mid;
			d = mid - 1;
		}
		else l = mid + 1;

	}

	return ans;
}