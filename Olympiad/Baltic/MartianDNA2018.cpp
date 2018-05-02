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

int cnt[maxn];
int arr[maxn];
int minimum[maxn];

int num_ok;

void add(int pos){
	int x = arr[pos];
	if(cnt[x] < minimum[x] && cnt[x] + 1 >= minimum[x])
		num_ok++;

	cnt[x]++;
}

void del(int pos){
	int x = arr[pos];
	if(cnt[x] >= minimum[x] && cnt[x] - 1 < minimum[x])
		num_ok--;

	cnt[x]--;
}

int main(){
	int n, k, r, ans = 2 * maxn;
	scanf("%d%d%d", &n, &k, &r);
	for(int i = 1; i <= n; i++)
		scanf("%d", arr + i);

	for(int i = 1; i <= r; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		minimum[x] = y;
	}



	num_ok = 0;
	int d = 1;						// next to add
	for(int i = 1; i <= n; i++){
		while(d <= n && num_ok < r){
			add(d);
			d++;
		}

		if(num_ok == r)
			ans = min(ans, d - i);

		del(i);
	}
	if(ans == 2 * maxn)
		printf("impossible\n");
	else
		printf("%d\n", ans);
	
	return 0;
}