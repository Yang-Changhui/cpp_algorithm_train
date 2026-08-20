# cpp_algorithm_train

C++ 算法训练仓库 · 个人刷题 & 笔试复习

本仓库结合 **高频 LeetCode 面试题** 与 **视觉 / 自动驾驶岗位手写题**，记录 C++17 实现与面试攻略，面向计算机视觉 / 自动驾驶方向的算法面试与笔试。

## 📂 仓库内容

| 文件 / 目录 | 说明 |
| --- | --- |
| `hash_test.cpp` | C++17 实现的 **数组与哈希** 模块题解（LC 1 / 49 / 128 / 238 / 560 / 41） |
| `高频算法笔试题单_视觉与自动驾驶.md` | 110 题刷题题单与速查表，含通用算法题、视觉/自动驾驶专项手写题、labuladong 框架题 |

- 题单覆盖 **14 个考点大类**：数组哈希、排序二分、双指针、滑动窗口、栈队列、链表、二叉树、BFS/DFS、图论、回溯、贪心、动态规划、堆 Top-K、字符串/矩阵/位运算等。
- 包含 **15 道视觉 & 自动驾驶岗位专项题**：IoU/GIoU、NMS、卷积、池化、连通域、RANSAC、3D 投影、voxelization、A*、Dijkstra、KD-Tree、SE(2)、匈牙利匹配、卡尔曼滤波等。
- 提供 **labuladong 框架补强题（10 题）**，强调可迁移的算法模板。
- 附赠 **解题框架速查表** 与 **刷题顺序建议**。

## 🚀 快速开始

### 编译 & 运行

题目代码使用 C++17 编写，推荐使用 `g++` 或 `clang++` 编译：

```bash
g++ -std=c++17 -O2 -Wall hash_test.cpp -o hash_test
./hash_test
```

### 刷题推荐

1. **2 周刷题**：完成所有 `S` 级通用题 + 视觉/规划专项必做题，每日 45–60 分钟模拟。
2. **4–6 周刷题**：`S` 题建模 → `A` 题优化 → 随机模拟抽题 → 目标公司 CodeTop 补集。

👉 详见 [`高频算法笔试题单_视觉与自动驾驶.md`](高频算法笔试题单_视觉与自动驾驶.md)

## 📖 题单结构

| 编号 | 分类 | 题数 |
| ---- | ---- | ---- |
| 1–85 | 通用算法题 | 85 |
| 86–100 | 岗位专项手写题 | 15 |
| 101–110 | labuladong 框架题 | 10 |

题目标注说明：
- **S**：第一轮必做，20–30 分钟独立完成，说明复杂度，覆盖边界。
- **A**：第二轮强化，识别题型，写出最优解。

## 🛠️ 参考来源

- [LeetCode 面试经典 150](https://leetcode.cn/studyplan/top-interview-150/)
- [LeetCode Interview 75](https://leetcode.cn/studyplan/coding-interviews/)
- [NeetCode 150](https://neetcode.io/practice/practice/neetcode150)
- [CodeTop 高频榜](https://codetop.cc/)
- [labuladong 算法笔记](https://labuladong.online/zh/algo/home/)
- [Autonomous Systems Interview Preparation](https://gist.github.com/sunsided/b76260626cefb7512a9b3579f1c9660e)

## License

Personal learning & interview preparation repository.
