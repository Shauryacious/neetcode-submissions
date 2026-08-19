// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>

using namespace std;

#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define all(x) (x).begin(), (x).end()
#define INF 1e9

/*
=======================================================================================
PATTERN: Two Pointers (Opposite Ends)
Time Complexity: O(N) strictly one pass | Space Complexity: O(1) auxiliary
=======================================================================================
Explanation:
- We initialize a `left` pointer at the start and a `right` pointer at the end.
- We check the sum of the elements at these two pointers.
- If the sum is too large, we decrement `right` to point to a smaller number.
- If the sum is too small, we increment `left` to point to a larger number.
- We repeat this "squeezing" process until we find the exact target.
=======================================================================================
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            
            if (sum == target) {
                // The problem asks for 1-indexed output!
                return {left + 1, right + 1};
            } 
            else if (sum > target) {
                // Too heavy, decrease the right side
                right--;
            } 
            else {
                // Too light, increase the left side
                left++;
            }
        }
        
        return {}; // This will never be hit due to problem constraints
    }
};