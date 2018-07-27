/*
Idea:
- x_i is weight of i-th smallest squark
- Smallest element is x_1 + x_2, second smallest element is x_1 + x_3
- It is not clear which element is x_2 + x_3 (there are more possibilities), so we try every element among first n as x2 + x_3
- If we know 3 elements all other are uniquely determined
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 333

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

vector<int> v;
multiset<int> ms;
set<vector<int> > ans;
int n;

void solve(int a, int b, int c){
	multiset<int> s = ms;

	s.erase(s.find(a + b));
	s.erase(s.find(a + c));
	s.erase(s.find(b + c));

	vector<int> cur;
	cur.pb(a); cur.pb(b); cur.pb(c);

	for(int i = 3; i < n; i++){
		int x = *s.begin() - a;
		for(int j = 0; j < i; j++){
			auto it = s.find(cur[j] + x);
			if(it == s.end())
				return;

			s.erase(it);
		}
		if(cur.back() > x)
			return;

		cur.pb(x);
	}
	ans.insert(cur);
}


int main(){
	scanf("%d", &n);
	for(int i = 0; i < n * (n - 1) / 2; i++){
		int a;
		scanf("%d", &a);
		v.pb(a);
		ms.insert(a);
	}

	sort(v.begin(), v.end());

	for(int i = 2; i < n; i++){
		int ab = v[0];
		int ac = v[1];
		int bc = v[i];

		if((ab + ac + bc) % 2 == 0){
			int abc = (ab + ac + bc) / 2;
			solve(abc - bc, abc - ac, abc - ab);
		}
	}

	printf("%d\n", (int) ans.size());
	for(auto it = ans.begin(); it != ans.end(); it++){
		for(int x : *it)
			printf("%d ", x);
		printf("\n");
	}

	return 0;
}