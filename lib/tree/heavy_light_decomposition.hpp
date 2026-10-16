// https://github.com/dkknk/kyopro/blob/main/lib/tree/heavy_light_decomposition.hpp
#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

struct heavy_light_decomposition{
    int n,root;
    std::vector<std::vector<int>> tree;
    std::vector<int> size,pre_id,post_id,head,depth,parent;
    heavy_light_decomposition(int n,int root = 0) : n(n),root(root){
        tree.resize(n);
        size.assign(n,0);
        pre_id.assign(n,0);
        post_id.assign(n,0);
        head.assign(n,0);
        depth.assign(n,0);
        parent.assign(n,0);
    }
    void add_edge(int u,int v){
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }
    void calc(){
        auto dfs = [&](auto self,int d,int v,int p=-1)->void{
            size[v] = 1;
            depth[v] = d;
            parent[v] = p;
            int m = 0;
            for(auto u : tree[v]){
                if(u == p) continue;
                self(self,d+1,u,v);
                size[v] += size[u];
                m = std::max(m,size[u]);
            }
            for(int i=0;i<tree[v].size();i++){
                if(tree[v][i] == p) continue;
                if(size[tree[v][i]] == m){
                    if(tree[v][0] == p) std::swap(tree[v][1],tree[v][i]);
                    else std::swap(tree[v][0],tree[v][i]);
                    break;
                }
            }
        };
        dfs(dfs,0,root);
        int id = 0;
        auto dfs2 = [&](auto self,int h,int v,int p=-1)->void{
            pre_id[v] = id++;
            head[v] = h;
            bool first = true;
            for(int i=0;i<tree[v].size();i++){
                if(tree[v][i] == p) continue;
                if(first){
                    self(self,h,tree[v][i],v);
                    first = false;
                }
                else self(self,tree[v][i],tree[v][i],v);
            }
            post_id[v] = id;
        };
        dfs2(dfs2,root,root);
    }
    std::pair<int,int> subtree(int v){ //[in,out)
        assert(0 <= v && v < n);
        return {pre_id[v],post_id[v]};
    }
    std::vector<std::pair<int,int>> path(int u,int v){
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);

        std::vector<std::pair<int,int>> ret;
        while(head[u] != head[v]){
            if(pre_id[u] < pre_id[v]){
                ret.emplace_back(pre_id[head[v]],pre_id[v]+1);
                v = parent[head[v]];
            }
            else{
                ret.emplace_back(pre_id[head[u]],pre_id[u]+1);
                u = parent[head[u]];
            }
        }
        if(depth[v] < depth[u]) std::swap(u,v);
        ret.emplace_back(pre_id[u],pre_id[v]+1);
        return ret;
    }
    int lca(int u,int v){
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);

        while(head[u] != head[v]){
            if(pre_id[u] < pre_id[v])
                v = parent[head[v]];
            else
                u = parent[head[u]];
        }
        if(depth[u] < depth[v]) return u;
        else return v;
    }
    int dist(int u,int v){
        return depth[u] + depth[v] - 2*depth[lca(u,v)];
    }
};