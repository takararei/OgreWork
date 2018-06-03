#include "stdafx.h"
#include "OgreData.h"

IMPLEMENT_SERIAL(OgreData,CObject,1)

OgreData::OgreData(void)
{
}


OgreData::~OgreData(void)
{
}


void OgreData::Serialize(CArchive& ar)

{

	if(ar.IsLoading())
	{
		ar>>count;
		for (int i=0;i<count;i++)
		{
			ar>>scale[i];
			ar>>posX[i];
			ar>>posY[i];
			ar>>posZ[i];
			ar>>modelname[i];
		}
	}
	else if(ar.IsStoring())
	{
		ar<<count;

		for (int i=0;i<count;i++)
		{
			ar<<scale[i];
			ar<<posX[i];
			ar<<posY[i];
			ar<<posZ[i];
			ar<<modelname[i];
			
		}
	}

}