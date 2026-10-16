// https://github.com/dkknk/kyopro/blob/main/lib/data-structure/staticpointaddrectanglesum.hpp
#pragma once
#include <vector>
#include <tuple>
#include <lib/data-structure/fenwicktree.hpp>

template <typename T>
struct Point_Add_Rectangle_Sum{
    std::vector<std::tuple<int,int,int,T,int>> qs;
    std::vector<int> ys;
    int id;
    bool add_is_done;
    Point_Add_Rectangle_Sum(){
        id = 0;
        add_is_done = false;
    }
    void add(int x,int y,T w){
        assert(!add_is_done);
        qs.emplace_back(x,1,y,w,id++);
        ys.emplace_back(y);
    }
    void sum(int l,int d,int r,int u){
        add_is_done = true;
        ys.emplace_back(u);
        ys.emplace_back(d);
        qs.emplace_back(r,0,u,1,id);
        qs.emplace_back(r,0,d,-1,id);
        qs.emplace_back(l,0,u,-1,id);
        qs.emplace_back(l,0,d,1,id++);
    }
    std::vector<T> calc(){
        std::vector<T> ret(qs.size());
        sort(qs.begin(),qs.end());
        sort(ys.begin(),ys.end());
        ys.erase(unique(ys.begin(),ys.end()),ys.end());
        fenwick_tree<T> fw(ys.size());
        for(auto [x,t,y,w,id] : qs){
            y = lower_bound(ys.begin(),ys.end(),y)-ys.begin();
            if(t){
                fw.add(y,w);
            }
            else{
                ret[id] += w*fw.sum(0,y);
            }
        }
        return ret;
    }
};