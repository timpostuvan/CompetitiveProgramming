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

int main(){
	ll a;
	scanf("%lld", &a);
	a++;

	if(a == 1){
		printf("0\n");
		return 0;
	}

	if(a % 2 == 0)
		printf("%lld\n", a / 2);
	else
		printf("%lld\n", a);	
	return 0;
}