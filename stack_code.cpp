#include<iostream>
#include<stack>
#include<algorithm>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

/*
## 5. 栈、队列与单调结构（5）

23. **LC 20 有效的括号**｜Easy｜S｜栈
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。

示例 1：

输入：s = "()"

输出：true

*/

bool isValid(const string& s) {
    // 遇到左括号时，把期望匹配的右括号入栈。
    stack<char> st;
    for (char ch : s)
    {
        if (ch == '[')
            st.push(']');
        else if (ch == '(')
            st.push(')');
        else if (ch == '{')
            st.push('}');
        else
        {
            // 当前是右括号：栈不能为空，而且必须和栈顶期望字符一致。
            if (st.empty() || ch != st.top())
                return false;
            st.pop();
        }
    }
    return st.empty();
}

/*
24. **LC 155 最小栈**｜Medium｜S｜辅助栈
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:

MinStack() 初始化堆栈对象。
void push(int value) 将元素 value 推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。
 
示例 1

输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]
*/
class MinStack {
public:
    MinStack() {
        
    }
    
    void push(int value) {
        s.push_back(value);
        if(minstack.empty() || value<=minstack.back())
        {
            minstack.push_back(value);
        }
    }
    
    void pop() {
        if (s.empty()) {
            return;
        }

        // 如果弹出的元素正好是当前最小值，
        // minStack 也要同步弹出
        if (s.back() == minstack.back()) {
            minstack.pop_back();
        }

        s.pop_back();
    }
    
    int top() {
        if(!s.empty())
            return s.back();
        return -1;
    }
    
    int getMin() {
        if(!minstack.empty())
            return minstack.back();
        return -1;

    }
private:
    vector<int> s;
    vector<int> minstack;
};

/*
25. **LC 394 字符串解码**｜Medium｜S｜栈 + 状态保存
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

测试用例保证输出的长度不会超过 105。

示例 1：

输入：s = "3[a]2[bc]"
输出："aaabcbc"
*/


class Solution {
public:
    string decodeString(const string& s) {
        stack<int> numStack;
        stack<string> strStack;

        int num = 0;
        string current;

        for (char ch : s) {

            // 1. 数字
            if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
            }

            // 2. 遇到 [
            else if (ch == '[') {
                numStack.push(num);
                strStack.push(current);

                // 开始处理新的一层
                num = 0;
                current = "";
            }

            // 3. 遇到 ]
            else if (ch == ']') {
                int repeat = numStack.top();
                numStack.pop();

                string previous = strStack.top();
                strStack.pop();

                for (int i = 0; i < repeat; ++i) {
                    previous += current;
                }

                current = previous;
            }

            // 4. 普通字母
            else {
                current += ch;
            }
        }

        return current;
    }
};

/*
26. **LC 739 每日温度**｜Medium｜S｜单调栈
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，
其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

 
示例 1:

输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
*/

vector<int> dailyTemperatures(const vector<int>& temperatures) {
    int n= temperatures.size();
    stack<int> st;
    vector<int> result(n,0);
    for(int i=0;i<n;i++)
    {
        while (!st.empty() && temperatures[i]>temperatures[st.top()])
        {
            int index=st.top();
            st.pop();
            result[index]=i-index;
        }
        st.push(i);
    }
    return result;
}

/*
27. **LC 84 柱状图中最大的矩形**｜Hard｜A｜单调栈边界
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10
*/

int largestRectangleArea(const vector<int>& heights) {
    int n=heights.size();
    int result=0;
    stack<int> st;
    for(int i=0;i<=n;i++)
    {
        int currentHeight=(i==n)?0:heights[i];
        while(!st.empty() && currentHeight<heights[st.top()])
        {
            int index=st.top();
            st.pop();

            int height=heights[index];
            int left=st.empty()?-1:st.top();
            int width=i-left-1;
            result=max(result,width*height);
        }
        if (i < n)
            st.push(i);
    }
    return result;
}


