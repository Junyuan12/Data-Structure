#include <iostream>

using namespace std;

//非尾递归
void reverse() {
    char ch;
    cin.get(ch);
    if(ch != '\n') {
        reverse();
        cout.put(ch);
    }
}

int main() {
    cout << "Input string: \n";
    reverse();
    cout << "\n";
    system("pause");
    return 0;
}