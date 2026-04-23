#pragma once
using namespace std;
vector<int> manacher2(const string &tmp) { 
  int n = tmp.size();
  string s;
  s += '#';
  for(int i=0;i<n;i++){
    s += tmp[i];
    s += '#';
  }
  vector<int> radius(s.size());
  int i = 0, j = 0;
  while(i < s.size()) {
    while(i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) {
      ++j;
    }
    radius[i] = j;
    int k = 1;
    while(i - k >= 0 && i + k < s.size() && k + radius[i - k] < j) {
      radius[i + k] = radius[i - k];
      ++k;
    }
    i += k;
    j -= k;
  }
  for(int i=1;i<2*n;i++){
      radius[i] = (radius[i]>>1)<<1;
      if(i%2) radius[i]--;
  }
  return vector<int>(radius.begin()+1,radius.end()-1);
}