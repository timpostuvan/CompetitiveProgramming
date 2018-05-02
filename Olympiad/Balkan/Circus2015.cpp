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


// DELA SAMO ZA 51 PIK


int dp[maxn];
bool used[maxn];
int a[maxn], n, m;

void init(int N, int M, int ARR[]){
	n = N;
	m = M;
	for(int i = 0; i < n; i++){
		a[i] = ARR[i];
		dp[i] = INF;
	}

	a[n] = m;
	dp[n] = 0;

	for(int k = 0; k < n; k++){
		int mini = -1;
		for(int i = 0; i <= n; i++){
			if(used[i])
				continue;

			if(mini == -1 || dp[mini] > dp[i])	
				mini = i;
		}

		used[mini] = 1;

		for(int i = 0; i <= n; i++){
			if(abs(a[mini] - a[i]) >= dp[mini])
				dp[i] = min(dp[i], abs(a[mini] - a[i]));
		}
	}



//	for(int i = 0; i <= n; i++)
//		cout << i << "  " << dp[i] << endl;
}

int minLength(int x){
	int ans = INF;
	for(int i = 0; i <= n; i++){
		if(abs(a[i] - x) >= dp[i])
			ans = min(ans, abs(a[i] - x));
	}
	return ans;
}

int arr[maxn];

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++)
		scanf("%d", arr + i);

	init(n, m, arr);
	
	int q;
	scanf("%d", &q);
	while(q--){
		int x;
		scanf("%d", &x);
		printf("%d\n", minLength(x));
	}
	return 0;
}