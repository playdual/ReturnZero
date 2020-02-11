#include <vector>
#include <memory>
#include <iostream>
using namespace std;

struct some {
	int x;
	int y;
	void something() {
		cout << "hello world" << endl;
	} 
};

int main() {

	vector<shared_ptr<some>> v;

	some* a = new some;

	a->something();

	for (auto& e : v) {
		(*e).x = 3;
		e->y = 4;
	}


	//이터레이터로 v 벡터의 처음부터       끝까지 돌아준다.
	for (auto iter = v.begin(); iter != v.end(); )// 그런데 ++it을 안해준다.
	{
		if ((**iter).x == 2) 
		{
			//erase는 지우는 요소의 다음 이터레이터를 반환한다.
			iter = v.erase(iter);
		}
		else {
			++iter;
		}
	}
}
