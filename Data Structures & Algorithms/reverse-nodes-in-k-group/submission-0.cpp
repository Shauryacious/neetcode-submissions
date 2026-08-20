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
PATTERN: Surgical Pointer Manipulation
Time Complexity: O(N) | Space Complexity: O(1) auxiliary
=======================================================================================
Explanation:
- We use a `dummy` node to anchor the beginning of the list, as the actual head will change.
- `prev_group_tail` keeps track of the end of the last reversed chunk so we can attach 
  the newly reversed chunk to it.
- We probe `k` nodes ahead to find `kth`. If `kth` is NULL, we break and leave the rest.
- The Reversal: We initialize `prev = next_group_head` so the tail of our reversed 
  chunk automatically links forward. We reverse exactly `k` nodes.
- Finally, we connect the `prev_group_tail` to our new `kth` head, and shift our 
  trackers forward for the next iteration.
=======================================================================================
*/

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;
        
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        
        // This pointer will always sit exactly one node before the group we are about to reverse
        ListNode* prev_group_tail = dummy;
        
        while (true) {
            
            // 1. Probe exactly k steps ahead
            ListNode* kth = prev_group_tail;
            for (int i = 0; i < k && kth != NULL; i++) {
                kth = kth->next;
            }
            
            // If we don't have a full k-group left, the problem says to leave it as is
            if (kth == NULL) {
                break;
            }
            
            // 2. Setup the boundaries for reversal
            ListNode* next_group_head = kth->next;
            ListNode* curr = prev_group_tail->next; // The current head of the group
            
            // TRICK: Initialize prev to the start of the next group! 
            // This instantly wires our reversed tail to the rest of the list.
            ListNode* prev = next_group_head; 
            
            // 3. Standard Linked List Reversal (exactly k times)
            for (int i = 0; i < k; i++) {
                ListNode* nxt = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nxt;
            }
            
            // 4. Rewire the previous group to point to the newly reversed head
            ListNode* temp = prev_group_tail->next; // The original head is now the tail
            prev_group_tail->next = kth;            // kth is the new head of this reversed chunk
            
            // 5. Shift the boundary pointer forward for the next chunk
            prev_group_tail = temp; 
        }
        
        return dummy->next;
    }
};