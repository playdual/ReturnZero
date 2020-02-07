#include <iostream>
#include <memory>
#include <vector>
#include <map>
using namespace std;

class Item{
public:
	Item(string _name)
		:name(_name)
	{}

public:
	string name;
};

map<int, shared_ptr<Item>> ItemList;


void add(int _key, string _name) 
{
	shared_ptr<Item> tempItem = make_shared<Item>(_name);
	ItemList.insert(make_pair(_key, tempItem));
}

void show() {
	for (auto& e : ItemList) {
		cout << e.first << " " << e.second->name.c_str() << endl;
	}

}


int main() {


	add(3, "모모");
	add(10, "천재");
	add(10, "나 제발 넣어줘");
	add(1, "천재");
	
	auto findVale = ItemList.find(10);

	if (findVale == ItemList.end()) 
		cout << "그거없음 ^^" << endl;
	else {
		cout << findVale->second->name.c_str() << endl;
	}
	
	//cout << findVale->name.c_str() << endl;

	show();
}
