#pragma once
#include "GlobalDef.h"

struct CPlayer_SEquipment
{

	CPlayer_SEquipment()
	{
		Reset();
		/*stEquipItemType = ErrorUnsignedShortID;*/
	}

	void Reset()
	{
		iModelID = InvalidLogicNumber;
		iModelID2 = InvalidLogicNumber;
		iModelID3 = InvalidLogicNumber;
	}
	//װ����Ʒ
	SCharItem item;
	//װ����ģ��ID
	int						iModelID;
	int						iModelID2; //˫����������ͷ������
	int						iModelID3; //�յ����ģ��
	//short  stEquipItemType;//װ������
	//Ч��??
};