#pragma once
// https://github.com/dkknk/kyopro/blob/main/lib/graph/functional_graph.hpp
#include<vector>
#include <assert.h>
#include <numeric>
using namespace std;
/*
tree : cycleをつぶしてできる木の辺を逆向きにしている
cycle_rootにtreeの根を格納
root : vからたどっていける根を格納
　　　　比較することで連結成分が判定可能
*/
struct FunctionalGraph{
    int n;
    vector<int> to,root,cycle_roots,is_cycle;
    vector<vector<int>> cycles,rev,tree;
    FunctionalGraph() {}
    FunctionalGraph(const vector<int> &to) : n((int)to.size()),to(to) {}
    void calc(){
        root.resize(n);
        is_cycle.assign(n,0);
        cycles.assign(n,{});
        cycle_roots.clear();
        rev.assign(n,{});
        tree.assign(n,{});
        for(int i=0;i<n;i++){
            assert(0 <= to[i] && to[i] < n);
            rev[to[i]].push_back(i);
        }

        vector<int> color(n,0);
        iota(root.begin(),root.end(),0);

        for(int i=0;i<n;i++){
            if(color[i]) continue;
            //detect cycle
            int r=i;
            while(!color[r]){
                color[r]=i+1;
                r=to[r];
            }
            if(color[r] == i+1){
                is_cycle[r] = 1;
                cycle_roots.push_back(r);
                cycles[r].push_back(r);
                auto dfs = [&](auto self,int v,int p=-1)->void{
                    root[v] = r;
                    if(p != -1){
                        if(is_cycle[p])
                            tree[r].push_back(v);
                        else
                            tree[p].push_back(v);
                    }

                    for(auto u : rev[v]){
                        if(is_cycle[u]) continue;
                        self(self,u,v);
                    }
                };
                for(int v=to[r];v != r;v = to[v]){
                    is_cycle[v] = 1;
                    cycles[r].push_back(v);
                }
                dfs(dfs,r);
                for(int v=to[r];v != r;v = to[v])
                    dfs(dfs,v);
            }
        }
    }
};