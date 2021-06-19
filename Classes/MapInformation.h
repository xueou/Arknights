#pragma once
#include "cocos2d.h"
#include "Enemy.h"
#include "Employee.h"
#include "employeeList.h"

#define maxpositionarray 15//路径坐标数组存放最大坐标点数
#define SHIBING 1
#define YUANSHICHONG 2
#define YAOGUAI 3

#ifndef _MAPINFORMATION_H_
#define _MAPINFORMATION_H_

USING_NS_CC;

class MapInformation
{
public:
	Vector<Enemy*> allEnemyInMap;
	Vector<Employee*> allEmployeeInMap;
	//Vector<employeeList<map>*> allEmployeeInList;

	static MapInformation* getInstance();
	void addEnemy(int type, int direction, Vec2 positionArray[maxpositionarray], Vec2 positionXYArray[maxpositionarray]);
	//void addList(employeeList<map>* list);
	static void eraseAll();
private:
	static MapInformation* instance;
};

#endif