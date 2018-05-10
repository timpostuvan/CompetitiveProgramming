#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;

int main(){
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	printf("%d\n", min(abs(a - c), abs(b - c)) + abs(a - b));
	return 0;
}