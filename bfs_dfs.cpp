#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>
using namespace std;

/*
## 8. BFS / DFS 与二维网格（8）

42. **LC 200 岛屿数量**｜Medium｜S｜网格 DFS/BFS
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。

示例 1：
输入：grid = [
  ['1','1','1','1','0'],
  ['1','1','0','1','0'],
  ['1','1','0','0','0'],
  ['0','0','0','0','0']
]
输出：1
*/
void dfs(vector<vector<char>>& grid,vector<vector<bool>>& visited,int i,int j)
{

    int m = grid.size();
    int n = grid[0].size();
    //超出边界
    if(i<0 || i>=m || j<0 || j>=n)
        return;
    
    if(grid[i][j]=='0' || visited[i][j]==true)
        return;
    
    visited[i][j]=true;
    dfs(grid,visited,i+1,j);
    dfs(grid,visited,i-1,j);
    dfs(grid,visited,i,j-1);
    dfs(grid,visited,i,j+1);
}
int numIslands(vector<vector<char>>& grid) {
    if(grid.empty())
        return 0;
    
    int m=grid.size();
    int n=grid[0].size();
    vector<vector<bool>> visited(m,vector<bool>(n,false));

    int result=0;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(grid[i][j]=='1'  && !visited[i][j])
            {
                result++;
                dfs(grid,visited,i,j);
            }
        }
    }
    return result;

}

/*
43. **LC 695 岛屿的最大面积**｜Medium｜S｜连通域统计
给你一个大小为 m x n 的二进制矩阵 grid 。

岛屿 是由一些相邻的 1 (代表土地) 构成的组合，
这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻。
你可以假设 grid 的四个边缘都被 0（代表水）包围着。

岛屿的面积是岛上值为 1 的单元格的数目。

计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。

输入：grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],
[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],
[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],
[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
输出：6
解释：答案不应该是 11 ，因为岛屿只能包含水平或垂直这四个方向上的 1 。
*/

int dfs_area(vector<vector<int>>& grid,
             vector<vector<bool>>& visited,
             int i, int j)
{
    int m = grid.size();
    int n = grid[0].size();

    if(i < 0 || i >= m || j < 0 || j >= n)
        return 0;

    if(grid[i][j] == 0 || visited[i][j])
        return 0;

    visited[i][j] = true;

    return 1
        + dfs_area(grid, visited, i + 1, j)
        + dfs_area(grid, visited, i - 1, j)
        + dfs_area(grid, visited, i, j + 1)
        + dfs_area(grid, visited, i, j - 1);
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    if(grid.empty())
        return 0;
    
    int m=grid.size();
    int n=grid[0].size();
    vector<vector<bool>> visited(m,vector<bool>(n,false));

    int result=0;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(grid[i][j] == 1 && !visited[i][j])
            {
                int area = dfs_area(grid, visited, i, j);
                result = max(result, area);
            }
        }
    }
    return result;

}

/*
44. **LC 994 腐烂的橘子**｜Medium｜S｜多源 BFS
在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：

值 0 代表空单元格；
值 1 代表新鲜橘子；
值 2 代表腐烂的橘子。
每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。

返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。

输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
输出：4
*/

int orangesRotting(vector<vector<int>>& grid) {
    if(grid.empty())
        return 0;
    
    int m=grid.size();
    int n=grid[0].size();
    queue<pair<int,int>> q;

    int fresh=0;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(grid[i][j]==2)
                q.push({i,j});
            if(grid[i][j]==1)
                fresh++;
        }
    }

    int directions[4][2]={
        {-1,0},
        {1,0},
        {0,-1},
        {0,1}
    }

    int minute=0;
    while(!q.empty() && fresh > 0)
    {
        int size=q.size();
        for(int k=0;k<size;++k)
        {
            auto [x,y]=q.front();
            q.pop();

            for(int d=0;d<4;++d)
            {
                int nx=x+directions[d][0];
                int ny=y+directions[d][1];

                if(nx < 0 || nx >= m ||
                    ny < 0 || ny >= n)
                    {
                        continue;
                    }
                
                if(grid[nx][ny]!=1)
                    continue;
                
                grid[nx][ny]=2;
                fresh--;

                q.push({nx,ny});
            }
        }
        minute++;
    }

    if(fresh>0)
        return -1;

    return minute;
}

