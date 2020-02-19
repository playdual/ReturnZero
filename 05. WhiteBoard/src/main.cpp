#include <iostream>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include <string>
using namespace std;

int main() 
{
	std::vector<int> num;
	//std::swap(num(5), num(1));
	num.push_back(1);
	num.push_back(2);
	num.push_back(3);
	num.push_back(4);
	num.push_back(5);
	num.insert(num.begin(), 0);
	//std::cout << num.front() << endl;

	for (int i = 0; i < num.size(); i++)
	{
		cout << num[i] << endl;
	}
	return 0;
}

int main1()
{
	std::vector<int> num;

	num.push_back(1);
	num.push_back(2);
	num.push_back(3);
	num.push_back(4);
	num.push_back(5);

	
	//std::cout << num.front() << endl;
	for (int i = 0; i < num.size() -1 ; i++)
	{
		std::swap(num[i],num[i+1]);
		cout << num[i] << endl;
	}
	return 0;
}