#pragma once
#include "cocos2d.h"
#include "Employee.h"
#include <cmath>
#include <vector>
#include <string>
#define maxpositionarray 15//路径坐标数组存放最大坐标点数
#define down 0//地面敌人
#define up 1//空中敌人
#define phisical 0//物伤敌人
#define magical 1//法伤敌人
#define left 1
#define right 2

typedef enum {
	enemyStateNone = 0, //无状态
	enemyStateIdle,
	enemyStateAttackOnce,
	enemyStateAttackKeep,
	enemyStateMove,
	enemyStateDie,
	enemyPingYi//此状态并非实际状态（平移始终与move状态绑定），只是为了给平移动作设tag
}EnemyState;

//考虑到阻挡因素，实际action时起始点不一定在路径拐点上，故需根据实际像素坐标差、理论像素坐标差、理论格子数计算该动作实际格子数
#define realSquareNum(realXY,theoryRealXY,theorySquareNum) static_cast<float>(std::sqrt((static_cast<double>(realXY.x)*realXY.x+static_cast<double>(realXY.y)*realXY.y)/(static_cast<double>(theoryRealXY.x)*theoryRealXY.x+static_cast<double>(theoryRealXY.y)*theoryRealXY.y)*(static_cast<double>(theorySquareNum.x)*theorySquareNum.x+static_cast<double>(theorySquareNum.y)*theorySquareNum.y)))
//获得当前移动方向，从而调用不同方向的动作
#define getDirection(xNow,xNext) xNow>=xNext?(left):(right)

#define CREATE_SPIRITE(__TYPE__) \
static __TYPE__* create(const char *filename) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithFile(filename)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

USING_NS_CC;

#ifndef __ENEMY_H__
#define __ENEMY_H__

class Enemy : public cocos2d::Sprite
{
public:
	virtual bool initWithFile(const char* filename);
	void initAnimation();
	void releaseAnimation();

	//赋予对象移动路径、停顿时间
	void getPositionArray(Vec2 a[maxpositionarray],Vec2 b[maxpositionarray]);
	void getIntervalArray(float p[maxpositionarray]);
	//获得动画
	Animation* createAnimate(int direction, const char* name, const char* action, int num, int loop, float delayPerUnit, float yPlus=0.f);
	void loadingBlood();
	bool searchEmployee();
	void getIsBlockedBy(Employee* p);
	virtual void attrackBlocked();
	void attrackSelected(Employee* p);
		
	void idleForInterval(float ddt);
	void zorderUpdate(float dt);
	void movingAttrackUpdate(float dt);
	void bloodUpdate(float dt);
	void positionUpdate(float dt);
	void recoverPositionUpdate(float dt);
	void positionXYUpdate(float dt);
	void stateUpdate(float dt);
	void update(float dt);
	
	//移动坐标点数组（实际像素坐标）
	Vec2 positionArray[maxpositionarray] = {}; 
	//路线所属格子xy坐标
	Vec2 positionXYArray[maxpositionarray] = {};
	//路线每点停顿时间
	float interval[maxpositionarray] = {};
	//数组中实际存放点数（计数从0开始）、当下已经过的点数
	int pointNum = -1, pointNow;
	//当下所处实际xy格子坐标
	std::vector<Vec2> positionXYNow;
	//当下所处实际像素位置坐标
	Vec2 positionNow;
	Employee* isBlockedBy = NULL;
protected:
	std::string name;
	//最大生命值、攻、攻击速度、法伤/物伤
	int healthMAX, attrack, attrackSpeed, damageType;
	//移动速度、攻击间隔、远程攻击半径（格子数）
	float moveSpeed, attrackInterval, attrackR;
	//是否只有被阻挡时才攻击、路径中是否存在停顿	
	bool onlyAttrackWhenBlocked, withInterval = false;
	//锁定的攻击干员
	Vector<Employee*> selectedEmployee;
	//动作
	Animation* attack1keep, *attack2keep, * attack1once, * attack2once, *move1, *move2, *idle1, *idle2, *die1, *die2;
	//帧数
	int attackNum, moveNum, idleNum, dieNum;
	//攻击生效帧数
	int attackReachNum;
	CC_SYNTHESIZE(int, health, Health);//当前生命值
	CC_SYNTHESIZE(int, defend, Defend);//防
	CC_SYNTHESIZE(int, blockNumber, BlockNumber);//所需阻挡数（重量）
	CC_SYNTHESIZE(int, magicDefend, MagicDefend);//法抗
	CC_SYNTHESIZE(int, positionType, PositionType);//地面/高台
	CC_SYNTHESIZE(EnemyState, lastState, LastState);
	CC_SYNTHESIZE(EnemyState, presentState, PresentState);
	CC_SYNTHESIZE(bool, isadded, Isadded);//是否被添加到地图
	CC_SYNTHESIZE(bool, isblocked, Isblocked);//是否被阻挡
	CC_SYNTHESIZE(bool, ismoving, Ismoving);//是否在移动
};

