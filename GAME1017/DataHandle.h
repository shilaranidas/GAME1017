#pragma once
#include <vector>
#include "Box.h"
using namespace std;
class DataHandle
{
private:
	vector<Box*> m_vBoxes;
public:
	DataHandle();
	~DataHandle();
	vector<Box*> ReadData();
	void WriteData(vector<Box*> vBoxes);
};

