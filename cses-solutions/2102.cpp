/******************************************************************************
Link: https://cses.fi/problemset/task/2102
Code: 2102
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-13-22.08.45
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int n, k;
string matches[MAXN + 5];
string S;

struct AhoCorasick{
    struct Node{
        int nxt[26];
        int completed;
        int par, failure;
        int ch;
        vector<int> completes;

        Node(){
            memset(nxt, -1, sizeof nxt);
            completed = 0;
            par = -1;
            failure = -1;
            ch = -1;
        }
    };

    vector<Node> T;
    int root;

    AhoCorasick(){
        T.emplace_back();
        root = 0;
    }

    void add(int idx, const string& s){
        int p = root;
        for(char c: s){
            c -= 'a';

            if(T[p].nxt[c] == -1){
                T[p].nxt[c] = T.size();

                T.emplace_back();
                T.back().par = p;
                T.back().ch = c;
            }
            p = T[p].nxt[c];
        }

        ++T[p].completed;
        T[p].completes.push_back(idx);
    }

    void construct(){
        T[root].failure = root;
        queue<int> que;

        for(int c = 0; c < 26; ++c){
            if(T[root].nxt[c] != -1){
                T[T[root].nxt[c]].failure = root;
                que.push(T[root].nxt[c]);
            }
        }
        while(!que.empty()){
            int i = que.front();
            que.pop();

            int j = T[T[i].par].failure;
            while(j != root && (T[j].nxt[T[i].ch] == -1)){
                j = T[j].failure;
            }

            if(T[j].nxt[T[i].ch] != -1 && T[j].nxt[T[i].ch] != i){
                j = T[j].nxt[T[i].ch];
            }
            T[i].failure = j;

            for(int c = 0; c < 26; ++c){
                if(T[i].nxt[c] != -1) que.push(T[i].nxt[c]);
            }
        }
    }

    void dfs(int u){
        for(int c = 0; c < 26; ++c){
            int v = T[u].nxt[c];
            if(v != -1){
                cerr << u << ' ' << v << " " << (char)(T[v].ch+'a') << '\n';
                dfs(v);
            }
        }
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("2102.INP","r",stdin);
    //freopen("2102.OUT","w",stdout);
    cin >> S;
    n = S.size();

    cin >> k;
    AhoCorasick aho;
    for(int i = 0; i < k; ++i){
        cin >> matches[i];
        aho.add(i, matches[i]);
    }

//    aho.dfs(aho.root);

    aho.construct();
//    for(int i = 0; i < aho.T.size(); ++i){
//        cerr << i << ": " << aho.T[i].failure << '\n';
//    }


    int p = aho.root;
    vector<bool> res(k, false);
    for(int i = 0; i < n; ++i){
        while(p > 0 && aho.T[p].nxt[S[i] - 'a'] == -1){
            p = aho.T[p].failure;
            for(int idx: aho.T[p].completes){
                res[idx] = true;
//                cerr << "\t" << idx << '\n';
            }
        }
        if(aho.T[p].nxt[S[i] - 'a'] != -1) p = aho.T[p].nxt[S[i] - 'a'];

//        cerr << p << '\n';

        for(int idx: aho.T[p].completes){
//            cerr << "\t" << idx << '\n';
            res[idx] = true;
        }
    }
    while(p > 0 && aho.T[p].nxt[S.back() - 'a'] == -1){
        p = aho.T[p].failure;
        for(int idx: aho.T[p].completes){
            res[idx] = true;
//            cerr << "\t" << idx << '\n';
        }
    }

    for(int i = 0; i < k; ++i){
        cout << (res[i] ? "YES\n" : "NO\n");
    }

    return 0;
}

/*
gcatcg
4
acc
atc
cat
gcg

acdefg
3
acd
cd
fg

abc
3
abc
bc
c
*/
