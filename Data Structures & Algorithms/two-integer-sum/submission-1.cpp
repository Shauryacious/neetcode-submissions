// // Approach 1 -> O(N^2)
// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         int n = nums.size();
//         for(int i=0; i<n-1; i++){
//             for(int j=i+1; j<n; j++){
//                 if(nums[i] + nums[j] == target)
//                 return {i,j};
//             }
//         }
//         return {};
//     }
// };


// Approach 2 -> O(NlogN + NlogN) Sort then Binary Search
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int, int>> numIdx;
        for (int i = 0; i < nums.size(); i++) {
            numIdx.push_back({nums[i], i});
        }
        
        sort(numIdx.begin(), numIdx.end());
        
        for (int i = 0; i < numIdx.size(); i++) {
            int diff = target - numIdx[i].first;
            int l = i + 1, r = numIdx.size() - 1;
            
            while (l <= r) {
                int m = l + (r - l) / 2;
                if (numIdx[m].first == diff) {
                    return {min(numIdx[i].second, numIdx[m].second), max(numIdx[i].second, numIdx[m].second)};
                } else if (numIdx[m].first < diff) {
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
        }
        return {};
    }
};


// Approach 3 -> O(NlogN + N) Sort then Two pointer most optimal approach better than binary search
// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         int n = nums.size();
//         vector<pair<int, int>> v(n); 
//         for(int i=0; i<n; i++){
//             v[i] = make_pair(nums[i], i);
//         }

//         sort(v.begin(), v.end());
//         int i=0, j=n-1;

//         while(i < j){
//             if(v[i].first + v[j].first == target){
//                 return {v[i].second, v[j].second};
//             }
//             else if(v[i].first + v[j].first > target){
//                 j--;
//             }
//             else{
//                 i++;
//             }   
//         }

//         return {};
//     }
// };