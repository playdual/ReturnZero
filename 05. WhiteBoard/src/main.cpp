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



	return 0;
}
