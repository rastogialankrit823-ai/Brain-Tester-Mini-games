#pragma once
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <deque>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

// ============================================================================
// SOLVER CLASS
// ============================================================================
class Solver {
public:
    // 1. KEY HUNTER (BFS + Bitmasking)
    int solveKeyHunter(const vector<string>& grid, int K) {
        int keys=0,si=0,sj=0;
        int n=grid.size()-1,m=grid[0].size()-1;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++){
                if(grid[i][j]>='a'&&grid[i][j]<='f')keys++;
                else if(grid[i][j]=='@'){si=i;sj=j;}
            }
        map<tuple<int,int,string>,int> v;
        deque<tuple<int,int,string,int>> q;
        q.push_back({si,sj,"",0});
        int formula[][2]={{0,1},{0,-1},{1,0},{-1,0}};
        while(!q.empty()){
            auto [i,j,ke,st]=q.front();q.pop_front();
            auto key=make_tuple(i,j,ke);
            if(v.count(key))continue;
            v[key]=0;
            char curr=grid[i][j];
            if(curr=='#')continue;
            else if(curr>='a'&&curr<='f'&&ke.find(curr)==string::npos){
                ke+=curr;
                sort(ke.begin(),ke.end());
                if((int)ke.size()==K)return st;
            }
            else if(curr>='A'&&curr<='F'&&ke.find(tolower(curr))==string::npos)continue;
            for(auto&k:formula){
                if((i+k[0])>=0&&(i+k[0])<=n&&(j+k[1])>=0&&(j+k[1])<=m)
                    q.push_back({i+k[0],j+k[1],ke,st+1});
            }
        }
        return -1;
    }

    // 2. DUNGEON SURVIVAL (2D DP)
    int solveDungeonSurvival(const vector<vector<int>>& dn) {
        int n=dn.size(),m=dn[0].size();
        vector<vector<int>> work(n+1,vector<int>(m+1,0));
        int nn=n-1,mm=m-1;
        for(int i=nn;i>=0;i--){
            int b=dn[i][mm]+work[i+1][mm];
            if(b<0)work[i][mm]=b;
        }
        for(int i=m-1;i>=0;i--){
            int b=dn[nn][i]+work[nn][i+1];
            if(b<0)work[nn][i]=b;
        }
        for(int i=nn-1;i>=0;i--)
            for(int j=mm-1;j>=0;j--){
                int b=max(work[i+1][j],work[i][j+1])+dn[i][j];
                if(b<0)work[i][j]=b;
            }
        return abs(work[0][0]-1);
    }

    // 3. DUAL ROBOT CHALLENGE (3D DP)
    int solveDualRobot(const vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        vector<vector<vector<int>>> dp(m,vector<vector<int>>(n,vector<int>(n,0)));
        for(int row=m-1;row>=0;row--)
            for(int col1=0;col1<n;col1++)
                for(int col2=0;col2<n;col2++){
                    int result=0;
                    result+=grid[row][col1];
                    if(col1!=col2)result+=grid[row][col2];
                    if(row!=m-1){
                        int best=0;
                        for(int nc1:{col1,col1+1,col1-1})
                            for(int nc2:{col2,col2+1,col2-1})
                                if(nc1>=0&&nc1<n&&nc2>=0&&nc2<n)
                                    best=max(best,dp[row+1][nc1][nc2]);
                        result+=best;
                    }
                    dp[row][col1][col2]=result;
                }
        return dp[0][0][n-1];
    }

    // 4. CHERRY EXPEDITION (DP with time steps)
    int solveCherryExpedition(const vector<vector<int>>& grid) {
        int N=grid.size();
        vector<vector<int>> dp(N,vector<int>(N,INT_MIN));
        dp[0][0]=grid[0][0];
        for(int t=1;t<2*N-1;t++){
            vector<vector<int>> dp2(N,vector<int>(N,INT_MIN));
            for(int i=max(0,t-(N-1));i<=min(N-1,t);i++)
                for(int j=max(0,t-(N-1));j<=min(N-1,t);j++){
                    if(grid[i][t-i]==-1||grid[j][t-j]==-1)continue;
                    int val=grid[i][t-i];
                    if(i!=j)val+=grid[j][t-j];
                    int best=INT_MIN;
                    for(int pi:{i-1,i})for(int pj:{j-1,j})
                        if(pi>=0&&pj>=0&&dp[pi][pj]!=INT_MIN)
                            best=max(best,dp[pi][pj]+val);
                    if(best!=INT_MIN)dp2[i][j]=best;
                }
            dp=dp2;
        }
        return max(0,dp[N-1][N-1]);
    }

    // 5. PERMUTATION PUZZLE (Greedy Chessboard Transform)
    int solveMovesToChessboard(const vector<vector<int>>& board) {
        int n=board.size();
        auto fn=[&](vector<int>& vals)->int{
            int total=0,odd=0;
            for(int i=0;i<(int)vals.size();i++){
                if(vals[0]==vals[i]){
                    total++;
                    if(i&1)odd++;
                }
                else if((vals[0]^vals[i])!=((1<<n)-1))return INT_MAX;
            }
            int ans=INT_MAX;
            if((int)vals.size()<=2*total&&2*total<=(int)vals.size()+1)ans=odd;
            if((int)vals.size()-1<=2*total&&2*total<=(int)vals.size()&&ans>total-odd)ans=total-odd;
            return ans;
        };
        vector<int> rows(n,0),cols(n,0);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(board[i][j]){
                    rows[i]^=1<<j;
                    cols[j]^=1<<i;
                }
        int ans=fn(rows)+fn(cols);
        return ans<INT_MAX?ans:-1;
    }

    // 6. SUDOKU MASTER (Backtracking with bitmasks)
    void solveSudoku(vector<vector<int>>& board) {
        int subm[3][3]={};
        int row[9]={},col[9]={};
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                if(board[i][j]!=0){
                    row[i]^=1<<board[i][j];
                    col[j]^=1<<board[i][j];
                    subm[i/3][j/3]^=1<<board[i][j];
                }
        bool found=false;
        work(board,row,col,subm,0,0,found);
    }
private:
    void work(vector<vector<int>>& board,int row[],int col[],int subm[][3],int i,int j,bool&found) {
        if(i==9&&j==0){found=true;return;}
        if(board[i][j]!=0){
            if(j==8)work(board,row,col,subm,i+1,0,found);
            else work(board,row,col,subm,i,j+1,found);
            return;
        }
        for(int m=1;m<=9;m++){
            if((row[i]&(1<<m))==0&&(col[j]&(1<<m))==0&&(subm[i/3][j/3]&(1<<m))==0){
                row[i]^=1<<m;
                col[j]^=1<<m;
                subm[i/3][j/3]^=1<<m;
                board[i][j]=m;
                if(j==8)work(board,row,col,subm,i+1,0,found);
                else work(board,row,col,subm,i,j+1,found);
                if(found)return;
                row[i]^=1<<m;
                col[j]^=1<<m;
                subm[i/3][j/3]^=1<<m;
                board[i][j]=0;
            }
        }
    }
};
