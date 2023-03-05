//新的战场基类
#pragma once
class BaseGameBattle
{
public:
	//BaseGameBattle();
	//~BaseGameBattle();

	virtual unsigned char RunUpdate( unsigned int nCurrentTime ) =0;
	virtual void Init() = 0;
	virtual void Destroy() = 0;
};
//inline BaseGameBattle::BaseGameBattle()
//{
//	Init();
//}
//inline BaseGameBattle::~BaseGameBattle()
//{
//	Destroy();
//}