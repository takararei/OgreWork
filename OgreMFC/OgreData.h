#pragma once

#include<iostream>
#include<vector>
using namespace std;
class OgreData:public CObject
{
public:

	DECLARE_SERIAL(OgreData)

	OgreData(void);
	~OgreData(void);
	virtual void Serialize(CArchive& ar);
	
	int count;//生成物体计数
	
	float scale[100];
	float posX[100];
	float posY[100];
	float posZ[100];
	int modelname[100];

	
};


