#define pb push_back

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();

        map<vector<int>, vector<string>> mp;

        for(int i=0; i<n; i++){
            vector<int> f(26, 0);
            for(auto x : strs[i]){
                f[x - 'a']++;
            }

            mp[f].pb(strs[i]);
        }


        vector<vector<string>> ans;

        for(auto [f, v] : mp){
            ans.pb(v);
        }

        return ans;
    }
};