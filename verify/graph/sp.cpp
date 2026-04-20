#line 1 "sp.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path" // 例
#include <bits/stdc++.h>
#line 3 "graph.hpp"
using namespace std;

template <typename T>
struct Edge{
    int src,to;
    T cost;

    Edge(int to,T cost) : src(-1),to(to),cost(cost){}
    Edge(int scr,int to,T cost) : src(-1),to(to),cost(cost){}
    Edge &operator = (const int &x){
        to = x;
        return *this;
    }
    operator int() const{return to;}
};

template<class T>
using Edges = vector<Edge<T>>;
template<class T>
using WeightedGraph = vector<Edges<T>>;
template<class T>
using UnWeightedGraph = vector<vector<int>>;
#line 4 "sp.test.cpp"
using namespace std;
using ll = long long;
using P = tuple<ll,int,int>;

int main() {
    int n,m,s,t;
    cin >> n >> m >> s >> t;
    WeightedGraph<ll> graph(n);
    for(int i=0;i<m;i++){
        int a,b,c;
        cin >> a >> b >> c;
        graph[a].emplace_back(a,b,c);
    }
    priority_queue<P,vector<P>,greater<P>> pq;
    pq.push({0,s,-1});
    vector<ll> dist(n,1LL<<60);
    vector<int> from(n,-1);
    while(!pq.empty()){
        auto [d,v,f] = pq.top(); pq.pop();
        if(dist[v] <= d) continue;
        dist[v] = d;
        from[v] = f;
        for(auto [_,u,c] : graph[v]){
            pq.push({d+c,u,v});
        }
    }
    if(dist[t] == 1LL << 60){
        cout << "-1\n";
        return 0;
    }
    vector<int> vs;
    int v = t;
    while(from[v] != -1){
        vs.push_back(v);
        v = from[v];
    }
    vs.push_back(v);
    reverse(vs.begin(),vs.end());
    cout << dist[t] << " " << vs.size()-1 << "\n";
    for(int i=0;i<vs.size()-1;i++)
        cout << vs[i] << " " << vs[i+1] << "\n";
}
