class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& a) {
        int n = a.size();
        int t = 0; //target

        sort(a.begin(), a.end());

        vector<vector<int>> ans;
        for(int i = 0; i < n; i++) { // Use while logic for skipping duplicates
            int curr = a[i];

            int newt = t - a[i]; //new target
            int l = i + 1, h = n - 1;
            while(l < h) {
                int sum = a[l] + a[h];
                if(sum == newt) {
                    ans.push_back({a[i], a[l], a[h]});
                    int left = a[l];
                    int right = a[h];
                    while(l < h && a[l] == left) { // Skip duplicates for l
                        l++;
                    }
                    while(l < h && a[h] == right) { // Skip duplicates for h
                        h--;
                    }
                }
                else if(sum > newt) { 
                    h--;
                }
                else { //sum < new target
                    l++;
                }
            }

            while(i < n && a[i] == curr) { // Skip duplicates for i
                i++;
            }
            i--;
        }
        return ans;
    }
};