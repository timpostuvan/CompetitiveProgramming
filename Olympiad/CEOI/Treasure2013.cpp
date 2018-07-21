/*
Idea:
- http://ceoi2013.hsin.hr/tasks/tasks_and_solutions.pdf
*/

#include "treasure.h"
#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

int pre[maxn][maxn];

void findTreasure(int N){
	int n = N;
	int mid = n / 2;

	for(int i = n; i >= 1; i--){
		for(int j = n; j >= 1; j--){
			if(i > mid && j > mid)
				pre[i][j] = countTreasure(1, 1, i, j);

			if(i <= mid && j > mid)
				pre[i][j] = pre[n][j] - countTreasure(i + 1, 1, n, j);
			
			if(i > mid && j <= mid)
				pre[i][j] = pre[i][n] - countTreasure(1, j + 1, i, n);
			
			if(i <= mid && j <= mid)
				pre[i][j] = -pre[n][n] + pre[n][j] + pre[i][n] + countTreasure(i + 1, j + 1, n, n);
		}
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(pre[i][j] - pre[i - 1][j] - pre[i][j - 1] + pre[i - 1][j - 1] == 1)
				Report(i, j);
		}
	}   		
}