static void printVector(const vector<int>& values)
{
    cout << "[";
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (i > 0) cout << ",";
        cout << values[i];
    }
    cout << "]";
}

int main()
{
    int passed = 0;
    int total = 0;

    auto checkBool = [&](const string& name, bool actual, bool expected) {
        ++total;
        bool ok = (actual == expected);
        passed += ok;
        cout << (ok ? "[PASS] " : "[FAIL] ") << name
             << " actual=" << boolalpha << actual
             << " expected=" << expected << '\n';
    };

    auto checkInt = [&](const string& name, int actual, int expected) {
        ++total;
        bool ok = (actual == expected);
        passed += ok;
        cout << (ok ? "[PASS] " : "[FAIL] ") << name
             << " actual=" << actual << " expected=" << expected << '\n';
    };

    auto checkString = [&](const string& name, const string& actual, const string& expected) {
        ++total;
        bool ok = (actual == expected);
        passed += ok;
        cout << (ok ? "[PASS] " : "[FAIL] ") << name
             << " actual=\"" << actual << "\" expected=\"" << expected << "\"\n";
    };

    auto checkVector = [&](const string& name, const vector<int>& actual, const vector<int>& expected) {
        ++total;
        bool ok = (actual == expected);
        passed += ok;
        cout << (ok ? "[PASS] " : "[FAIL] ") << name << " actual=";
        printVector(actual);
        cout << " expected=";
        printVector(expected);
        cout << '\n';
    };

    // LC 20
    checkBool("LC20 ()", isValid("()"), true);
    checkBool("LC20 ()[]{}", isValid("()[]{}"), true);
    checkBool("LC20 ([{}])", isValid("([{}])"), true);
    checkBool("LC20 (]", isValid("(]"), false);
    checkBool("LC20 ([)]", isValid("([)]"), false);
    checkBool("LC20 single left", isValid("("), false);

    // LC 155
    {
        MinStack ms;
        ms.push(-2);
        ms.push(0);
        ms.push(-3);
        checkInt("LC155 getMin #1", ms.getMin(), -3);
        ms.pop();
        checkInt("LC155 top", ms.top(), 0);
        checkInt("LC155 getMin #2", ms.getMin(), -2);

        ms.push(-2);
        checkInt("LC155 duplicate min", ms.getMin(), -2);
        ms.pop();
        checkInt("LC155 duplicate min after pop", ms.getMin(), -2);
    }

    // LC 394
    Solution solution;
    checkString("LC394 basic", solution.decodeString("3[a]2[bc]"), "aaabcbc");
    checkString("LC394 nested", solution.decodeString("3[a2[c]]"), "accaccacc");
    checkString("LC394 suffix", solution.decodeString("2[abc]3[cd]ef"), "abcabccdcdcdef");
    checkString("LC394 multi-digit", solution.decodeString("10[a]"), "aaaaaaaaaa");

    // LC 739
    checkVector("LC739 example",
                dailyTemperatures(vector<int>{73,74,75,71,69,72,76,73}),
                vector<int>{1,1,4,2,1,1,0,0});
    checkVector("LC739 increasing",
                dailyTemperatures(vector<int>{30,40,50,60}),
                vector<int>{1,1,1,0});
    checkVector("LC739 decreasing",
                dailyTemperatures(vector<int>{60,50,40}),
                vector<int>{0,0,0});

    // LC 84
    checkInt("LC84 example", largestRectangleArea(vector<int>{2,1,5,6,2,3}), 10);
    checkInt("LC84 two bars", largestRectangleArea(vector<int>{2,4}), 4);
    checkInt("LC84 increasing", largestRectangleArea(vector<int>{1,2,3,4,5}), 9);
    checkInt("LC84 equal", largestRectangleArea(vector<int>{2,2,2}), 6);
    checkInt("LC84 empty", largestRectangleArea(vector<int>{}), 0);

    cout << "\nSummary: " << passed << "/" << total << " tests passed.\n";
    return passed == total ? 0 : 1;
}
