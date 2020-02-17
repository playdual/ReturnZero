#include <iostream>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include <string>
using namespace std;

void add(int& _a)
{
	_a += 3;

}

int main() 
{
	int a = 4;
	add(a);
	cout << a << endl;
}
