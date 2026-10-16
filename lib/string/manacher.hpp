// https://github.com/dkknk/kyopro/blob/main/lib/string/manacher.hpp
#pragma once
using namespace std;
vector<int> manacher(const string &s) { //https://ei1333.github.io/luzhiled/snippets/string/manacher.html
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
  return radius;
}