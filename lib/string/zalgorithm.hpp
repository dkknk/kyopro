#pragma once
using namespace std;

vector<int> z_algorithm(const string &s){ //https://qiita.com/Pro_ktmr/items/16904c9570aa0953bf05
    int n = s.length();
    vector<int> Z(n);
    Z[0] = s.size();
    int i=1,j=0;
    while(i < s.size()){
        while(i+j < s.size() && s[j] == s[i+j]) j++;
        Z[i] = j;
        if(j == 0){
            i++;
            continue;
        }
        int k=1;
        while(k < j && k+Z[k] < j){
            Z[i+k] = Z[k];
            k++;
        }
        i += k;
        j -= k;
    }
    return Z;
}