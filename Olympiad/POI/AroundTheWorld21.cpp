#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 30)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int odsek[maxn], jump[maxn];

int mod(int x, int m){
	return x >= m ? x - m : x;
}

int solve(int n, int skok){
	int sum = 0, j = 0;

	for(int i = 0; i < n; i++){
		while(sum + odsek[mod(j, n)] <= skok){
			sum += odsek[mod(j, n)];
			j++;
		}
		jump[i] = j - i;
		sum -= odsek[i];
	}

	int start = 0;
	for(int i = 0; i < n; i++)
		start = mod(start + jump[start], n);

	int x = start, ans = 0;
	while(x < start + n){
		ans++;
		x = x + jump[mod(x, n)];
	}
	return ans;
}


int main(){
	int n, s, maks = -1;
	scanf("%d%d", &n, &s);
	for(int i = 0; i < n; i++){
		scanf("%d", odsek + i);
		maks = max(maks, odsek[i]);
	}

	while(s--){
		int skok;
		scanf("%d", &skok);
		if(skok < maks){			// can't complete
			printf("NIE\n");
		}
		else
			printf("%d\n", solve(n, skok));
	}


	
	return 0;
}