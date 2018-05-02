#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

void Solve(){
	int arr[3] = {1, 1, 1};
   	int ret = Theory(arr[0], arr[1], arr[2]);
   	while(ret != 0){
   		arr[ret - 1]++;
   		ret = Theory(arr[0], arr[1], arr[2]);
   	}
}