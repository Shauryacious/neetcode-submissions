class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        int n = tokens.size();
        stack<int> st;
        for(int i=0; i<n; i++){
            if(tokens[i] == "+"){
                int a = st.top();
                st.pop();

                int b = st.top();
                st.pop();

                int res = a + b;
                st.push(res);
            }
            else if(tokens[i] == "-"){
                int a = st.top();
                st.pop();

                int b = st.top();
                st.pop();

                int res = b - a;
                st.push(res);
            }
            else if(tokens[i] == "*"){
                int a = st.top();
                st.pop();

                int b = st.top();
                st.pop();

                int res = a * b;
                st.push(res);
            }
            else if(tokens[i] == "/"){
                int a = st.top();
                st.pop();

                int b = st.top();
                st.pop();

                int res = b / a;
                st.push(res);
            }
            else{
                st.push(stoi(tokens[i]));
            }
        }

        return st.top();
    }
};