/*
45. **LC 542 01 矩阵**｜Medium｜S｜多源 BFS
给定一个由 0 和 1 组成的矩阵 mat ，请输出一个大小相同的矩阵，
其中每一个格子是 mat 中对应位置元素到最近的 0 的距离。
两个相邻元素间的距离为 1 。

输入：mat = [[0,0,0],[0,1,0],[0,0,0]]
输出：[[0,0,0],[0,1,0],[0,0,0]]
*/
int bfs_mat(vector<vector<int>>& mat,int i,int j)
{
    int m=mat.size();
    int n=mat[0].size();
    queue<pair<int,int>> q;
    vector<vector<bool>> visited(m,vector<bool>(n,false));
    q.push({i,j});
    int directions[4][2]={
        {-1,0},
        {1,0},
        {0,-1},
        {0,1}
    };
    int count=0;
    while(!q.empty())
    {
        int size=q.size();
        bool flag=false;
        for(int k=0;k<size;++k)
        {
            auto [x,y]=q.front();
            q.pop();

            for(int d=0;d<4;++d)
            {
                int nx=x+directions[d][0];
                int ny=y+directions[d][1];
                if(nx<0 || nx>=m || ny<0 || ny>=n)
                    continue;

                if(mat[nx][ny]==0)
                {
                    flag=true;
                    break;
                }
                if(visited[nx][ny])
                    continue;
                visited[nx][ny]=true;
                q.push({nx,ny});
            }
            if(flag)
                break;
        }
        count++;
        if(flag)
            return count;
    }
    return count;
}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    if(mat.empty())
        return {};
    int m=mat.size();
    int n=mat[0].size();
    vector<vector<int>> result(m,vector<int>(n,0));

    //找出所有1的位置
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(mat[i][j]==1)
            {
                int dis=bfs_mat(mat,i,j);
                result[i][j]=dis;
            }   
        }
    }
    return result;
}

//简化方案
vector<vector<int>> updateMatrix_optim(vector<vector<int>>& mat) {
    if(mat.empty())
        return {};
    int m=mat.size();
    int n=mat[0].size();
    vector<vector<int>> result(m,vector<int>(n,-1));
    queue<pair<int,int>> q;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(mat[i][j]==0)
            {
                q.push({i,j});
                result[i][j]=0;
            }
        }
    }
    int directions[4][2]={
        {-1,0},
        {1,0},
        {0,-1},
        {0,1}
    };

    while(!q.empty())
    {
        auto [x,y]=q.front();
        q.pop();
        for(int d=0;d<4;++d)
        {
            int nx=x+directions[d][0];
            int ny=y+directions[d][1];
            if(nx<0 || nx>=m || ny<0 || ny>=n)
                continue;
            if(result[nx][ny]!=-1)
                continue;
            result[nx][ny]=result[x][y]+1;
            q.push({nx,ny});
        }
    }
    return result;
}

/*
46. **LC 79 单词搜索**｜Medium｜S｜DFS + 回溯
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。
输入：board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = "ABCCED"
输出：true
*/
bool dfs_exist(vector<vector<char>>& board,int i,int j,vector<vector<bool>>& visited,int index,const string& word)
{
    int m=board.size();
    int n=board[0].size();
    if(i<0 || i>=m || j<0 || j>=n)
        return false;
    if(visited[i][j])
        return false;
    if(board[i][j]!=word[index])
        return false;
    if(index==word.size()-1)
        return true;

    visited[i][j]=true;
    bool found = dfs_exist(board,i-1,j,visited,index+1,word) || 
        dfs_exist(board,i+1,j,visited,index+1,word) || 
        dfs_exist(board,i,j-1,visited,index+1,word) || 
        dfs_exist(board,i,j+1,visited,index+1,word);
    visited[i][j]=false;
    return found;

}
bool exist(vector<vector<char>>& board, string word) {
    if(board.empty() || board[0].empty())
        return false;

    if(word.empty())
        return true;

    int m=board.size();
    int n=board[0].size();
    vector<vector<bool>> visited(m,vector<bool>(n,false));
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(dfs_exist(board,i,j,visited,0,word))
                return true;        
        }
    }
    return false;
}

