#include <bits/stdc++.h>
 
using namespace std;
 
#define maxn 200011
 
long double x[maxn], r[maxn];
long double rad[maxn];
 
stack<pair<long double, long double> > s;
 
long double f(pair<long double, long double> a, long double x2){
  long double x1 = a.first;
  long double r1 = a.second;
  return ((x2 - x1) * (x2 - x1) / (4.0 * r1));
}
 
int main(){
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++)
    cin >> x[i] >> r[i];
   
  s.push(make_pair(x[0], r[0]));
  rad[0] = r[0];
   
  for(int i = 1; i < n; i++){
    long double tren = r[i];
    while(!s.empty()){
      tren = min(tren, f(s.top(), x[i]));
      if(tren >= s.top().second) s.pop();
      else break;
    }
    s.push(make_pair(x[i], tren));
    rad[i] = tren;
  }
  for(int i = 0; i < n; i++)
    cout << fixed << setprecision(3) << rad[i] << "\n";   
  return 0;
}