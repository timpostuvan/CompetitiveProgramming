/*
Idea:
- http://ceoi.inf.elte.hu/probarch/14/carnival-spoiler.pdf (first solution)
*/

#include <bits/stdc++.h>
  
using namespace std;
  
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define INF (1LL << 55)
#define maxn 155
 
typedef long long ll;
typedef pair<int, int> pii;

int val[maxn];
vector<int> v;

int ask(int l, int d, int x){
	vector<int> cur;
	for(int i = l; i <= d; i++)
		cur.pb(v[i]);

	cur.pb(x);

	cout << cur.size();
	for(int i : cur)
		cout << " " << i;

	cout << endl;

	int ret;
	cin >> ret;
	return ret;
}

  
int main(){
	int n, cnt = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int num = ask(0, v.size() - 1, i);
		if(num == v.size() + 1){
			v.pb(i);
			val[i] = ++cnt;
			continue;
		}

		int l = 0, d = v.size() - 1, mid;
		while(l <= d){
			mid = (l + d) / 2;
			num = ask(l, mid, i);

			if(num == 1){
				val[i] = val[v[l]];
				break;
			}

			if(num == (mid - l + 1 + 1))
				l = mid + 1;

			else
				d = mid;
		}
	}

	cout << "0";
	for(int i = 1; i <= n; i++)
		cout << " " << val[i];

	cout << endl;
	return 0;
}