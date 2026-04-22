#include<lib/graph/graph.hpp>

struct scc{
    int n,id;
    vector<int> ord,see,leader;
    vector<vector<int>> graph,rgraph,scc_graph,conn;
    scc(int n):n(n){
        graph.resize(n);
        rgraph.resize(n);
        scc_graph.resize(n);
        conn.resize(n);
        ord.resize(n+1);
        see.assign(n,0);
        leader.assign(n,0);
    }
    void add_edge(int a,int b){
        graph[a].emplace_back(b);
        rgraph[b].emplace_back(a);
    }
    void calc(){
        id = 0;
        auto dfs = [&](auto self,int v){
            if(see[v]) return;
            see[v] = 1;
            ord[id++] = v;
            for(auto u : graph[v]) 
                self(self,u);
        };
        for(int v=0;v<n;v++){
            if(see[v]) continue;
            dfs(dfs,v);
        }
        for(int i=0;i<n;i++) see[i]=0;
        auto dfs2 = [&](auto self,int r,int v){
            if(see[v]) return;
            conn[r].push_back(v);
            leader[v] = r;
            see[v] = 1;
            ord[id++] = v;
            for(auto u : rgraph[v]) 
                self(self,r,u);
        };
        for(int v=n-1;v>=0;v--){
            if(see[v]) continue;
            dfs2(dfs2,v,v);
        }
    }
};