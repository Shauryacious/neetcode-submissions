class Solution {
public:
    vector<int> productExceptSelf(vector<int>& a) {
        int n = a.size();

        //ans will not be counted in the most optimised approach for SC calc
        vector<int> ans(n, 0);
        ans[0] = a[0];

        // nums = [1,2,3,4]
        // ans  = [1,2,6,24]
        for(int i=1; i<n; i++){
            ans[i] = ans[i-1] * a[i];
        }

        // for(int i=0; i<n; i++){
        //     cout<<ans[i]<<" ";
        // }
        // cout<<endl;

        int right = 1;

        for(int i=n-1; i>0; i--){
            ans[i] = ans[i-1] * right;
            right *= a[i];
        }

        ans[0] = right;

        return ans;
    }
};