// //Wrong greedy -> 
// // height = [1,2,1]
// // Output
// // 1
// // Expected
// // 2

// class Solution {
// public:
//     int maxArea(vector<int>& a) {
//         int n = a.size();


//         //p1 = pole 1 -> choose highest one greedly
//         // we need max area
//         // max area = width(h1, h2) * min(h1, h2);
//         int p1 = max_element(a.begin(), a.end()) - a.begin();

//         int ans = 0;

//         for(int i=0; i<n; i++){
//             int area = abs(i-p1) * a[i];

//             ans = max(ans, area);
//         }

//         return ans;
//     }
// };


//Approach 2 : two pointer
class Solution {
public:
    int maxArea(vector<int>& a) {
        int n = a.size();
        
        int i = 0, j = n - 1;
        int ans = 0;

        // area = (j - i) * min(a[i], a[j]);
        // we want to maximize area
        // since we are start from the extreme end point 
        // so j-i will always decrease
        // so we need to maximize min(a[i], a[j])
        // if (a[i] < a[j]) -> move i++
        // else move j++;

        while(i < j) {
            // Calculate the current area and update max
            int area = (j - i) * min(a[i], a[j]);
            ans = max(ans, area);

            // Always move the pointer that points to the shorter line.
            // If they are equal, moving either is fine.
            if (a[i] < a[j]) {
                i++;
            } else {
                j--;
            }
        }

        return ans;
    }
};