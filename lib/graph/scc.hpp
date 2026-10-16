#pragma once
// https://github.com/dkknk/kyopro/blob/main/lib/graph/scc.hpp
#include "lib/graph/graph.hpp"

struct scc{
    int n,id;
    vector<int> ord,see,leader,leaders;
    vector<vector<int>> graph,rgraph,scc_graph,conn;
    scc(int n):n(n){
        graph.resize(n);
        rgraph.resize(n);
        scc_graph.resize(n);
        conn.resize(n);
        ord.resize(n);
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
            for(auto u : graph[v]) 
                self(self,u);
            ord[id++] = v;
        };
        for(int v=0;v<n;v++){
            if(see[v]) continue;
            dfs(dfs,v);
        }
        for(int i=0;i<n;i++) see[i]=0;
        auto dfs2 = [&](auto self,int r,int v){
            if(see[v]) return;
            see[v] = 1;
            conn[r].push_back(v);
            leader[v] = r;
            for(auto u : rgraph[v]) 
                self(self,r,u);
        };
        for(int v=n-1;v>=0;v--){
            if(see[ord[v]]) continue;
            leaders.push_back(ord[v]);
            dfs2(dfs2,ord[v],ord[v]);
        }
        for(int v=0;v<n;v++){
            for(auto u : graph[v]){
                scc_graph[leader[v]].push_back(leader[u]);
            }
        }
        for(auto v : leaders){
            sort(scc_graph[v].begin(),scc_graph[v].end());
            scc_graph[v].erase(unique(scc_graph[v].begin(),scc_graph[v].end()),scc_graph[leader[v]].end());
        }
    }
};