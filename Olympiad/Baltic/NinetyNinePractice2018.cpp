#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 110

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int main(){
	cout << (rand() % 2) + 1 << endl;

	int x;
	while(x != 99){
		cin >> x;

		if(x == 99)
			break;

		if(x % 3 == 0)
			x = x + (rand() % 2) + 1;
		else
			x = (x / 3 + 1) * 3;

		cout << x << endl;
	}

	return 0;
}