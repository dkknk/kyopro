#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include<bits/stdc++.h>
#include "lib/graph/graph.hpp"
#include "lib/utility.hpp"
#include "lib/math/modint.hpp"
#include "lib/data-structure/lazysegtree.hpp"
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

using mint = modint998244353;
struct S{
    mint val;
    int len;
};
struct F{
    mint b,c;
};
S op(S l,S r){
    return S{l.val+r.val,l.len+r.len};
}
S e(){return S{0,0};}
S mapping(F f,S s){
    return S{s.val*f.b+s.len*f.c,s.len};
}
F composition(F f,F g){
    return F{f.b*g.b,f.b*g.c+f.c};
}
F id(){return F{1,0};}
void solve(){
    int n,q; cin >> n >> q;
    vector<int> a(n);
    rep(i,0,n) cin >> a[i];
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
    rep(i,0,n) seg.set(i,S{a[i],1});
    while(q--){
        int t; cin >> t;
        if(t){
            int l,r; cin >> l >> r;
            cout << seg.prod(l,r).val.val() << "\n";
        }
        else{
            int l,r,b,c; cin >> l >> r >> b >> c;
            seg.apply(l,r,F{mint::raw(b),mint::raw(c)});
        }
    }
}