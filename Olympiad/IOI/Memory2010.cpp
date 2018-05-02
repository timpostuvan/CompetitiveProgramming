#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> v[33];

void play(){
	for(int i = 1; i <= 25; i++){
		char c = faceup(2 * i);
		v[c - 'A'].push_back(2 * i);
		c = faceup(2 * i - 1);
		v[c - 'A'].push_back(2 * i - 1);
	}
	for(int i = 0; i < 25; i++){
		faceup(v[i][0]);
		faceup(v[i][1]);
	}
}