#include <iostream>

using namespace std;



char str[20] = "Hi, there!";



int main() {
int* v1 = new int[4];

for(int i = 0; i < 3; i++)

	v1[i] = i;

int* v2 = v1;

v1[3] = 3;

v2[3] = 4;

for(int i = 0; i < 4; i++)

{

	cout << v1[i] << ", ";

	cout << v2[i] << endl;

}

cout << "delete" << endl;

delete []v1;

for(int i = 0; i < 4; i++)

{

	cout << v1[i] << ", ";

	cout << v2[i] << endl;

}

}