class Solution {
public:
    bool hasDuplicate(vector<int>& a) {
        int n = a.size();
        unordered_map<int, int> mp;
        for(auto x : a){
            mp[x]++;
            if(mp[x] > 1) return true;
        }

        return false;

    }
};