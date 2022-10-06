#include <iostream>

using namespace std;

void funcion(int *&ptr)

{
	int *a;
	ptr = a;
}

int main()

{

	int *p;
	cout << p << endl;
	funcion(p);
	cout << p << endl;
	return 0;
}