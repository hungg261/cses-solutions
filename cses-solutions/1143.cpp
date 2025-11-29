#include<bits/stdc++.h>
#define int long long
using namespace std;

/*
    credit: hungg261 (me)
    template segment tree (v1)
*/
struct SegmentTree{
    struct Node{
        int value;
        Node(int x = 0){ value = x; }
    };

    vector<Node> Nodes;
    vector<int> a;
    int n;

    void init(){ Nodes.resize(n * 4 + 5); }

    SegmentTree() = default;
    SegmentTree(int n, int value = 0){ a.resize(n + 1, value); this->n = n; }

    Node PLACEHOLDER = Node(LLONG_MIN);
    Node mergeNodes(const Node& u, const Node& v){
        Node res;
        res.value = max(u.value, v.value);

        return res;
    }

    void build(int id, int l, int r){
        if(l == r){
            Nodes[id] = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        Nodes[id] = mergeNodes(Nodes[id * 2], Nodes[id * 2 + 1]);
    }

    void update(int id, int l, int r, int idx, int value){
        if(r < idx || idx < l) return;

        if(l == r){
            Nodes[id] = value;
            return;
        }

        int mid = (l + r) / 2;
        update(id * 2, l, mid, idx, value);
        update(id * 2 + 1, mid + 1, r, idx, value);
        Nodes[id] = mergeNodes(Nodes[id * 2], Nodes[id * 2 + 1]);
    }

    Node get(int id, int l, int r, int u, int v){
        if(r < u || v < l) return PLACEHOLDER;

        if(u <= l && r <= v){
            return Nodes[id];
        }

        int mid = (l + r) / 2;
        Node left = get(id * 2, l, mid, u, v),
            right = get(id * 2 + 1, mid + 1, r, u, v);

        return mergeNodes(left, right);
    }

    void build(){ init(); build(1, 1, n); }
    void update(int idx, int value){ update(1, 1, n, idx, value); }
    Node get(int l, int r){ return get(1, 1, n, l, r); }
};

int find_first_geq(int target, SegmentTree& segtree){
    int l = 1, r = segtree.n, res = 0;
    while(l <= r){
        int mid = (l + r) / 2;
        if(segtree.get(1, mid).value >= target){
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return res;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;

    vector<int> r(m + 1);
    SegmentTree segg(n);

    for(int i = 1; i <= n; ++i) cin >> segg.a[i];
    for(int i = 1; i <= m; ++i) cin >> r[i];

    segg.build();

    for(int i = 1; i <= m; ++i){
        int find_idx = find_first_geq(r[i], segg);
        cout << find_idx << ' ';

        segg.a[find_idx] -= r[i];
        segg.update(find_idx, segg.a[find_idx]);
    }

    return 0;
}
