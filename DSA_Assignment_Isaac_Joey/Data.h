#pragma once
#include <string>
using namespace std;
class Data
{
public:
	Data();
	virtual void displayInfo();
	~Data();
private: 
	int id;
	string name;

};

