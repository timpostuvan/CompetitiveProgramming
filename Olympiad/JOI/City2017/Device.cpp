/*
Idea:
- https://codeforces.com/blog/entry/51010 (city)
*/

#include "Device.h"
#include <bits/stdc++.h>

using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxm 1000111
#define maxn 250111
#define maxk 252
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int a1[maxk];

void InitDevice(){
	a1[1] = 1;
	for(int i = 2; i < maxk; i++){
		a1[i] = (double) a1[i - 1] * 1.05;
		a1[i] = max(a1[i], a1[i - 1] + 1);
	}
}

void decode(ll x, int &l, int &d){
	l = x % maxm;
	d = l + a1[x / maxm] - 1; 
}

int Answer(long long S, long long T){
	int la, ra; decode(S, la, ra);
	int lb, rb; decode(T, lb, rb);
	if(lb <= la && ra <= rb)
		return 0;

	if(la <= lb && rb <= ra)
		return 1;

	return 2;
}