#include<iostream>
#include<stack>
#include<algorithm>

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

bool isValid(string s) {
    //遇到左括号入栈右括号
    stack<char> st;
    for(int i=0;i<static_cast<int>(s.size());++i)
    {
        char ch=s[i];
        if(ch=='[')
            st.push(']');
        else if(ch=='(')
            st.push(')');
        else if(ch=='{')
            st.push('}');
        else if(st.empty() || ch!=st.top())
            return false;
        st.pop();
    }
    return st.empty();
}

/*
24. **LC 155 最小栈**｜Medium｜S｜辅助栈

*/