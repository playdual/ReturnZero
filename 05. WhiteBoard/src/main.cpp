#include <iostream>
#include <vector>
using namespace std;

class Animal {
protected:
	int a = 0;
	int b = 10;
public:
	virtual void howl() {
		cout << "..." << endl;
	}
	virtual void update() 
	{
		a -= 1;
	}
	virtual void render() 
	{
		cout << b << endl;
	}
};

class Cat
	:public Animal
{
public:
	void howl() {
		cout << "야옹 야옹~" << endl;
	}
	virtual void update() {
		Animal::update();
		a += 2;
	}
	virtual void render() {
		cout << a << endl;
	}

};
class Dog
	:public Animal
{
public:
	void howl()  {
		cout << "멍멍!~" << endl;
	}
	virtual void update() {
		a += 1;
	}
	virtual void render() {
		cout << a << endl;
	}
};

int main() {
	vector<Animal*> animals;
	Animal* jimin = new Cat;
	Animal* kyungJun = new Dog;

	animals.push_back(jimin);
	animals.push_back(kyungJun);

	for (int i = 0; i < animals.size(); ++i) 
	{
		animals[i]->update();
		animals[i]->render();
	}
}
