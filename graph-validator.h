#include "testlib.h"
#include <bits/stdc++.h>

namespace graph_val{
    struct union_find{
        std::vector<int> p;
        union_find(int n) : p(n+1) { std::iota(p.begin(), p.end(), 0); }
        int find(int v){ return v == p[v] ? v : p[v] = find(p[v]); }
        bool merge(int u, int v){ return find(u) != find(v) && (p[p[u]]=p[v], true); }
        bool is_connected(int u, int v){ return find(u) == find(v); }
    };

    bool is_undirected_connected_graph(int n, const std::vector<std::pair<int,int>> &edges){
        union_find uf(n);
        for(const auto &[u,v] : edges) uf.merge(u, v);
        for(int i=2; i<=n; i++) if(!uf.is_connected(1, i)) return false;
        return true;
    }

    bool is_undirected_simple_connected_graph(int n, std::vector<std::pair<int,int>> edges){
        if(!is_undirected_connected_graph(n, edges)) return false;
        for(const auto &[u,v] : edges) if(u == v) return false;
        for(auto &[u,v] : edges) if(u > v) std::swap(u, v);
        sort(edges.begin(), edges.end());
        for(int i=1; i<edges.size(); i++) if(edges[i-1] != edges[i]) return false;
        return true;
    }

    bool is_forest(int n, const std::vector<std::pair<int,int>> &edges){
        union_find uf(n);
        for(const auto &[u,v] : edges) if(!uf.merge(u, v)) return false;
        return true;
    }

    bool is_tree(int n, const std::vector<std::pair<int,int>> &edges){
        return is_undirected_simple_connected_graph(n, edges) && is_forest(n, edges);
    }

    bool is_directed_acyclic_graph(int n, std::vector<std::pair<int,int>> &edges){
        std::vector<int> in(n+1);
        std::vector<std::vector<int>> gph(n+1);
        for(const auto &[u,v] : edges) gph[u].push_back(v), in[v]++;

        std::queue<int> que;
        for(int i=1; i<=n; i++) if(!in[i]) que.push(i);
        while(!que.empty()){
            int v = que.front(); que.pop();
            for(auto i : gph[v]) if(!--in[i]) que.push(i);
        }
        return std::count(in.begin(), in.end(), 0) == in.size();
    }
}
