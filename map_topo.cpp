#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include <functional>  // 提供 greater、less 等比较器
#include<algorithm>
#include<cmath>
#include<unordered_map>
#include<unordered_set>
#include<string>
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
bool canFinish_dfs(int numCourses, vector<vector<int>>& prerequisites) {
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

bool canFinish_bfs(int numCourses, vector<vector<int>>& prerequisites) {
    // 使用bfs+入度
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses,0);
    for(int i=0;i<prerequisites.size();++i)
    {
        graph[prerequisites[i][1]].push_back(prerequisites[i][0]);    
        indegree[prerequisites[i][0]]+=1;
    }
    queue<int> q;
    for(int i=0;i<numCourses;++i)
    {
        if(indegree[i]==0)
            q.push(i);
    }
    int count=0;

    while(!q.empty())
    {
        int pre=q.front();
        q.pop();
        count++;
        
        for(auto next:graph[pre])
        {
            if(--indegree[next]==0)
                q.push(next);
        }
    }
    if(count!=numCourses)
        return false;
    return true;
}

/*
51. **LC 210 课程表 II**｜Medium｜S｜输出拓扑序
现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。给你一个数组 prerequisites ，
其中 prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修 bi 。

例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。
如果不可能完成所有课程，返回 一个空数组 。

示例 1：

输入：numCourses = 2, prerequisites = [[1,0]]
输出：[0,1]
解释：总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。
*/

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses,0);
    int m=prerequisites.size();
    for(int i=0;i<m;++i)
    {
        int pre=prerequisites[i][1];
        int next=prerequisites[i][0];
        graph[pre].push_back(next);
        indegree[next]+=1;
    }
    queue<int> q;
    for(int i=0;i<numCourses;++i)
    {
        if(indegree[i]==0)
            q.push(i);
    }
    vector<int> result;
    while(!q.empty())
    {
        int pre=q.front();
        q.pop();
        result.push_back(pre);
        for(auto next:graph[pre])
        {
            indegree[next]--;
            if(indegree[next]==0)   
                q.push(next);
        }
    }
    if(result.size()!=numCourses)
        return {};
    return result;
}

/*
52. **LC 547 省份数量**｜Medium｜S｜并查集
有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b 直接相连，且城市 b 与城市 c 直接相连，
那么城市 a 与城市 c 间接相连。

省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。

给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，
而 isConnected[i][j] = 0 表示二者不直接相连。

返回矩阵中 省份 的数量。
输入：isConnected = [[1,1,0],[1,1,0],[0,0,1]]
输出：2
*/

int findCircleNum_dfs(vector<vector<int>>& isConnected)
{
    // 使用dfs对每个城市遍历
    int n = isConnected.size();

    vector<bool> visited(n, false);
    int count = 0;

    for(int i = 0; i < n; ++i)
    {
        if(visited[i])
            continue;

        count++;

        queue<int> q;
        q.push(i);
        visited[i] = true;

        while(!q.empty())
        {
            int cur = q.front();
            q.pop();

            for(int j = 0; j < n; ++j)
            {
                if(isConnected[cur][j] == 1 && !visited[j])
                {
                    visited[j] = true;
                    q.push(j);
                }
            }
        }
    }

    return count;
}

//并查集
class UnionFind{
public:
    vector<int> parent;
    UnionFind(int n)
    {
        parent.resize(n);
        for(int i=0;i<n;++i)
            parent[i]=i;
    }
    int find(int x)
    {
        if(parent[x]!=x)
            parent[x]=find(parent[x]);
        return parent[x];
    }
    bool unite(int x,int y)
    {
        int rootX=find(x);
        int rootY=find(y);
        if(rootX==rootY)
            return false;
        parent[rootX]=rootY;
        return true;
    }
};

int findCircleNum(vector<vector<int>>& isConnected) {
    int m=isConnected.size();
    int count=m;
    UnionFind uf(m);

    for(int i=0;i<m;++i)
    {
        for(int j=i+1;j<m;++j)
        {
            if(isConnected[i][j]==1)
            {
                if(uf.unite(i,j))
                    count--;
            }

        }
    }
    return count;
}

/*
53. **LC 684 冗余连接**｜Medium｜A｜并查集判环
树可以看成是一个连通且 无环 的 无向 图。

给定一个图，该图从一棵 n 个节点 (节点值 1～n) 的树中添加一条边后获得。
添加的边的两个不同顶点编号在 1 到 n 中间，且这条附加的边不属于树中已存在的边。
图的信息记录于长度为 n 的二维数组 edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。

请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，则返回数组 edges 中最后出现的那个。
输入: edges = [[1,2], [1,3], [2,3]]
输出: [2,3]
*/

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    if(edges.empty()||edges[0].empty())
        return {};
    int n=edges.size();
    UnionFind uf(n+1);
    for(int i=0;i<n;++i)
    {
        int node1=edges[i][0];
        int node2=edges[i][1];
        if(!uf.unite(node1,node2))
            return edges[i];
    }
    return {};
}

