/*
Idea:
- http://hsin.hr/coci/archive/2006_2007/
- similar solution but implemented with binary search
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 500111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

pii v[maxn], tren[maxn];
int arr[maxn], par[maxn], n;
bool used[maxn];

stack<int> s;
deque<pii> q;

void add(int x){
	int ind = 0;
	while(x <= n && !used[x]){
		tren[ind++] = mp(arr[x], x);
		used[x] = 1;
		x = par[x];
	}

	for(int i = ind - 1; i >= 0; i--)
		q.push_front(tren[i]);
}

void remove(int x){
	while(!q.empty() && q.front().se <= x)
		q.pop_front();
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", arr + i);

	for(int i = n - 1; i >= 0; i--){
		while(s.size() && arr[s.top()] < arr[i])
			s.pop();

		if(s.size())
			par[i] = s.top();
		else
			par[i] = n;

		s.push(i);
	}

	used[n] = 1;
	ll ans = 0;
	for(int i = 0; i < n - 1; i++){
		remove(i);
		add(i + 1);	

		if(arr[i] < arr[i + 1]){
			ans++;
			continue;
		}

		int l = 0, d = q.size() - 1, mid, cur = -1;
		while(l <= d){
			mid = (l + d) / 2;

			if(q[mid].fi <= arr[i]){
				cur = mid;
				l = mid + 1;
			}
			else
				d = mid - 1;
		} 

		if(cur != q.size() - 1)
			cur++;

		ans += 1 + cur; 
	}

	printf("%lld\n", ans);
	return 0;
}