class shibing :public Enemy
{
public:
	static shibing* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	static shibing* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray]);
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(shibing);
	void update(float dt);
private:
	
};

class yuanshichong :public Enemy
{
public:
	static yuanshichong* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	static yuanshichong* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray]);
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(yuanshichong);
	void update(float dt);
};

class ganranzhegaojijiuchaguan :public Enemy
{
public:
	static ganranzhegaojijiuchaguan* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	static ganranzhegaojijiuchaguan* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray]);
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(ganranzhegaojijiuchaguan);
	void update(float dt);
};

class wusasilieshouzumu :public Enemy
{
public:
	static wusasilieshouzumu* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	static wusasilieshouzumu* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray],float interval[maxpositionarray]);
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(wusasilieshouzumu);
	void update(float dt);
};

class wusasigaojizhuokaishushi :public Enemy
{
public:
	static wusasigaojizhuokaishushi* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	static wusasigaojizhuokaishushi* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray]);
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(wusasigaojizhuokaishushi);
	void update(float dt);
};

class diguoqianfengjingrui :public Enemy
{
public:
	static diguoqianfengjingrui* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	static diguoqianfengjingrui* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray]);
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(diguoqianfengjingrui);
	void update(float dt);

	void attrackIncreasing(float dt);
};

class diguoqianfengbaizhanjingrui :public Enemy
{
public:
	static diguoqianfengbaizhanjingrui* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	static diguoqianfengbaizhanjingrui* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray]);
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(diguoqianfengbaizhanjingrui);
	void update(float dt);

	void attrackIncreasing(float dt);
};

class diguopaohuozhongshuxianzhaozhe :public Enemy
{
public:
	static diguopaohuozhongshuxianzhaozhe* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	static diguopaohuozhongshuxianzhaozhe* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray]);
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(diguopaohuozhongshuxianzhaozhe);
	void update(float dt);
};

class huangdideliren :public Enemy
{
public:
	static huangdideliren* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	static huangdideliren* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray]);
	bool initWithFile(const char* filename);
	void initAnimation();
	void releaseAnimation();
	CREATE_SPIRITE(huangdideliren);
	void attrackBlocked();
	void update(float dt);
	void stateUpdate(float dt);

    Vec2 searchForGuodu();
	bool searchForEmployee();
	void skillGuodu(Vec2 center);
	void skillRecover();
	void unbeatableOver(float dt);

	void skillTansuo(float dt);
	void guoduRecover(float dt);
	void guoduUpdate1(float dt);
	void guoduUpdate2(float dt);
	void guoduUpdate3(float dt);
	void guoduUpdate4(float dt);
	void skillOverUpdate(float dt);
protected:
	Vec2 guoduCenter[4] = { Vec2(-1,-1),Vec2(-1,-1) ,Vec2(-1,-1) ,Vec2(-1,-1) };
	Animation* guodu1, * guodu2, * skill1, * skill2, * beforerecover1, * beforerecover2, * duringrecover1, * duringrecover2, * afterrecover1, * afterrecover2;
	int guoduNum, skillNum, beforerecoverNum, duringrecoverNum, afterrecoverNum;
	float recoverTime, guoduTime, skillTime;
	bool isrecovered = false;
};

#endif