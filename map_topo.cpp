#include<iostream>
#include<vector>

using namespace std;

/*
## 9. 图、并查集、拓扑与最短路（7）

50. **LC 207 课程表**｜Medium｜S｜拓扑排序 / 判环
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，
其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

 
示例 1：

输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
*/
bool dfs_can(int i,vector<vector<int>>& graph,vector<int>& visited)
{
    if(visited[i]==1)
        return false;
    if(visited[i]==2)
        return true;
    visited[i]=1;
    for(int next:graph[i])
    {
        if(!dfs_can(next,graph,visited))
            return false;
    }
    visited[i]=2;
    return true;
}
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    // 使用邻接表+dfs
    vector<vector<int>> graph(numCourses);
    for(int i=0;i<prerequisites.size();++i)
        graph[prerequisites[i][1]].push_back(prerequisites[i][0]);    
    vector<int> visited(numCourses,0);

    for(int i=0;i<numCourses;++i)
    {
        if(visited[i]==0)
        {
            if(!dfs_can(i,graph,visited))
                return false;
        }

    }
    return true;
}
