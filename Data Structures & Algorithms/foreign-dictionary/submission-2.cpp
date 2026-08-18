class Solution {
  public:
    string foreignDictionary(vector<string>& words) {
        int n = words.size();
        
        // adj: Maps a character to a SET of characters that come after it.
        // We use a set to avoid adding duplicate edges, which would falsely inflate in-degrees!
        unordered_map<char, set<char>> adj;
        unordered_map<char, int> indegree;

        // 1. Initialize the graph: Every unique character needs a starting indegree of 0.
        // This is crucial because some characters might not have any edges (e.g., ["z", "z"]).
        for(auto word : words) {
            for(char c : word) {
                indegree[c] = 0; 
            }
        }

        // 2. Extract edges by comparing adjacent words ONLY
        for(int i = 0; i < n - 1; i++){
            string word1 = words[i];
            string word2 = words[i+1];
            int j = 0;
            
            // Skip the identical prefix
            while(j < min(word1.size(), word2.size()) && word1[j] == word2[j]) {
                j++;
            }

            // TRAP 1: The Prefix Rule. 
            // If word2 is entirely a prefix of word1, word1 MUST be shorter. 
            // If it's longer, the dictionary is invalid.
            if(j == word2.size() && word1.size() > word2.size()) {
                return "";
            }

            // If we found a difference, draw a directed edge!
            if(j < min(word1.size(), word2.size())) {
                char u = word1[j];
                char v = word2[j];
                
                // Prevent duplicate edges from inflating indegree
                if(adj[u].find(v) == adj[u].end()) {
                    adj[u].insert(v);
                    indegree[v]++;
                }
            }
        }

        // 3. Kahn's Algorithm (BFS)
        queue<char> q;
        for(auto p : indegree) {
            if(p.second == 0) {
                q.push(p.first); // Characters with no prerequisites go first
            }
        }

        string order = "";
        while(!q.empty()) {
            char u = q.front();
            q.pop();
            order += u;

            for(char v : adj[u]) {
                indegree[v]--;
                if(indegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // TRAP 2: Cycle Detection.
        // If we didn't process every unique character, a cycle locked the graph.
        if(order.size() == indegree.size()) {
            return order;
        } else {
            return ""; 
        }           
    }
};