//
// Created by ralph on 4/2/20.
//

#ifndef DATASTRUCTURE_TEST_H
#define DATASTRUCTURE_TEST_H

#include <vector>
using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        vector<vector<int>> tmp(board);
        size_t rows = tmp.size();
        size_t cols = tmp[0].size();
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j){
                board[i][j] = countAdjacentAlive(tmp, rows, cols, i, j);
            }
        }
    }

private:

    int countAdjacentAlive(vector<vector<int>>& board, size_t rows, size_t cols, int m, int n){
        int nCount = 0;

        if((n - 1) >= 0 && board[m][n-1]) ++nCount;
        if((n + 1) < cols && board[m][n+1]) ++nCount;

        if((m - 1) >= 0){
            if((n - 1) >= 0 && board[m-1][n-1]) ++nCount;
            if(board[m-1][n]) ++nCount;
            if((n + 1) < cols && board[m-1][n+1]) ++nCount;
        }

        if((m + 1) < rows){
            if((n - 1) >= 0 && board[m+1][n-1]) ++nCount;
            if(board[m+1][n]) ++nCount;
            if((n + 1) < cols && board[m+1][n+1]) ++nCount;
        }
        return nCount;
    }
};

#endif //DATASTRUCTURE_TEST_H
