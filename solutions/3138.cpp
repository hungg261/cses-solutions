#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 2e5;
const int BASE = 31, MOD = 1e9 + 9;
int n, hashes[MAXN + 5], rev_hashes[MAXN + 5], powhash[MAXN + 5];
string s, rev_s;

void compute(){
    powhash[0] = 1 % MOD;
    for(int i = 1; i <= n; ++i){
        powhash[i] = powhash[i - 1] * BASE % MOD;
        hashes[i] = (hashes[i - 1] * BASE + s[i] - 'a' + 1) % MOD;
        rev_hashes[i] = (rev_hashes[i - 1] * BASE + rev_s[i] - 'a' + 1) % MOD;
    }
}

int getHash(int l, int r){
    return ((hashes[r] - hashes[l - 1] * powhash[r - l + 1]) % MOD + MOD) % MOD;
}

int getRevHash(int l, int r){
    return ((rev_hashes[r] - rev_hashes[l - 1] * powhash[r - l + 1]) % MOD + MOD) % MOD;
}

bool check_palindrome(int l, int r){
    return getHash(l, r) == getRevHash(n - r + 1, n - l + 1);
}

int cnp_chan(int center){
    int l = 1, r = min(center - 1, n - center + 1), res = 0;
    while(l <= r){
        int mid = (l + r) / 2;
        if(check_palindrome(center - mid, center + mid - 1)){
            res = mid * 2;
            l = mid + 1;
        }
        else r = mid - 1;
    }

    return res;
}

int cnp_le(int center){
    int l = 1, r = min(center, n - center + 1), res = 1;
    while(l <= r){
        int mid = (l + r) / 2;
        if(check_palindrome(center - mid + 1, center + mid - 1)){
            res = mid * 2 - 1;
            l = mid + 1;
        }
        else r = mid - 1;
    }

    return res;
}

struct Palindrome{
    int id, halflength;
    bool isOpen, isOddLength;
};

vector<Palindrome> palindromes[MAXN + 5];

struct compare{
    bool operator() (int a, int b){
        return
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> s;

    rev_s = s;
    reverse(begin(rev_s), end(rev_s));

    n = s.size();
    s = ' ' + s; rev_s = ' ' + rev_s;

    compute();
    for(int i = 1; i <= n; ++i){
        int length = max(cnp_chan(i), cnp_le(i));
        int L = i - length / 2, R = L + length - 1;

        palindromes[L].push_back({i, (length + 1) / 2, true, length & 1});
        palindromes[R].push_back({i, (length + 1) / 2, false, length & 1});
    }

    set<int> candidates;
    for(int i = 1; i <= n; ++i){

    }

    return 0;
}
