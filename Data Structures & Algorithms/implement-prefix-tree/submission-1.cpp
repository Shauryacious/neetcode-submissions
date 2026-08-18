class TrieNode {
public:
    bool isSpecial;
    TrieNode* children[26];
    TrieNode() {
        isSpecial = false;
        for(int i=0; i<26; i++){
            children[i] = NULL;
        }
    }
};

class PrefixTree {
public:
    TrieNode* root;
    PrefixTree() {
        root = new TrieNode();
    }

    void insert(string s){
        TrieNode* curr = root;
        for(char ch : s){
            int idx = ch - 'a';
            if(curr->children[idx] == NULL){
                curr->children[idx] = new TrieNode();
                curr = curr->children[idx];
            }
            else{
                curr = curr->children[idx];
            }
        }
        curr->isSpecial = true;
    }

    bool search(string s){
        TrieNode* curr = root;
        for(char ch : s){
            int idx = ch - 'a';
            if(curr->children[idx] == NULL){ // if the character is not present
                return false;
            }
            curr = curr->children[idx];
        }
        return curr->isSpecial;
    }

    bool startsWith(string s){
        TrieNode* curr = root;
        for(char ch : s){
            int idx = ch - 'a';
            if(curr->children[idx] == NULL){ // if the character is not present
                return false;
            }
            curr = curr->children[idx];
        }
        // after the loop, we have reached the end of the string
        // so, we can return true because the string is present
        // as a prefix of some other string in the trie
        return true;
    }
};