class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size();

        auto ok = [&](char ch) -> bool {
            if(('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ('0' <= ch && ch <= '9')) return true;

            return false;
        };

        string t = "";
        for(auto x : s){
            if(ok(x)){
                if('A' <= x && x <= 'Z'){
                    x = 'a' + (x - 'A');
                }

                t += x;
            }
        }

        cout<<t;


        int i = 0, j = t.size()-1;
        while(i < j){
            if(t[i] == t[j]){
                i++;
                j--;
            }
            else{
                return false;
            }
        }

        return true;
    }
};