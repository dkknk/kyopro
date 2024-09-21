#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct S{
    ll siz,sum;
    S(ll siz,ll sum) : siz(siz),sum(sum){}
};

template <typename T,typename U>
struct Rerooting{
    struct edge{
        int to;
        U cost;
        edge(int t,U c) : to(t),cost(c){};
    };
    int n;
    //g(merge(f(v1),...,f(vk)))
    function<T(T,T)> merge;
    function<T(int,T)> f;
    function<T(int,T)> g;
    T id,ini;
    vector<vector<edge>> tree;
    vector<vector<T>> cuml,cumr;
    vector<int> par;
    vector<T> dp,dp2;//,table;
    bool is_calc = false;

    Rerooting(int n,T id,function<T(T,T)> merge,function<T(int,T)> f,function<T(int,T)> g): n(n),id(id),ini(id),merge(merge),f(f),g(g){
        tree.resize(n);
        cuml.resize(n);
        cumr.resize(n);
        par.resize(n);
        dp.assign(n,id);
        dp2.assign(n,id);
    }
    Rerooting(int n,T id,T ini,function<T(T,T)> merge,function<T(int,T)> f,function<T(int,T)> g):
        n(n),id(id),ini(ini),merge(merge),f(f),g(g){
        tree.resize(n);
        cuml.resize(n);
        cumr.resize(n);
        par.resize(n);
        dp.assign(n,id);
        dp2.assign(n,id);
    }
    void add_edge(int u,int v,U c = 1){
        tree[u].emplace_back(v,1);
        tree[v].emplace_back(u,1);
    }

    void dfs(int v,int p = -1){
        par[v] = p;
        for(auto e : tree[v]){
            if(p == e.to) continue;
            dfs(e.to,v);
            dp[v] = merge(dp[v],f(e.to,dp[e.to]));
        }
        if(tree[v].size() > 1 || tree[v][0].to != p)
            dp[v] = g(v,dp[v]);
        else
            dp[v] = ini;
    }

    void dfs2(int v,int p = -1){
        int idx = 0;
        for(auto e : tree[v]){
            if(e.to == p) continue;
            dp2[e.to] = g(v,merge(dp2[v],merge(cuml[v][idx],cumr[v][idx+1])));
            idx++;
            dfs2(e.to,v);
        }
        dp2[v] = g(v,dp2[v]);
    }

    vector<T> calc(){
        if(is_calc) return dp;
        is_calc = true;
        dfs(0);

        for(int v=0;v<n;v++){
            cuml[v].assign(tree[v].size()+1,id);
            cumr[v].assign(tree[v].size()+1,id);

            int idx = 0;
            for(auto e : tree[v]){
                if(e.to == par[v]) continue;
                idx++;
                cuml[v][idx] = merge(cuml[v][idx-1],f(e.to,dp[e.to]));
            }
            for(int i=tree[v].size()-1;i>0;i--){
                if(tree[v][i].to == par[v]) continue;
                cumr[v][idx-1] = merge(cumr[v][idx],f(tree[v][i].to,dp[tree[v][i].to]));
                idx--;
            }
        }

        dfs2(0);
        for(int v=0;v<n;v++) dp[v] = merge(dp[v],dp2[v]);
        return dp;
    }
};
//g(merge(f(v1),...,f(vk)))

int main(){
    //abc220f
    int n; cin >> n;
    auto f = [](int idx,S val)->S{
        return val;
    };
    auto g = [](int idx,S val)->S{
        return S{val.siz + 1,val.sum + val.siz};
    };
    auto merge = [](S a,S b)->S{
        return S{a.siz + b.siz,a.sum + b.sum};
    };

    Rerooting<S,int> re(n,S{0,0},S{1,0},merge,f,g);
    for(int i=0;i<n-1;i++){
        int s,t; cin >> s >> t;
        s--;t--;
        re.add_edge(s,t);
    }
    vector<S> dp = re.calc();
    for(int i=0;i<n;i++){
        cout << dp[i].sum << endl;
    }
}
