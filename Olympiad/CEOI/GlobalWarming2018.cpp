/*
Idea:
- https://ceoi2018.pl/wp-content/uploads/2018/08/solutions_day1.pdf (Global Warming)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int pre[maxn], suf[maxn];
int best[maxn], arr[maxn];

int findSmaller(int x){
	int l = 0, d = maxn - 1, mid, ans = -1;
	while(l <= d){
		mid = (l + d) / 2;
		if(best[mid] < x){
			l = mid + 1;
			ans = mid;
		}
		else
			d = mid - 1;
	}
	return ans;
}

int findLarger(int x){
	int l = 0, d = maxn - 1, mid, ans = -1;
	while(l <= d){
		mid = (l + d) / 2;
		if(best[mid] > x){
			l = mid + 1;
			ans = mid;
		}
		else
			d = mid - 1;
	}
	return ans;
}

int main(){
	int n, d;
	scanf("%d%d", &n, &d);
	for(int i = 1; i <= n; i++)
		scanf("%d", arr + i);

	for(int i = 0; i < maxn; i++)
		best[i] = -1;
	best[0] = INF;

	for(int i = n; i >= 1; i--){
		int val = findLarger(arr[i]);
		suf[i] = val + 1;
		best[suf[i]] = max(best[suf[i]], arr[i]);
	}

	for(int i = 0; i < maxn; i++)
		best[i] = INF;
	best[0] = 0;

	int ans = 0;
	for(int i = 1; i <= n; i++){
		int val = findSmaller(arr[i] + d);
		ans = max(ans, val + suf[i]);

		val = findSmaller(arr[i]);
		pre[i] = val + 1;
		best[pre[i]] = min(best[pre[i]], arr[i]);
	}

	printf("%d\n", ans);
	return 0;
}