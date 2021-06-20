#pragma once
#include "cocos2d.h"
USING_NS_CC;

int danfaRange = 10;
Vec2 danfa[5][10] =
{
	{},
	{Vec2(0,0),Vec2(0,1),Vec2(0,-1),Vec2(-1,0),Vec2(-1,1),Vec2(-1,-1),Vec2(-2,0),Vec2(-2,1),Vec2(-2,-1),Vec2(-3,0)},
	{Vec2(0,0),Vec2(0,1),Vec2(0,-1),Vec2(1,0),Vec2(1,1),Vec2(1,-1),Vec2(2,0),Vec2(2,1),Vec2(2,-1),Vec2(3,0)},
	{Vec2(0,0),Vec2(-1,0),Vec2(1,0),Vec2(0,1),Vec2(-1,1),Vec2(1,1),Vec2(0,2),Vec2(-1,2),Vec2(1,2),Vec2(0,3)},
	{Vec2(0,0),Vec2(-1,0),Vec2(1,0),Vec2(0,-1),Vec2(-1,-1),Vec2(1,-1),Vec2(0,-2),Vec2(-1,-2),Vec2(1,-2),Vec2(0,-3)}
};
int huoshanRange = 25;
Vec2 huoshan[25] = { Vec2(0,0),Vec2(0,1),Vec2(0,2) ,Vec2(0,3) ,Vec2(0,-1) ,Vec2(0,-2) ,Vec2(0,-3) ,Vec2(1,0) ,Vec2(1,1) ,Vec2(1,2) ,Vec2(1,-1) ,Vec2(1,-2)
,Vec2(2,0) ,Vec2(2,1) ,Vec2(2,-1) ,Vec2(3,0) ,Vec2(-1,0) ,Vec2(-1,1) ,Vec2(-1,2) ,Vec2(-1,-1) ,Vec2(-1,-2) ,Vec2(-2,0) ,Vec2(-2,1) ,Vec2(-2,-1) ,Vec2(-3,0) };



int zhongzhuangRange = 2;
Vec2 zhongzhuang[5][2] =
{
	{},
	{Vec2(0,0),Vec2(-1,0)},
	{Vec2(0,0),Vec2(1,0)},
	{Vec2(0,0),Vec2(0,1)},
	{Vec2(0,0),Vec2(0,-1)}
};
int lizhijuRange = 1;
Vec2 lizhiju[5][1] =
{
	{},
	{Vec2(-1,0)},
	{Vec2(1,0)},
	{Vec2(0,1)},
	{Vec2(0,-1)}
};



int naidunattrackRange = 1;
Vec2 naidunattrack[5][1] =
{
	{},
	{Vec2(0,0)},
	{Vec2(0,0)},
	{Vec2(0,0)},
	{Vec2(0,0)}
};
int naiduncureRange = 21;
Vec2 naiduncure[21] = { Vec2(0,0),Vec2(0,1),Vec2(0,2) ,Vec2(0,-1) ,Vec2(0,-2) ,Vec2(1,0) ,Vec2(1,1) ,Vec2(1,2) ,Vec2(1,-1) ,Vec2(1,-2)
,Vec2(2,0) ,Vec2(2,1) ,Vec2(2,-1)  ,Vec2(-1,0) ,Vec2(-1,1) ,Vec2(-1,2) ,Vec2(-1,-1) ,Vec2(-1,-2) ,Vec2(-2,0) ,Vec2(-2,1) ,Vec2(-2,-1)};



int fajinweiRange = 2;
Vec2 fajinwei[5][2] =
{
	{},
	{Vec2(0,0),Vec2(-1,0)},
	{Vec2(0,0),Vec2(1,0)},
	{Vec2(0,0),Vec2(0,1)},
	{Vec2(0,0),Vec2(0,-1)}
};
int huanghunRange = 4;
Vec2 huanghun[5][4] =
{
	{},
	{Vec2(0,0),Vec2(-1,0),Vec2(-2,0),Vec2(-3,0)},
	{Vec2(0,0),Vec2(1,0),Vec2(2,0),Vec2(3,0)},
	{Vec2(0,0),Vec2(0,1),Vec2(0,2),Vec2(0,3)},
	{Vec2(0,0),Vec2(0,-1),Vec2(0,-2),Vec2(0,-3)}
};



int qunweiRange = 3;
Vec2 qunwei[5][3] =
{
	{},
	{Vec2(0,0),Vec2(-1,0),Vec2(-2,0)},
	{Vec2(0,0),Vec2(1,0),Vec2(2,0)},
	{Vec2(0,0),Vec2(0,1),Vec2(0,2)},
	{Vec2(0,0),Vec2(0,-1),Vec2(0,-2)}
};



int dannaiRange = 12;
Vec2 dannai[5][12] =
{
	{},
	{Vec2(0,0),Vec2(0,1),Vec2(0,-1),Vec2(-1,0),Vec2(-1,1),Vec2(-1,-1),Vec2(-2,0),Vec2(-2,1),Vec2(-2,-1),Vec2(-3,0),Vec2(-3,1),Vec2(-3,-1)},
	{Vec2(0,0),Vec2(0,1),Vec2(0,-1),Vec2(1,0),Vec2(1,1),Vec2(1,-1),Vec2(2,0),Vec2(2,1),Vec2(2,-1),Vec2(3,0),Vec2(3,1),Vec2(3,-1)},
	{Vec2(0,0),Vec2(-1,0),Vec2(1,0),Vec2(0,1),Vec2(-1,1),Vec2(1,1),Vec2(0,2),Vec2(-1,2),Vec2(1,2),Vec2(0,3),Vec2(1,3),Vec2(-1,3)},
	{Vec2(0,0),Vec2(-1,0),Vec2(1,0),Vec2(0,-1),Vec2(-1,-1),Vec2(1,-1),Vec2(0,-2),Vec2(-1,-2),Vec2(1,-2),Vec2(0,-3),Vec2(1,-3),Vec2(-1,-3)}
};



Vec2 suju[5][12] =
{
	{},
	{},
	{},
	{},
	{}
};