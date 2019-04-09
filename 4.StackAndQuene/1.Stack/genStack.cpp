//******************* genStack.h ************************
//用栈实现分隔符的匹配

#include <iostream>
#include "genStack.h"
#include <string>

using namespace std;

int main() {
    string str = "s=t[5]+u/(v*(w+y))";
    Stack<char> s1;
    for (int i = 0; i < str.size(); i++) {
        //注意单引号和双引号的使用！！！
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            s1.push(str[i]);
            //cout << "topEL: " << s1.topEl() << endl;
        }
        else if (str[i] == ')' || str[i] == ']' || str[i] == '}') {
            if ((s1.topEl()=='(' && str[i]==')') || (s1.topEl()=='[' && str[i]==']') || (s1.topEl()=='{' && str[i]=='}')) {
                s1.pop();
            }
            else {
                cout << "error!" << endl;
                system("pause");
                return 0;
            } 
        }
        else if (str[i] == '/') {
            if (str[i + 1] == '*') {
                for (int j = i; j < str.size(); j++) {
                    if (str[j] == '*' && str[j + 1] == '/') {
                        i = j + 1;
                        break;
                    }
                    else if (j == str.size()-1) {
                        cout << "'/*' can not match '*/'" << endl;
                        system("pause");
                        return 0;
                    }
                }
            }
            else
                continue;
        }
    }

    if (s1.isEmpty())
        cout << "success!" << endl;
    else
        cout << "failed!" << endl;
    system("pause");
    return 0;
}