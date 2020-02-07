#include <iostream>
#include <string>
#include <fstream>
using namespace std;
  
//addPotionItem("초급 Hp포션", WINSIZEX / 2, 100, 400, 80, "초급 Hp포션", 3, 50, " 포켓몬의 체력을 30만큼 회복 시켜준다.", 30, 0);

enum KINDCOUNT
{
	ITEMKIND = 1, NAME , RECTX , RECTY , WIDTH , HEIGHT ,
	COUNT , PRICE , DESCRIPTION , HEALHP , DAMAGE , ADDABILITY 
};
struct potionText {
	int		itemKind[100];		//1
	string	name[100];			//2
	int		rectX[100];			//3
	int		rectY[100];			//4
	int		width[100];			//5	
	int		height[100];		//6
	int		count[100];			//7
	int		price[100];			//8
	string	description[100];	//9
	int		healHp[100];		//10
	int		damage[100];		//11
	int		addAbility[100];	//12
};

int main(void)
{
	std::string str;
	std::string inputStr;
	KINDCOUNT kindCount;
	kindCount = ITEMKIND;

	potionText itemPotion;

	ifstream readFile;
	readFile.open("text/itemList.txt");

	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			getline(readFile, str);
			readFile.imbue(std::locale("kor"));
			inputStr += str;
			inputStr += "\n";
		}
		readFile.close();
	}
	char myInputStr[5000];
	strcpy(myInputStr, inputStr.c_str());
	//cout << myInputStr << endl;

	char *ptr = strtok(myInputStr, "#");
	int count = 0;

	while (ptr != NULL)
	{
		char spaceBar = *ptr;
		count++;
	
		for (int i = 0; i < 14; i++)
		{
			if (spaceBar == '\n')
			{
				count = 0;
				ptr = strtok(NULL, "#");
			}
			switch (kindCount)
			{
			case ITEMKIND:
				itemPotion.itemKind[i] = atoi(ptr);
				cout << "ITEMKIND : " << itemPotion.itemKind[i] << endl;
				ptr = strtok(NULL, "#");

			case NAME:
				itemPotion.name[i] = ptr;
				cout << "NAME : " << itemPotion.name[i] << endl;
				ptr = strtok(NULL, "#");


			case RECTX:
				itemPotion.rectX[i] = atoi(ptr);
				cout << "RECTX : " << itemPotion.rectX[i] << endl;
				ptr = strtok(NULL, "#");

			case RECTY:
				itemPotion.rectY[i] = atoi(ptr);
				cout << "RECTY : " << itemPotion.rectY[i] << endl;
				ptr = strtok(NULL, "#");


			case WIDTH:
				itemPotion.width[i] = atoi(ptr);
				cout << "WIDTH : " << itemPotion.width[i] << endl;
				ptr = strtok(NULL, "#");

			case HEIGHT:
				itemPotion.height[i] = atoi(ptr);
				cout << "HEIGHT : " << itemPotion.height[i] << endl;
				ptr = strtok(NULL, "#");


			case COUNT:
				itemPotion.count[i] = atoi(ptr);
				cout << "COUNT : " << itemPotion.count[i] << endl;
				ptr = strtok(NULL, "#");


			case PRICE:
				itemPotion.price[i] = atoi(ptr);
				cout << "PRICE : " << itemPotion.price[i] << endl;
				ptr = strtok(NULL, "#");


			case DESCRIPTION:
				itemPotion.description[i] = ptr;
				cout << "DESCRIPTION : " << itemPotion.description[i] << endl;
				ptr = strtok(NULL, "#");

			if (itemPotion.itemKind[i] == 2)
			{
				case HEALHP:
				itemPotion.healHp[i] = atoi(ptr);
				cout << "HEALHP : " << itemPotion.healHp[i] << endl;
				ptr = strtok(NULL, "#");

			}
			
			if ( itemPotion.itemKind[i] == 2 || itemPotion.itemKind[i] == 5)
			{
				case DAMAGE:
				itemPotion.damage[i] = atoi(ptr);
				cout << "DAMAGE : " << itemPotion.damage[i] << endl;
				ptr = strtok(NULL, "#");
				
			}
			
			if (itemPotion.itemKind[i] == 4)
			{
			case ADDABILITY:
				itemPotion.addAbility[i] = atoi(ptr);
				cout << "ADDABILITY : " << itemPotion.addAbility[i] << endl;
				ptr = strtok(NULL, "#");

			}
			default:
				 count = 0;
				 cout << endl;
			}
		}

		//cout << ptr << endl;
		ptr = strtok(NULL, "#");
	}

	for (int i = 0; i < 15; i++)
	{
		cout << itemPotion.name[i] << endl;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//==========================================================
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//
	//char practice[300] = "\n[몬스터볼]\n1.\n100\n210\n85";

	//char* pract = strtok(practice, "\n");

	//
	//bool isFind = false;
	//int count = 0;
	//while (pract != NULL)
	//{
	//	count++;
	//    char a = *pract;
	//	string insertChar = pract;
	//    if (a == '[')
	//    {
	//    	pract = strtok(NULL, "\n");
	//		count -= 1;
	//    	continue;
	//    }
	//	for (auto& c : insertChar)
	//	{
	//		if (c == '.')
	//		{
	//		   pract = strtok(NULL, "\n");
	//		   continue;
	//		}
	//	}


	//   //switch (count)
	//   //{
	//   //case 1:
	//	  // num.a = atoi(pract);
	//	  // cout << "a = "<< num.a << endl;
	//	  //
	//	  // break;

	//   //case 2:
	//	  // num.b = atoi(pract);
	//	  // cout << "b = " << num.b << endl;
	//	  // break;

	//   //case 3:
	//	  // num.c = atoi(pract);
	//	  // cout << "c = " << num.c << endl;
	//	  // break;

	//   //default:
	//	  // break;
	//   //}
	//   pract = strtok(NULL, "\n");

	//}

	//==========================================================

	return 0;
}

