#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char str[3111111], x[3111111];
int small[255], big[255];

bool check(){
  for(int i = 'a'; i <= 'z'; i++) if(small[i] != big[i]) return 0;
  for(int i = 'A'; i <= 'Z'; i++) if(small[i] != big[i]) return 0;
  return 1;
}

int main(){
  int g, s;
  scanf("%d%d", &g, &s);
  scanf("%s %s", x, str);
  for(int i = 0; i < g; i++){
    small[x[i]]++;
    big[str[i]]++;
  }
  int ans = 0;
  ans += check();
  for(int i = g; i < s; i++){
    big[str[i - g]]--;
    big[str[i]]++;
    ans += check();
  } 
  printf("%d\n", ans);
  return 0;
}