#include<iostream>

using namespace std;

void f(int x, int & y){
    x = 5;
    y = 8;
}


int main() {
    int x = 1, y = 2;
    f(y, x);
    cout << x << " - " << y << endl;
    return 0;
}