#include "json.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <Windows.h>
#include <vector>

using namespace std;

struct Tile {
	int type;
	int m_BlockPositionX;
	int m_BlockPositionY;
	std::vector<std::pair<std::string, int>> m_innerPocketMonInfo;
	std::string m_nextMapName;
	POINT m_nextMapStartIdx;

	void print() {
		cout << type << endl
			<< m_BlockPositionX << endl
			<< m_BlockPositionY << endl
			<< m_nextMapName << endl
			<< m_nextMapStartIdx.x << endl
			<< m_nextMapStartIdx.y << endl;
		for (auto e : m_innerPocketMonInfo) {
			cout << e.first << " " << e.second << endl;
		}
		cout << endl;
	}
};

void writer(vector<Tile>& v, string name) {
	Json::Value root;
	string innerPocketName = "innerPocketName-";
	string innerPocketLevel = "innerPocketLevel-";
	for (int i = 0; i < v.size(); ++i) {
		Json::Value tile;
		string s = to_string(i);
		tile["type"] = v[i].type;
		tile["bPosX"] = v[i].m_BlockPositionX;
		tile["bPosY"] = v[i].m_BlockPositionY;
		tile["nextMap"] = v[i].m_nextMapName;
		tile["nextMapStartX"] = v[i].m_nextMapStartIdx.x;
		tile["nextMapStartY"] = v[i].m_nextMapStartIdx.y;
		tile["innerPocketMonCnt"] = v[i].m_innerPocketMonInfo.size();
		for (int j = 0; j < v[i].m_innerPocketMonInfo.size(); ++j) {
			tile[innerPocketName + to_string(j)] = v[i].m_innerPocketMonInfo[j].first;
			tile[innerPocketLevel + to_string(j)] = v[i].m_innerPocketMonInfo[j].second;
		}
		root[s] = tile;
	}
	ofstream ouput(name, ios::out);
	ouput << root;
	ouput.close();
}

vector<Tile> reader(std::string mapName) {
	Json::Value root;
	Json::Reader reader;
	ifstream input(mapName, ifstream::binary);
	reader.parse(input, root);
	input.close();

	vector<Tile> readTileVector;
	string innerPocketName = "innerPocketName-";
	string innerPocketLevel = "innerPocketLevel-";
	for (auto& e : root) {
		Tile tile;
		tile.type = e["type"].asInt();
		tile.m_BlockPositionX = e["bPosX"].asInt();
		tile.m_BlockPositionY = e["bPosY"].asInt();
		tile.m_nextMapName = e["nextMap"].asString();
		tile.m_nextMapStartIdx.x = e["nextMapStartX"].asInt();
		tile.m_nextMapStartIdx.y = e["nextMapStartY"].asInt();
		int innerPocketCnt = e["innerPocketMonCnt"].asInt();
		for (int i = 0; i < innerPocketCnt; ++i) {
			string name = e[innerPocketName + to_string(i)].asString();
			int level = e[innerPocketLevel + to_string(i)].asInt();
			tile.m_innerPocketMonInfo.push_back(make_pair(name, level));
		}
		readTileVector.push_back(tile);
	}
	return readTileVector;
}

int main() {

	string mapName = "sunwoo.json";
	/*vector<Tile> map;

	Tile tile;
	tile.m_BlockPositionX = 13;
	tile.m_BlockPositionY = 13;
	tile.type = 13;
	tile.m_innerPocketMonInfo.push_back(make_pair("fuck", 3));
	tile.m_nextMapName = "nami";
	tile.m_nextMapStartIdx.x = 10;
	tile.m_nextMapStartIdx.y = 10;

	Tile tile2;
	tile2.m_BlockPositionX = 13;
	tile2.m_BlockPositionY = 13;
	tile2.type = 13;
	tile2.m_innerPocketMonInfo.push_back(make_pair("YoungHwanZzang", 3));
	tile2.m_innerPocketMonInfo.push_back(make_pair("JunsooZzang", 3));
	tile2.m_nextMapName = "sandi";
	tile2.m_nextMapStartIdx.x = 10;
	tile2.m_nextMapStartIdx.y = 10;

	Tile tile3;
	tile3.m_BlockPositionY = 11;
	tile3.m_BlockPositionX = 11;
	tile3.type = 76;
	tile3.m_nextMapName = "sunwoo";
	tile3.m_nextMapStartIdx.x = 1;
	tile3.m_nextMapStartIdx.y = 1;

	map.push_back(tile);
	map.push_back(tile2);
	map.push_back(tile3);

	writer(map, mapName);*/
	auto a = reader(mapName);
	/*auto vector = reader(mapName);*/

	for (auto e : a)
		e.print();

	//Item temp;
	//temp.name = "husidin";
	//temp.xpos = 1000;
	//temp.ypos = 100;
	//temp.recovery = 400;
	//temp.buyPrice = 80;
	//temp.count = 5;
	//temp.sellPrice = 300;
	//temp.description = "it is good potion";

	//Item temp2;
	//temp2.name = "power";
	//temp2.xpos = 10200;
	//temp2.ypos = 1030;
	//temp2.recovery = 1400;
	//temp2.buyPrice = 480;
	//temp2.count = 25;
	//temp2.sellPrice = 3010;
	//temp2.description = "it is good potion";

	//Json::Value Medicine;
	//Json::Value husidin;
	//husidin["name"] = temp.name;
	//husidin["xpos"] = temp.xpos;
	//husidin["ypos"] = temp.ypos;
	//husidin["recovery"] = temp.recovery;
	//husidin["buyPrice"] = temp.count;
	//husidin["count"] = temp.count;
	//husidin["sellPrice"] = temp.sellPrice;
	//husidin["description"] = temp.description;

	//Json::Value power;
	//power["name"] = temp2.name;
	//power["xpos"] = temp2.xpos;
	//power["ypos"] = temp2.ypos;
	//power["recovery"] = temp2.recovery;
	//power["buyPrice"] = temp2.count;
	//power["count"] = temp2.count;
	//power["sellPrice"] = temp2.sellPrice;
	//power["description"] = temp2.description;


	//Medicine["husidin"] = husidin;
	//Medicine["power"] = power;
	//////Json::StyledWriter writer;
	//////string ret = writer.write(root);

	//ofstream ouput("test.json", ios::out);
	//ouput << Medicine;
	////cout << Medicine << endl;
	//ouput.close();


	/*Json::Reader reader;
	ifstream input(name, ifstream::binary);
	reader.parse(input, root);
	input.close();*/

	//vector<Item> itemVector;

	//Json::Value MedicineIn;
	//Json::Reader reader;
	//ifstream input("test.json", ifstream::binary);
	//reader.parse(input, MedicineIn);  //json >> root; 
	//input.close();

	//for (auto e : MedicineIn) {
	//	Item temp;
	//	temp.init(e);
	//	itemVector.push_back(temp);
	//	//cout << e << endl;
	//}
	//for (auto e : itemVector)
	//	e.show();
}