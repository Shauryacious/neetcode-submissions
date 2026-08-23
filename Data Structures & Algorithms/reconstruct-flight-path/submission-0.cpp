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
#define vvpii vector<vpii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define pll pair<ll, ll>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define all(x) (x).begin(), (x).end()
#define INF 1e18
#define ff first
#define ss second

/*
=======================================================================================
PATTERN: Hierholzer's Algorithm (Eulerian Path / "Edge Destruction DFS")
Time Complexity: O(E log E) | Space Complexity: O(V + E) 
Where E is the number of tickets (edges) and V is the number of airports (vertices).
=======================================================================================
THE BIG MISCONCEPTION: THIS IS NOT A TOPOLOGICAL SORT!

1. Vertices vs. Edges (The Core Difference): 
   - Topological Sort is about processing every NODE exactly once based on dependencies. 
     If there is a cycle, Topo Sort breaks completely.
   - Hierholzer's Algorithm is about traversing every EDGE exactly once. You are 
     expected to visit the same node multiple times. Eulerian paths actually require 
     cycles to function!
     
2. Cycle Unraveling (Why Post-Order DFS works):
   - If you fly into a loop (JFK -> A -> B -> C -> A), a standard graph DFS gets trapped.
   - Hierholzer's Post-Order DFS flies into the cycle, exhausts all its tickets, and 
     gets "stuck" at 'A'. It then writes 'A' down and steps backward. It acts like 
     untangling a ball of yarn: you pull the string until you hit a knot, snip the knot 
     off the graph, tuck it into your answer array, and keep pulling.
     
3. The Priority Queue (The LeetCode Quirk):
   - The PQ has nothing to do with Eulerian graph theory. It strictly exists to satisfy 
     the arbitrary "smallest lexical order" constraint. If the problem accepted ANY valid 
     itinerary, a standard `vector<string>` popping from the back would run in O(E) time.

=======================================================================================
PRACTICE HIERHOLZER'S ALGORITHM (Eulerian Circuits & Paths):

1. LC 753: Cracking the Safe 
   (https://leetcode.com/problems/cracking-the-safe/)
   - The ultimate Eulerian Circuit problem mapped to De Bruijn sequences.

2. LC 2097: Valid Arrangement of Pairs 
   (https://leetcode.com/problems/valid-arrangement-of-pairs/)
   - Almost identical mechanics to Reconstruct Itinerary, but you have to manually 
     calculate in/out degrees to find the correct starting node.

3. CSES: Mail Delivery 
   (https://cses.fi/problemset/task/1691)
   - The pure, raw Eulerian Circuit template problem for CP.

4. CSES: Teleporters Path 
   (https://cses.fi/problemset/task/1693)
   - The pure, raw Eulerian Path template problem for CP.
=======================================================================================
*/

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        
        // Adjacency list: Airport -> Min-Heap of destinations
        // Guarantees we always greedily attempt the lexicographically smallest path first
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj;
        
        // Build the graph
        for (auto& t : tickets) {
            string u = t[0], v = t[1];
            adj[u].push(v);
        }
        
        vector<string> ans;
        
        // Post-Order Edge Destruction DFS
        auto dfs = [&](string u, auto&& dfs) -> void {
            
            // As long as there are flights leaving this airport...
            while (!adj[u].empty()) {
                // Grab the lexicographically smallest destination
                string v = adj[u].top();
                // Destroy the ticket (remove the edge permanently)
                adj[u].pop(); 
                
                // Fly to that destination
                dfs(v, dfs);
            }
            
            // We are completely stuck! No more outgoing flights from 'u'.
            // Add it to our reverse itinerary.
            ans.pb(u);
        };
        
        // The problem strictly dictates we must start at JFK
        dfs("JFK", dfs);
        
        // The post-order traversal untangled the path exactly backwards. Reverse it!
        reverse(all(ans));
        
        return ans;
    }
};