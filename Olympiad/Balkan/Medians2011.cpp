/*
Idea:
- For a number to be median there have to be (i - 1) greater and (i - 1) smaller numbers
- If we add two numbers greater than current median, median will become the smallest number greater than current median in prefix (same for decrease)
- It is always optimal to add greatest/smallest number
- We also must be sure that median is contained in prefix
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

bool used[maxn];
int med[maxn], max_ind, min_ind, n;
vector<int> ans;

int find_max(){
	while(max_ind >= 1 && used[max_ind] == 1)
		max_ind--;

	used[max_ind] = 1;
	return max_ind;
}

int find_min(){
	while(min_ind <= 2 * n - 1 && used[min_ind] == 1)
		min_ind++;

	used[min_ind] = 1;
	return min_ind;
}

int main(){
	scanf("%d", &n);	
	for(int i = 1; i <= n; i++)
		scanf("%d", med + i);

	ans.pb(med[1]);
	used[med[1]] = 1;

	min_ind = 1;
	max_ind = 2 * n - 1;
	
	for(int i = 2; i <= n; i++){
		if(med[i] == med[i - 1]){
			ans.pb(find_max());
			ans.pb(find_min());
		}

		if(med[i] > med[i - 1]){
			ans.pb(find_max());
			if(used[med[i]])
				ans.pb(find_max());
			else{
				ans.pb(med[i]);
				used[med[i]] = 1;
			}
		}

		if(med[i] < med[i - 1]){
			ans.pb(find_min());
			if(used[med[i]])
				ans.pb(find_min());
			else{
				ans.pb(med[i]);
				used[med[i]] = 1;
			}
		}
	}

	for(int i : ans)
		printf("%d ", i);
	printf("\n");

	return 0;
}