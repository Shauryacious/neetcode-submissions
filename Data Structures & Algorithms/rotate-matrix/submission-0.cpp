class Solution {
public:
    void rotate(vector<vector<int>>& mat) {
       int n = mat.size();

       //TRANSPOSE
       for(int i=0; i<n; i++){
           for(int j=0; j<n; j++){
               if(j < i){ //swap once only
                    swap(mat[i][j], mat[j][i]);
               }
           }
       } 

        // Reverse each row
        for(int i=0; i<n; i++){
            reverse(mat[i].begin(), mat[i].end());
        }
    }
};