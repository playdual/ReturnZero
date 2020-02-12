#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct info {
	int age;
	int tall;
	int love;
	int noise;

	void print() {
		cout << age << " " << tall << " " << love << " " << noise << endl;
	}
};

class Animal {

public:
	virtual void howl() = 0;
	virtual info getInfo() = 0;

	info in;
};

class Cat
	: public Animal
{
public:
	virtual void howl() override
	{
		cout << "야옹 야옹" << endl;
	}
	virtual info getInfo() {
		in.age = 3;
		in.tall = 100;
		in.love = 50;
		return in;
	}
};

class Dog
	: public Animal
{
public:
	void howl() override
	{
		cout << "멍 멍!~" << endl;
	}
	virtual info getInfo() {
		in.age = 3;
		in.tall = 100;
		in.noise = 50;
		return in;
	}
};

int main()
{
	vector<shared_ptr<Animal>> animals;

	animals.push_back(make_shared<Cat>());
	animals.push_back(make_shared<Dog>());

	for (auto e : animals) {
		e->howl();
		e->getInfo().print();
	}


int main() {

	return 0;
}

//vector<shared_ptr<some>> v;
//
//some* a = new some;
//
//a->something();
//
//for (auto& e : v) {
//	(*e).x = 3;
//	e->y = 4;
//}
//
//
////이터레이터로 v 벡터의 처음부터       끝까지 돌아준다.
//for (auto iter = v.begin(); iter != v.end(); )// 그런데 ++it을 안해준다.
//{
//	if ((**iter).x == 2)
//	{
//		//erase는 지우는 요소의 다음 이터레이터를 반환한다.
//		iter = v.erase(iter);
//	}
//	else {
//		++iter;
//	}
//}
