#include "paint.h"
#include <bits/stdc++.h>
using namespace std;

#define maxn 200111
#define maxk 211

int n, k;
char t[maxn];
int pre[maxn];
bool l[maxk][maxn], r[maxk][maxn];
int empty[maxn], full[maxn];

bool has_white(int a, int b){
	return pre[b] != pre[a - 1];
}

string solve_puzzle(string s, vector<int> c) {
	n = s.size();
	k = c.size();

	for(int i = 1; i <= n; i++)
		t[i] = s[i - 1];

	t[n + 1] = '_';
	n++;

	for(int i = 1; i <= n; i++)
		pre[i] = pre[i - 1] + (t[i] == '_');

	l[0][0] = 1;
	for(int i = 0; i <= k; i++){
		for(int j = 1; j <= n; j++){
			if(t[j] == 'X')
				continue;

			l[i][j] = l[i][j - 1];
			if(i > 0 && j >= c[i - 1] + 1 && !has_white(j - c[i - 1], j - 1))
				l[i][j] |= l[i - 1][j - c[i - 1] - 1];
		}
	}


	r[k][n + 1] = 1;
	for(int i = k; i >=0; i--){
		for(int j = n; j; j--){
			if(t[j] != 'X')
				r[i][j] = r[i][j + 1];
			if(i < k && j + c[i] <= n && t[j + c[i]] != 'X' && !has_white(j, j + c[i] - 1))
				r[i][j] |= r[i + 1][j + c[i] + 1];
		}
	}


	for(int i = 1; i < n; i++){
		for(int j = 0; j <= k; j++){
			if(l[j][i] && r[j][i + 1] && t[i] != 'X'){
				empty[i] = 1;
			}
		}
	}


	for(int i = 1; i <= k; i++){
		for(int j = 0; j <= n - 1 - c[i - 1]; j++){
			if(l[i - 1][j] && r[i][j + c[i - 1] + 2] && !has_white(j + 1, j + c[i - 1]) && t[j] != 'X' && t[j + c[i - 1] + 1] != 'X'){
				full[j + 1]++;
				full[j + c[i - 1] + 1]--;
			}
		}
	}

	for(int i = 1; i <= n; i++)
		full[i] += full[i - 1];

	string ans;
	for(int i = 1; i < n; i++){
		if(full[i] && empty[i])
			ans.push_back('?');
		else if(full[i])
			ans.push_back('X');
		else if(empty[i])
			ans.push_back('_');
	}
	return ans;
}