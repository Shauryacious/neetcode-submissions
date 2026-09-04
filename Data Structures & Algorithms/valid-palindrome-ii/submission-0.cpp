// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<stack>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
#include<chrono>
#include<random>
#include<string>
#include<functional>
#include<iomanip>
#include<limits>
#include<array>
#include<utility>
#include<iterator>
#include<cstring>

using namespace std;

// Define Constants & Macros
#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e9 
#define nl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define py cout<<"YES"<<nl
#define pn cout<<"NO"<<nl
#define pm cout<<"-1"<<nl
#define all(x) (x).begin(), (x).end()

// Typedef
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<string> vs;
typedef vector<pll> vpll;

#define vvpll vector<vpll>

/*
=======================================================================================
PATTERN: Two Pointers with a Single Branch
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
EXPLANATION OF LOGIC:
1. Initialize `left` at the start and `right` at the end of the string.
2. Advance inwards while characters match.
3. If a mismatch is found at `s[left] != s[right]`:
   - We must use our 1 deletion here.
   - We check if skipping the left character makes a valid palindrome: `[left+1, right]`
   - We check if skipping the right character makes a valid palindrome: `[left, right-1]`
   - If either returns true, the overall string is valid.
4. The helper function `isPalindrome` simply runs a strict two-pointer check without 
   any skips allowed.
=======================================================================================
*/

class Solution {
private:
    // Helper function to check if a specific substring is a strict palindrome
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

public:
    bool validPalindrome(string s) {
        int left = 0;
        int right = sz(s) - 1;
        
        while (left < right) {
            if (s[left] == s[right]) {
                // Characters match, continue closing the window
                left++;
                right--;
            } 
            else {
                // Mismatch found! We must branch.
                // Branch 1: Try deleting the character at 'left'
                // Branch 2: Try deleting the character at 'right'
                return isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1);
            }
        }
        
        // If we made it to the center without any mismatches, it's already a perfect palindrome
        return true;
    }
};