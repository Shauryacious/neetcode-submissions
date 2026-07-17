#define pb push_back

class Solution {
public:
    vector<int> topKFrequent(vector<int>& a, int k) {
        int n = a.size();
        unordered_map<int, int> mp;

        for(auto x : a){
            mp[x]++;
        }

        vector<vector<int>> v(n);
        // at max the freq of any element can be n
        // so we store opposite
        // idx = frequency -> {vector of ele with that f}

        for(auto [ele, f] : mp){
            v[f-1].pb(ele);
        }

        vector<int> ans;

        for(int i=n-1; i>=0 && k != 0; i--){
            while(v[i].size() > 0 && k != 0){
                ans.pb(v[i].back());
                v[i].pop_back();
                k--;
            }
        }

        return ans;
    }
};