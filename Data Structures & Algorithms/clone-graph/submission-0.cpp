// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<unordered_map>

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
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

/*
=======================================================================================
PATTERN: Graph DFS (Void Return Type) + Hash Map
Time Complexity: O(V + E) | Space Complexity: O(V) for Map and Recursion Stack
=======================================================================================
Explanation:
- We manually clone the starting node and put it in the map BEFORE starting DFS.
- The `void dfs` is now only responsible for building the `neighbors` lists.
- We loop through all original neighbors `v`. If `v` isn't cloned yet, we clone it 
  and recursively launch `dfs(v)`.
- Finally, we establish the edge strictly using the cloned pointers stored in `mp`.
=======================================================================================
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        // Base case: Empty graph
        if (node == NULL) return NULL;
        
        unordered_map<Node*, Node*> mp;
        
        // 1. Manually clone the root node BEFORE starting the DFS
        mp[node] = new Node(node->val);
        
        // 2. Void DFS: Its only job is to populate the 'neighbors' array of the clones
        auto dfs = [&](Node* u, auto&& dfs) -> void {
            
            // Look at every original neighbor 'v' of 'u'
            for (Node* v : u->neighbors) {
                
                // If 'v' hasn't been cloned yet, clone it and explore it!
                if (mp.find(v) == mp.end()) {
                    mp[v] = new Node(v->val);
                    dfs(v, dfs);
                }
                
                // At this point, we are 100% sure the clone of 'v' exists in the map.
                // Link the clone of 'u' to the clone of 'v'.
                mp[u]->neighbors.pb(mp[v]);
            }
        };
        
        // Launch the void DFS
        dfs(node, dfs);
        
        // The fully built graph's entry point is sitting right here in the map
        return mp[node];
    }
};