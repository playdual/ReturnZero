﻿#include "stdafx.h"
#include "txtData.h"

TxtData::TxtData()
{
}
TxtData::~TxtData()
{
}

bool TxtData::init()
{
	return true;
}

//한줄짜리 데이터를 담아둘것(모든 데이터를 한줄 단위로 짤라서 지정한다.)
void TxtData::txtSave(char * saveFileName, std::vector<std::string> vStr)
{

	HANDLE file;
	char str[128];
	DWORD write;
	_tcsncpy_s(str, 128, vectorArrayCombine(vStr), 128);

	file = CreateFile
	(saveFileName,			//생성할 파일또는 열 장치나 파일이름
		GENERIC_WRITE,		//파일이나 장치를 만들거나 열때 사용할 권한
		0,					//파일 공유 모드입력
		NULL,				//파일또는 장치를 열때 보안 및 특성
		CREATE_ALWAYS,		//파일이나 장치를 열때 취할 행동
		FILE_ATTRIBUTE_NORMAL, //파일이나 장치를 열때 갖게 될 특성
		NULL);				//만들어질 파일이 갖게 될 특성 확장 특성에 대한 정보

	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);

}
//현재 사용할 데이터(한줄짜리 데이터를 쉼표 단위로 띄어서 저장)
char * TxtData::vectorArrayCombine(std::vector<std::string> vArray)
{
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		_tcsncat_s(str, 128, vArray[i].c_str(), 128);

		if ((i + 1) < vArray.size())
		{
			_tcscat(str, TEXT(","));
		}
	}
	return str;
}

std::vector<std::string> TxtData::txtLoad(char * loadFileName)
{
	HANDLE file;
	char str[128];
	DWORD read;

	file = CreateFile
	(loadFileName,			//생성할 파일또는 열 장치나 파일이름
		GENERIC_READ,		//파일이나 장치를 만들거나 열때 사용할 권한
		0,					//파일 공유 모드입력
		NULL,				//파일또는 장치를 열때 보안 및 특성
		OPEN_EXISTING,		//파일이나 장치를 열때 취할 행동
		FILE_ATTRIBUTE_NORMAL, //파일이나 장치를 열때 갖게 될 특성
		NULL);				//만들어질 파일이 갖게 될 특성 확장 특성에 대한 정보

	ReadFile(file, str, 128, &read, NULL);
	CloseHandle(file);
	return charArraySeperation(str);
}
std::vector<std::string> TxtData::charArraySeperation(char charArray[])
{
	std::vector<std::string>vArray;

	char* seperator = ",";
	char* token;

	token = strtok(charArray, seperator);
	vArray.push_back(token);

	while (NULL!=(token = strtok(NULL, seperator)))
	{
		vArray.push_back(token);
	}
	return vArray;
}
