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
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
*/

/*
=======================================================================================
PATTERN: Linked List Traversal / Math Simulation
Time Complexity: O(max(N, M)) | Space Complexity: O(max(N, M)) for the new list
=======================================================================================
Explanation:
- We use a `dummy` node to cleanly anchor the head of our newly constructed list.
- We loop as long as there is an active node in `l1`, an active node in `l2`, OR a 
  lingering `carry` that needs to be added as a final node.
- At each step, we extract the values safely (handling cases where one list is 
  shorter than the other by substituting 0).
- We append a new node with `sum % 10` and update the `carry` for the next loop.
=======================================================================================
*/

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        // Dummy head elegantly handles empty list edge cases
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;
        
        int carry = 0;
        
        // Keep going if either list has digits OR if we have a lingering carry
        while (l1 != NULL || l2 != NULL || carry > 0) {
            int sum = carry;
            
            if (l1 != NULL) {
                sum += l1->val;
                l1 = l1->next;
            }
            
            if (l2 != NULL) {
                sum += l2->val;
                l2 = l2->next;
            }
            
            // The new node gets the ones place of the sum
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
            
            // Extract the tens place to carry over to the next iteration
            carry = sum / 10;
        }
        
        return dummy->next;
    }
};