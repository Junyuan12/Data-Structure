#include <iostream>

using namespace std;

//尾递归
void tail(int i) {
    if (i > 0) {
        cout << i << " ";
        tail(i - 1);
    }
}

int main() {
    tail(5);
    cout << "\n";
    system("pause");
    return 0;
}