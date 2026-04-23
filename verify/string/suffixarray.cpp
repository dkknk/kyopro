#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include<bits/stdc++.h>
#include "lib/graph/graph.hpp"
#include "lib/utility.hpp"
#include "lib/string/suffixarray.hpp"
#define rep(i,j,n) for(int i=j;i<(int)(n);i++)
#define rrep(i,j,n)  for(int i=j;i>=(int)(n);i--)
#define all(x) (x).begin(),(x).end()
#define pb emplace_back
#define perm(c) sort(all(c)); for(bool c##p=1;c##p;c##p=next_permutation(all(c)))
#define UNIQUE(v) sort(v.begin(),v.end()); v.erase(unique(v.begin(),v.end()),v.end())

using namespace std;
using std::cout;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const ll LINF = 1LL << 60LL;
const int IINF = (1 << 30) - 1;

void solve();

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    ll T;
    T = 1;
    /*
       cin >> T;
       */
    while(T--) solve();
}

void solve(){
    string s; cin >> s;
    vector<int> a = suffix_array(s);
    int n = s.length();
    rep(i,0,n) cout << a[i] << " \n"[i==n-1];
}