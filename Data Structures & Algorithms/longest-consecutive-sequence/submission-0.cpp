class Solution {
public:
    int longestConsecutive(vector<int>& a) {
        unordered_set<int> st(a.begin(), a.end());

        int ans = 0;
        for(auto x : a){
            //till the smaller exist move to smaller
            while(st.find(x-1) != st.end()){
                x--;
            }

            //till bigger exist count it and remove it
            int cnt = 1;
            while(st.find(x+1) != st.end()){
                cnt++;
                st.erase(x);
                x++;
            }

            ans = max(ans, cnt);
        }

        return ans;
    }
};