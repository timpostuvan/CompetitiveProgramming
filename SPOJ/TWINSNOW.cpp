/*
Idea:

-try all possible orientation of arms that represent the same snowflake
-for every snowflake take the lexicographically minimal orientation
-sort all snowflakes and if two have the same sizes then we found a match 

*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 29)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
 
int arr[6];
vector<vector<int> > all;
vector<int> cur;
 
int main(){
	vector<int> here(6);
 
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		vector<int> cur = {INF, INF, INF, INF, INF, INF};
 	
 
		for(int j = 0; j < 6; j++)
			scanf("%d", arr + j);
 
		for(int j = 0; j < 6; j++){
			for(int k = 0; k < 6; k++)
				here[k] = arr[(j + k) % 6];
 
			if(here < cur)
				cur = here;
		}
 
		reverse(arr, arr + 6);
 
		for(int j = 0; j < 6; j++){
			for(int k = 0; k < 6; k++)
				here[k] = arr[(j + k) % 6];
 
			if(here < cur)
				cur = here;
		}
 
		all.pb(cur);
	}
 
	sort(all.begin(), all.end());
 
	for(int i = 0; i < n - 1; i++){
		if(all[i] == all[i + 1]){
			printf("Twin snowflakes found.\n");
			return 0;
		}
	}
 
	printf("No two snowflakes are alike.\n");	
	return 0;
}  