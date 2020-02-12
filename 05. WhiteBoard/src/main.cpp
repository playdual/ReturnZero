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

void tempF(int& _temp)
{
	cout << _temp << endl;
	cout << &_temp << endl;

	
	int _second;
	//값이 복사가 된 것
	_second = _temp; 

	int *_third;
	//값이 갖고있는 주소값을 받아주는 것
	_third = &_temp;

	cout << endl << endl;

	cout << "temp: " << _temp << endl;
	cout << "&temp: " << &_temp << endl;

	cout << endl << endl;

	cout << "second: " << _second << endl;
	cout << "&second: " << &_second << endl;

	cout << endl << endl;

	cout << "third: " << _third << endl;
	cout << "*third: " << *_third << endl;
	cout << "&third: " << &_third << endl;

	int four;
	
}


int main()
{
	vector<shared_ptr<some>> v;
	shared_ptr<some> _some;

	int temp;
	int temp2 = 85;


	shared_ptr<some> aa = make_shared<some>();
	v.push_back(aa);
	shared_ptr<some> bb = make_shared<some>();
	v.push_back(bb);
	shared_ptr<some> cc = make_shared<some>();
	v.push_back(cc);

	cout << v.size() << endl;

	/*for (auto it = v.begin(); it != v.end(); ++it)
	{
		_some = (*it);
		cout << *it << endl;
		cout << _some << endl;

		break;
	}*/

	_some->something();
	
	cout << &temp2 << endl;
	tempF(temp2);






		
		
		
		
		
	//a->something();

	//for (auto& e : v) {
	//	(*e).x = 3;
	//	e->y = 4;
	//}


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

	return 0;
}
