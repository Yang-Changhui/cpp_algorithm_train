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
                int ny=x+directions[d][1];
                if(nx<0 || nx>=m || ny<0 || ny>=n)
                    continue;

                if(mat[nx][ny]==0)
                {
                    flag=true;
                    break;
                }
                if(visited[nx][ny])
                    continue;
                visited[x][y]=true;
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
