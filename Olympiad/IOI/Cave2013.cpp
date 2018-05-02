#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF (1LL << 55)
#define maxn 5011

typedef long long ll;

int n;
int q[maxn];
bool used[maxn];
int pos[maxn];
int pull[maxn];

int cpos, cpull;
int x;

bool make(int l, int d, int mid){
	memset(q, 1 - cpull, sizeof(q));

	for(int i = 0; i < n; i++){
		if(used[i])
			q[i] = pull[i]; 
	}

	for(int i = l; i <= mid; i++){
		if(!used[i]){
			q[i] = cpull;
		}
	}

	int a = tryCombination(q);
	//cout << l <<  "  " << d <<  "  " << mid <<  ":  "<< a << endl; 

	if(a == x)
		return 0;
	else
		return 1;
}


void find(){
	memset(q, 0, sizeof(q));
	for(int i = 0; i < n; i++){
		if(used[i])
			q[i] = pull[i]; 
	} 

	int a = tryCombination(q);
//	cout << x << " " <<  a << endl;
	if(a == x)
		cpull = 1;
	else
		cpull = 0;

	int l = 0, d = n - 1, mid;

	while(l <= d){
		mid = (l + d) / 2;
		if(l == d){
			cpos = l;
			break;
		}

		if(make(l, d, mid))
			d = mid;
		else
			l = mid + 1;

	}
}


void exploreCave(int N){
	n = N;
	for(int i = 0; i < n; i++){
		x = i;
		find();
	//	cout << "ans " << i << ":  " << cpull << "  " << cpos << endl;
		pull[cpos] = cpull;
		pos[cpos] = i;
		used[cpos] = 1;
	}
	answer(pull, pos);
}