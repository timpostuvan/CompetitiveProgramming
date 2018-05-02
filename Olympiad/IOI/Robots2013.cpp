#include "grader.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <cstdio>
#include <utility>
#include <iostream>

using namespace std;

pair<int, int> p[1111111];
int x[1111111], y[1111111];
int a, b, t;

bool check(int mid){
	priority_queue<int> pq;
	int ind = 0;

	for(int i = 0; i < a; i++){
		while(p[ind].first < x[i] && ind < t){
			pq.push(p[ind].second);
			ind++;
		}

		
		for(int j = 0; j < mid && !pq.empty(); j++) pq.pop();
	}

	while(ind < t){
		pq.push(p[ind].second);
		ind++;
	}

	for(int i = 0; i < b; i++){
		for(int j = 0; j < mid && !pq.empty(); j++){
			if(pq.top() < y[i]) pq.pop();
			else return false;
		}
	}

	if(pq.empty()) return true;
	return false;
}

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
	a = A, b = B, t = T;

	for(int i = 0; i < T; i++){
		p[i].first = W[i];
		p[i].second = S[i];
	}

	for(int i = 0; i < A; i++) x[i] = X[i];
	for(int i = 0; i < B; i++) y[i] = Y[i];

	sort(p, p + t);
	sort(x, x + a);
	sort(y, y + b);
	reverse(y, y + b);

	int l, d, mid, ans;
	l = 1; d = 1111111; ans = -1;


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