/*
Idea:
- http://blog.brucemerry.org.za/2014/07/ioi-2014-day-2-analysis.html (Friend)
*/

#include "friend.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((int) 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int val[maxn];

int findSample(int n, int confidence[], int host[], int protocol[]){
	for(int i = 0; i < n; i++)
		val[i] = confidence[i];

	int ans = 0;		
	for(int i = n - 1; i > 0; i--){
		int a = host[i];
		int b = i;

		if(protocol[i] == 0){
			ans += val[b];
			val[a] -= val[b];
			val[a] = max(val[a], 0);
		}
			
		if(protocol[i] == 1)
			val[a] += val[b];

		if(protocol[i] == 2)
			val[a] = max(val[a], val[b]);
	}

	ans += val[0];
	return ans;
}