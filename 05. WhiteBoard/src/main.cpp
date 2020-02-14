#include <iostream>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include <string>
using namespace std;
#define INFO_1 1;
#define INFO_2 2;
#define INFO_3 3;

struct Info {
	int InfoType = INFO_1;
	int value;
	string value2;
};
struct Info2 {
	int InfoType = INFO_2;
	float value;
	int name;
};
struct Info3 {
	int InfoType = INFO_3;
	float value;
	vector<int> v;
};
Info ret;
Info2 ret2;
Info3 ret3;

void* getInfo() {
	Info3* returnInfo = new Info3;
	return (void*)returnInfo;
}

int main() {
	/*_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	void* info = new Info;
	cout << *(int*)getInfo() << endl;*/

	//보이드 포인터는 가르키는 대상의 자료형을 미정으로 두는 것이다.

	void* ret = getInfo();
	int* int_ret = (int*)ret;
	cout << *int_ret << endl;

	int result = *int_ret;
	Info temp1;
	Info2 temp2;
	Info3 temp3;
	switch (result)
	{
	case 1:
		temp1 = *((Info*)ret);
		break;
	case 2:
		temp2 = *((Info2*)ret);
		break;
	case 3:
		temp3 = *((Info3*)ret);
		break;
	}	
}