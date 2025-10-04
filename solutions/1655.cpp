#include<bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    arr[0] = 0;
    for(int i = 1; i <= n; ++i){
        int cur; cin >> cur;
        arr[i] = arr[i - 1] ^ cur;
    }

    unordered_set<int> s;
    int ans = 0, mask = 0;
    for(int bit = 30; bit >= 0; --bit){
        mask |= (1 << bit);

        for(int ele: arr){
            s.insert(ele & mask);
        }

        int cur = ans | (1 << bit);
        for(int pref: s){
            if(s.count(pref ^ cur)){
                ans = cur;
                break;
            }
        }
        s.clear();
    }

    cout << ans << '\n';

    return 0;
}
