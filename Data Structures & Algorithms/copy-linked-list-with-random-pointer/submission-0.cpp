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
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

/*
=======================================================================================
SOLUTION 1: Hash Map (Two-Pass)
Time Complexity: O(N) | Space Complexity: O(N) auxiliary for the hash map
=======================================================================================
Explanation:
- We use an `unordered_map` to map memory addresses of original nodes to cloned nodes.
- This acts as a bridge between the original list and our new deep copy.
- First pass: Create all nodes.
- Second pass: Wire up the `next` and `random` pointers using the map.
=======================================================================================
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return NULL;
        
        unordered_map<Node*, Node*> m;
        Node* curr = head;
        
        // Pass 1: Create all cloned nodes and store in map
        while (curr) {
            m[curr] = new Node(curr->val);
            curr = curr->next;
        }
        
        curr = head;
        
        // Pass 2: Assign next and random pointers
        while (curr) {
            m[curr]->next = m[curr->next];
            m[curr]->random = m[curr->random];
            curr = curr->next;
        }
        
        // Return the head of the cloned list
        return m[head];
    }
};



/*
=======================================================================================
SOLUTION 2: Weaved List / Interleaving
Time Complexity: O(N) | Space Complexity: O(1) auxiliary (perfect optimization)
=======================================================================================
Explanation:
- PHASE 1: Weave the original list and cloned list together. A -> A' -> B -> B'.
- PHASE 2: Assign random pointers. Since A' is A->next, and the target clone Z' is 
  Z->next, we can set `curr->next->random = curr->random->next`.
- PHASE 3: Unweave the lists. We extract the clones by jumping two steps at a time, 
  carefully restoring the original list's `next` pointers along the way.
=======================================================================================
*/

class Solution2 {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return NULL;
        
        // Phase 1: Weave the list (A -> A' -> B -> B')
        Node* curr = head;
        while (curr) {
            Node* clone = new Node(curr->val);
            clone->next = curr->next;
            curr->next = clone;
            curr = clone->next; // Move to the next original node
        }
        
        // Phase 2: Wire up the random pointers for the clones
        curr = head;
        while (curr) {
            if (curr->random) {
                // clone->random = original_target->clone
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next; // Jump to the next original node
        }
        
        // Phase 3: Unweave the lists to extract the deep copy
        curr = head;
        Node* dummy = new Node(-1);
        Node* clone_curr = dummy;
        
        while (curr) {
            // Extract the cloned node
            clone_curr->next = curr->next;
            clone_curr = clone_curr->next;
            
            // Restore the original list
            curr->next = curr->next->next;
            curr = curr->next;
        }
        
        return dummy->next;
    }
};