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
APPROACH 1: Top-Down Dynamic Programming (Pair-State Tracking)
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
Intuition:
- We want to build a contiguous sequence. The easiest way to model this recursively 
  is to ask: "If I strictly start my subarray at index `i`, what are the best and 
  worst products I can form going forward?"
- We track TWO states per index because a heavily negative product (the "worst" product) 
  can suddenly become the "best" product if multiplied by another negative number.

Concept & State Definition:
- State: `f(i)` -> returns a `pair<ll, ll>` where:
  `first`  = Maximum product of a contiguous subarray STARTING strictly at index `i`.
  `second` = Minimum product of a contiguous subarray STARTING strictly at index `i`.

Base Case:
- If `i == n`, we have reached the end. Return `{1, 1}` (multiplicative identity).

Transition:
- Get `nxt = f(i + 1)`
- Candidates for contiguous subarray starting at index `i`:
  1. `c1 = a[i]` (Start fresh and end at i)
  2. `c2 = a[i] * nxt.first`  (Extend using maximum product starting at i+1)
  3. `c3 = a[i] * nxt.second` (Extend using minimum product starting at i+1)
- Return `{max(c1, c2, c3), min(c1, c2, c3)}`.
- Iterate through the DP table at the end to find the global maximum.
=======================================================================================
*/
class Solution {
public:
    int maxProduct(vector<int>& a) {
        int n = a.size();

        // dp[i] stores {max_prod_starting_at_i, min_prod_starting_at_i}
        vector<pair<ll, ll>> dp(n + 5, {-1e18, -1e18});

        auto f = [&](int i, auto && f) -> pair<ll, ll> {
            if (i == n) return {1, 1};
            if (dp[i].first != -1e18) return dp[i];

            pair<ll, ll> nxt = f(i + 1, f);

            ll c1 = (ll)a[i];
            ll c2 = (ll)a[i] * nxt.first;
            ll c3 = (ll)a[i] * nxt.second;

            ll max_prod = max({c1, c2, c3});
            ll min_prod = min({c1, c2, c3});

            return dp[i] = {max_prod, min_prod};
        };

        f(0, f); // Trigger recursion

        ll ans = -1e18;
        for (int i = 0; i < n; i++) {
            ans = max(ans, dp[i].first);
        }

        return (int)ans;
    }
};

/*
=======================================================================================
APPROACH 2: Bottom-Up DP / Kadane's Variant (State Space Compression)
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
Intuition:
- Looking at Approach 1, notice that index `i` ONLY ever asks for the values 
  calculated at `i + 1` (or in a bottom-up view, `i` asks for `i - 1`).
- We do not need an array of size O(N). We can compress the state into two running 
  variables: `cur_max` and `cur_min`.

The Transition Leap:
- As we iterate left to right, we ask: "What is the max/min subarray product strictly 
  ending at `i`?"
- We calculate the three choices (start fresh, extend max, extend min).
- We MUST save `cur_max` into a temporary variable before updating it, because 
  calculating the new `cur_min` requires the un-updated `cur_max` from the previous step!
=======================================================================================
*/
class Solution2 {
public:
    int maxProduct(vector<int>& a) {
        int n = a.size();
        
        // Initialize with the first element
        ll cur_max = a[0];
        ll cur_min = a[0];
        ll global_max = a[0];

        for (int i = 1; i < n; i++) {
            ll val = a[i];

            // Store previous max because we overwrite cur_max but need it for cur_min
            ll prev_max = cur_max;

            cur_max = max({val, val * prev_max, val * cur_min});
            cur_min = min({val, val * prev_max, val * cur_min});

            global_max = max(global_max, cur_max);
        }

        return (int)global_max;
    }
};

/*
=======================================================================================
APPROACH 3 (Expanded): Prefix and Suffix Arrays (3-Pass Method)
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
WHY DOES THIS MATHEMATICALLY WORK? 

To understand why we only need to check prefixes and suffixes, we have to look at 
how zeroes and negative numbers affect multiplication.

1. The "Zero" Walls:
   A zero destroys a product. Therefore, any optimal subarray will NEVER contain a zero 
   (unless the array is literally just [0, -1], in which case 0 is the max). 
   Zeroes act as "walls" that chop the array into independent, zero-free blocks.
   By resetting our running product to 1 whenever we hit a 0, we effectively evaluate 
   each block completely independently.

2. Inside a Zero-Free Block:
   In a block with no zeroes, there are exactly two cases:
   
   CASE A: The block has an EVEN number of negative numbers.
   Negative × Negative = Positive. If there are an even number of negatives, the 
   product of the ENTIRE block is positive. 
   -> The maximum product is simply the product of the whole block. Both our prefix 
      and suffix passes will naturally calculate this full-block product.

   CASE B: The block has an ODD number of negative numbers.
   The product of the entire block will be negative. To make it positive and maximal, 
   we MUST remove exactly one negative number to make the count even. 
   But because the subarray must be contiguous, we can't just pluck one out of the 
   middle. We have only two options:
     - Remove the FIRST negative number (and everything to its left). What remains 
       is a SUFFIX of the block.
     - Remove the LAST negative number (and everything to its right). What remains 
       is a PREFIX of the block.

THE GOLDEN PROOF:
Because the optimal answer in any zero-free block is ALWAYS either the entire block 
itself, a prefix of the block, or a suffix of the block, we literally do not need 
to check any middle subarrays! Checking all prefixes and all suffixes guarantees 
we evaluate the absolute maximum possible product.
=======================================================================================
*/
class Solution3 {
public:
    int maxProduct(vector<int>& a) {
        int n = a.size();
        
        // Arrays to explicitly store the products at every index
        vll prefix(n);
        vll suffix(n);
        
        // ---------------------------------------------------------
        // PASS 1: Build the Prefix Array (Left to Right)
        // ---------------------------------------------------------
        ll current_pref = 1;
        for (int i = 0; i < n; i++) {
            // If the running product is 0, the chain is dead. Reset to 1.
            if (current_pref == 0) current_pref = 1;
            
            current_pref *= a[i];
            prefix[i] = current_pref;
        }

        // ---------------------------------------------------------
        // PASS 2: Build the Suffix Array (Right to Left)
        // ---------------------------------------------------------
        ll current_suff = 1;
        for (int i = n - 1; i >= 0; i--) {
            // If the running product is 0, the chain is dead. Reset to 1.
            if (current_suff == 0) current_suff = 1;
            
            current_suff *= a[i];
            suffix[i] = current_suff;
        }

        // ---------------------------------------------------------
        // PASS 3: Scan both arrays for the Global Maximum
        // ---------------------------------------------------------
        ll max_prod = -1e18;
        for (int i = 0; i < n; i++) {
            max_prod = max({max_prod, prefix[i], suffix[i]});
        }

        return (int)max_prod;
    }
};