/*
54. **LC 743 网络延迟时间**｜Medium｜S｜Dijkstra
有 n 个网络节点，标记为 1 到 n。

给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，
其中 ui 是源节点，vi 是目标节点， wi 是一个信号从源节点传递到目标节点的时间。

现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1 。
输入：times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
输出：2
*/

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    // 使用优先队列
    vector<vector<pair<int,int>>> graph(n+1);
    for(int i=0;i<times.size();++i)
    {
        int ui=times[i][0];
        int vi=times[i][1]; 
        int wi=times[i][2]; 
        graph[ui].push_back({vi,wi});
    }
    vector<int> dis(n+1,INT_MAX);
    dis[k]=0;

    priority_queue<
        pair<int,int>,    
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    pq.push({0,k});
    while(!pq.empty())
    {
        auto [d,node]=pq.top();
        pq.pop();
        if(d>dis[node])
            continue;
        for(auto [next,w]:graph[node])
        {
            if(d+w<dis[next])
            {
                dis[next]=d+w;
                pq.push({dis[next],next});
            }
        }
    }
    int result=0;
    for(int i=1;i<=n;++i)
    {
        if(dis[i]==INT_MAX)
            return -1;
        result=max(result,dis[i]);
    }
    return result;
}


/*
55. **LC 1584 连接所有点的最小费用**｜Medium｜A｜Prim / Kruskal
给你一个points 数组，表示 2D 平面上的一些点，其中 points[i] = [xi, yi] 。

连接点 [xi, yi] 和点 [xj, yj] 的费用为它们之间的 曼哈顿距离 ：|xi - xj| + |yi - yj| ，其中 |val| 表示 val 的绝对值。

请你返回将所有点连接的最小总费用。只有任意两点之间 有且仅有 一条简单路径时，才认为所有点都已连接。
输入：points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
输出：20
*/

int minCostConnectPoints_Kruskal(vector<vector<int>>& points) {
    // Kruskal+并查集
    int n=points.size();
    vector<vector<int>> edges;

    //首先计算距离
    for(int i=0;i<n;++i)
    {
        for(int j=i+1;j<n;++j)
        {
            int dis=abs(points[i][0]-points[j][0])+abs(points[i][1]-points[j][1]);
            edges.push_back({i,j,dis});
        }
    }

    //排序
    sort(edges.begin(),edges.end(),
            [](const vector<int>&a,const vector<int>&b){return a.back() < b.back();});

    int result=0;
    int count=0;
    UnionFind uf(n);
    for(auto &edge:edges)
    {
        int pre=edge[0];
        int next=edge[1];
        int dis=edge[2];
        if(uf.unite(pre,next))
        {
            result+=dis;
            count+=1;
            if(count == n - 1)
                break;
        }
    }
    return result;
}

int minCostConnectPoints_prim(vector<vector<int>>& points) {
    //使用prim+visited
    int n=points.size();
    vector<bool> visited(n,false);

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>> pq;;

    pq.push({0,0});
    int result=0;
    int count=0;
    while(!pq.empty() && count<n)
    {
        auto [d,node]=pq.top();
        pq.pop();
        if(visited[node])
            continue;
        visited[node]=true;
        count+=1;
        result+=d;
        for(int next=0;next<n;++next)
        {
            if(visited[next])
                continue;
            int dis=abs(points[node][0]-points[next][0])+abs(points[node][1]-points[next][1]);
            pq.push({dis,next});
        }
    }
    return result;
}

/*
56. **LC 127 单词接龙**｜Hard｜A｜双向 BFS
在字典（单词列表） wordList 中，从单词 beginWord 和 endWord 的 转换序列 是一个按下述规格形成的序列：

序列中第一个单词是 beginWord 。
序列中最后一个单词是 endWord 。
每次转换只能改变一个字母。
转换过程中的中间单词必须是字典 wordList 中的单词。
给定两个长度相同但内容不同的单词 beginWord 和 endWord 和一个字典 wordList ，
找到从 beginWord 到 endWord 的 最短转换序列 中的 单词数目 。如果不存在这样的转换序列，返回 0。

示例 1：

输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
输出：5
解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。
*/