/*
47. **LC 130 被围绕的区域**｜Medium｜A｜边界反向搜索
给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' 组成，捕获 所有 被围绕的区域：

连接：一个单元格与水平或垂直方向上相邻的单元格连接。
区域：连接所有 'O' 的单元格来形成一个区域。
围绕：如果一个区域中的所有 'O' 单元格都不在棋盘的边缘，则该区域被包围。
这样的区域 完全 被 'X' 单元格包围。
通过 原地 将输入矩阵中的所有 'O' 替换为 'X' 来 捕获被围绕的区域。你不需要返回任何值。

示例 1：

输入：board = [['X','X','X','X'],['X','O','O','X'],['X','X','O','X'],['X','O','X','X']]

输出：[['X','X','X','X'],['X','X','X','X'],['X','X','X','X'],['X','O','X','X']]
*/
void dfs_cir(vector<vector<char>>& board,int i,int j,vector<vector<bool>>& visited)
{
    int m=board.size();
    int n=board[0].size();
    if(i<0 || i>=m || j<0 || j>=n)
        return;
    if(visited[i][j])
        return;
    if(board[i][j]!='O')
        return;
    visited[i][j]=true;
    dfs_cir(board,i-1,j,visited);
    dfs_cir(board,i+1,j,visited);
    dfs_cir(board,i,j-1,visited);
    dfs_cir(board,i,j+1,visited);
}
void solve(vector<vector<char>>& board) {
    if(board.empty() || board[0].empty())
        return;
    
    int m=board.size();
    int n=board[0].size();
    vector<vector<bool>> visited(m,vector<bool>(n,false));

    //遍历左右两列
    for(int i=0;i<m;++i)
    {
        if(board[i][0]=='O')
            dfs_cir(board,i,0,visited);
        if(board[i][n-1]=='O')
            dfs_cir(board,i,n-1,visited);
    }

    //遍历上下两行
    for(int j=0;j<n;++j)
    {
        if(board[0][j]=='O')
            dfs_cir(board,0,j,visited);
        if(board[m-1][j]=='O')
            dfs_cir(board,m-1,j,visited);
    }

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(board[i][j]=='O' && visited[i][j]==false)
                board[i][j]='X';
        }
    }
}

/*
48. **LC 417 太平洋大西洋水流问题**｜Medium｜A｜逆向搜索
有一个 m × n 的矩形岛屿，与 太平洋 和 大西洋 相邻。 “太平洋” 处于大陆的左边界和上边界，而 “大西洋” 处于大陆的右边界和下边界。

这个岛被分割成一个由若干方形单元格组成的网格。给定一个 m x n 的整数矩阵 heights ， 
heights[r][c] 表示坐标 (r, c) 上单元格 高于海平面的高度 。

岛上雨水较多，如果相邻单元格的高度 小于或等于 当前单元格的高度，雨水可以直接向北、南、东、西流向相邻单元格。
水可以从海洋附近的任何单元格流入海洋。

返回网格坐标 result 的 2D 列表 ，其中 result[i] = [ri, ci] 表示雨水从单元格 (ri, ci) 流动 既可流向太平洋也可流向大西洋 。
*/
void dfs_pac(vector<vector<int>>& heights,int i,int j,vector<vector<bool>>& visited)
{
    int m=heights.size();
    int n=heights[0].size();

    if(visited[i][j])
        return;
    
    visited[i][j]=true;
    int direct[4][2]=
    {
        {-1,0},
        {1,0},
        {0,-1},
        {0,1}
    };
    for(int k=0;k<4;++k)
    {
        int x=i+direct[k][0];
        int y=j+direct[k][1];
        // 必须先判断越界
        if(x < 0 || x >= m || y < 0 || y >= n)
            continue;

        if(visited[x][y])
            continue;

        // 反向搜索：
        // 从海洋往高处走
        if(heights[x][y] < heights[i][j])
            continue;

        dfs_pac(heights, x, y, visited);
    }

}

vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    // 当题目问“很多点能不能到某几个固定边界/终点”时，不要从每个点出发搜索，优先考虑从固定终点反向搜索。

    if(heights.empty()||heights[0].empty())
        return {};

    int m=heights.size();
    int n=heights[0].size();
    vector<vector<bool>> pacific(
        m, vector<bool>(n, false)
    );

    vector<vector<bool>> atlantic(
        m, vector<bool>(n, false)
    );    
    
    vector<vector<int>> result;

    // 太平洋：
    // 左边界 + 上边界
    for(int i=0;i<m;++i)
        dfs_pac(heights,i,0,pacific);
    for(int j=0;j<n;++j)
        dfs_pac(heights,0,j,pacific);
    
    // 大西洋：
    // 右边界 + 下边界
    for(int i=0;i<m;++i)
        dfs_pac(heights,i,n-1,atlantic);
    for(int j=0;j<n;++j)
        dfs_pac(heights,m-1,j,atlantic);


    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(pacific[i][j] && atlantic[i][j])
                result.push_back({i,j});
        }
    }
    return result;
}
