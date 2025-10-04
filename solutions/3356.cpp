/******************************************************************************
Link: https://cses.fi/problemset/task/3356
Code: 3356
Time (YYYY-MM-DD-hh.mm.ss): 2025-09-30-15.28.31
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
set<int> pos[MAXN * 2 + 1];
vector<int> values;
vector<tuple<int, int, int>> queries;
int n, q, arr[MAXN + 5];

void compress(){
    sort(begin(values), end(values));
    values.erase(unique(begin(values), end(values)), end(values));
}

int getval(int value){
    return lower_bound(begin(values), end(values), value) - begin(values);
}

struct SegmentTree{
    struct Node{
        int value, idx;

        static Node Identity(){
            Node res;
            res.value = 1e9;
            res.idx = -1;

            return res;
        }

        void renew(){
            if(idx == -1) return;

            int val = getval(arr[idx]);
            auto nxt = pos[val].upper_bound(idx);
            value = nxt == pos[val].end() ? n + 1 : *nxt;
        }

        Node mergeUpdate(Node& other){
            this->renew();
            other.renew();

            Node res;
            if(this->value < other.value){
                res.value = this->value;
                res.idx = this->idx;
            }
            else{
                res.value = other.value;
                res.idx = other.idx;
            }

            return res;
        }

        Node merge(Node& other){
            Node res;
            if(this->value < other.value){
                res.value = this->value;
                res.idx = this->idx;
            }
            else{
                res.value = other.value;
                res.idx = other.idx;
            }

            return res;
        }
    };

    vector<Node> nodes;

    SegmentTree(){
        nodes.resize(n * 2 + 1);
    }

    void build(){
        for(int i = 0; i < n; ++i){
            nodes[i + n].idx = i + 1;
            nodes[i + n].renew();
        }

        for(int id = n - 1; id > 0; --id){
            nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
        }
//        cerr << "nodes:\n";
//        for(int id = 0; id < n * 2; ++id){
//            cerr << id << ": " << nodes[id].value << '\n';
//        }
    }

    void update(int idx, int value){
        pos[getval(arr[idx])].erase(idx);
        arr[idx] = value;
        int id = idx - 1 + n;

        int val = getval(value);
        pos[getval(value)].insert(idx);
        auto nxt = pos[val].upper_bound(idx);
        if(nxt == pos[val].end()) nodes[id].value = n + 1;
        else nodes[id].value = *nxt;

        while(id > 1){
            id >>= 1;
            nodes[id] = nodes[id << 1].mergeUpdate(nodes[id << 1 | 1]);
        }
    }

    Node get(int l, int r){
        --l;
        l += n; r += n;

        Node res = Node::Identity();
        while(l < r){
            if(l & 1) res = res.mergeUpdate(nodes[l++]);
            if(r & 1) res = res.mergeUpdate(nodes[--r]);
            l >>= 1; r >>= 1;
        }

        return res;
    }

    bool distinct(int l, int r){
        return get(l, r).value > r;
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // freopen("3356.INP","r",stdin);
    // freopen("3356.OUT","w",stdout);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
        values.push_back(arr[i]);
    }

    for(int qr = 1; qr <= q; ++qr){
        int type, x, y;
        cin >> type >> x >> y;

        queries.push_back({type, x, y});
        values.push_back(y);
    }

    compress();
    for(int i = 1; i <= n; ++i){
        pos[getval(arr[i])].insert(i);
    }

//    for(int ele: values){
//        cerr << ele << ": ";
//        for(int id: pos[getval(ele)]) cerr << id << ' '; cerr << '\n';
//    }

    SegmentTree seg;
    seg.build();
    for(int qr = 0; qr < q; ++qr){
        int type, x, y;
        tie(type, x, y) = queries[qr];

        if(type == 1){
            seg.update(x, y);
        }
        else{
//            cout << (seg.get(x, y).value) << '\n';
            cout << (seg.distinct(x, y) ? "YES" : "NO") << '\n';
        }
    }

//    cerr << "----\n";
//    for(int ele: values){
//        cerr << ele << ": ";
//        for(int id: pos[getval(ele)]) cerr << id << ' '; cerr << '\n';
//    }

    return 0;
}