int ladderLength_singlebfs(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> words(wordList.begin(), wordList.end());
    if(!words.count(endWord))
        return 0;
    int n=wordList.size();
    unordered_set<string> visited;

    queue<string> q;
    q.push(beginWord);
    visited.insert(beginWord);

    int level=1;

    while(!q.empty())
    {
        int size=q.size();

        for(int i=0;i<size;++i)
        {
            string s=q.front();
            q.pop();
            //对于s遍历所有字符
            for(int j=0;j<s.size();++j)
            {
                string next=s;

                //改变26个字符
                for(char c='a';c<='z';++c)
                {
                    if(s[j]==c)
                        continue;
                    next[j]=c;
                    if(words.count(next) && !visited.count(next))
                    {
                        if(next==endWord)
                            return level+1;
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
        }
        level++;
    }
    return 0;
}

int ladderLength_doublebfs(string beginWord,
                 string endWord,
                 vector<string>& wordList)
{
    unordered_set<string> words(wordList.begin(), wordList.end());

    if(!words.count(endWord))
        return 0;

    // 两个方向的当前层
    unordered_set<string> beginSet{beginWord};
    unordered_set<string> endSet{endWord};

    // 已访问
    unordered_set<string> visited;
    visited.insert(beginWord);
    visited.insert(endWord);

    int level = 1;

    while(!beginSet.empty() && !endSet.empty())
    {
        // 永远扩展节点数量少的一边
        if(beginSet.size() > endSet.size())
            swap(beginSet, endSet);

        unordered_set<string> nextSet;

        // 遍历当前这一层
        for(const string& word : beginSet)
        {
            for(int i = 0; i < word.size(); ++i)
            {
                string next = word;

                for(char c = 'a'; c <= 'z'; ++c)
                {
                    if(c == word[i])
                        continue;

                    next[i] = c;

                    // 和另一边相遇
                    if(endSet.count(next))
                        return level + 1;

                    // 必须存在于字典，并且没有访问过
                    if(words.count(next) &&
                       !visited.count(next))
                    {
                        visited.insert(next);
                        nextSet.insert(next);
                    }
                }
            }
        }

        beginSet = move(nextSet);
        level++;
    }

    return 0;
}

int main()
{
    cout << boolalpha;

    // LC 207 课程表：无环 / 有环
    vector<vector<int>> prerequisites1{{1,0}};
    vector<vector<int>> prerequisites2{{1,0},{0,1}};
    cout << "LC207 DFS: " << canFinish_dfs(2, prerequisites1) << " (expected true)" << endl;
    cout << "LC207 BFS: " << canFinish_bfs(2, prerequisites2) << " (expected false)" << endl;

    // LC 210 课程表 II
    vector<vector<int>> prerequisites3{{1,0},{2,0},{3,1},{3,2}};
    vector<int> order = findOrder(4, prerequisites3);
    cout << "LC210 order:";
    for(int x : order)
        cout << " " << x;
    cout << " (one valid order expected)" << endl;

    // LC 547 省份数量
    vector<vector<int>> connected{{1,1,0},{1,1,0},{0,0,1}};
    cout << "LC547 BFS: " << findCircleNum_dfs(connected) << " (expected 2)" << endl;
    cout << "LC547 UnionFind: " << findCircleNum(connected) << " (expected 2)" << endl;

    // LC 684 冗余连接
    vector<vector<int>> edges{{1,2},{1,3},{2,3}};
    vector<int> redundant = findRedundantConnection(edges);
    cout << "LC684 redundant:";
    for(int x : redundant)
        cout << " " << x;
    cout << " (expected 2 3)" << endl;

    // LC 743 网络延迟时间
    vector<vector<int>> times{{2,1,1},{2,3,1},{3,4,1}};
    cout << "LC743: " << networkDelayTime(times, 4, 2) << " (expected 2)" << endl;

    // LC 1584 连接所有点的最小费用
    vector<vector<int>> points{{0,0},{2,2},{3,10},{5,2},{7,0}};
    cout << "LC1584 Kruskal: " << minCostConnectPoints_Kruskal(points) << " (expected 20)" << endl;
    cout << "LC1584 Prim: " << minCostConnectPoints_prim(points) << " (expected 20)" << endl;

    // LC 127 单词接龙
    vector<string> wordList{"hot","dot","dog","lot","log","cog"};
    cout << "LC127 single BFS: " << ladderLength_singlebfs("hit", "cog", wordList) << " (expected 5)" << endl;
    cout << "LC127 double BFS: " << ladderLength_doublebfs("hit", "cog", wordList) << " (expected 5)" << endl;

    return 0;
}
