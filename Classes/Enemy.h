#pragma once
#include "cocos2d.h"
#include "Employee.h"
#include <cmath>
#include <vector>
#include <string>
#define maxpositionarray 15//·����������������������
#define down 0//�������
#define up 1//���е���
#define phisical 0//���˵���
#define magical 1//���˵���
#define left 1
#define right 2

typedef enum {
	enemyStateNone = 0, //��״̬
	enemyStateIdle,
	enemyStateAttackOnce,
	enemyStateAttackKeep,
	enemyStateMove,
	enemyStateDie,
	enemyPingYi//��״̬����ʵ��״̬��ƽ��ʼ����move״̬�󶨣���ֻ��Ϊ�˸�ƽ�ƶ�����tag
}EnemyState;

//���ǵ��赲���أ�ʵ��actionʱ��ʼ�㲻һ����·���յ��ϣ��������ʵ�������������������������۸���������ö���ʵ�ʸ�����
#define realSquareNum(realXY,theoryRealXY,theorySquareNum) static_cast<float>(std::sqrt((static_cast<double>(realXY.x)*realXY.x+static_cast<double>(realXY.y)*realXY.y)/(static_cast<double>(theoryRealXY.x)*theoryRealXY.x+static_cast<double>(theoryRealXY.y)*theoryRealXY.y)*(static_cast<double>(theorySquareNum.x)*theorySquareNum.x+static_cast<double>(theorySquareNum.y)*theorySquareNum.y)))
//��õ�ǰ�ƶ����򣬴Ӷ����ò�ͬ����Ķ���
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

	//��������ƶ�·����ͣ��ʱ��
	void getPositionArray(Vec2 a[maxpositionarray],Vec2 b[maxpositionarray]);
	void getIntervalArray(float p[maxpositionarray]);
	//��ö���
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
	
	//�ƶ���������飨ʵ���������꣩
	Vec2 positionArray[maxpositionarray] = {}; 
	//·����������xy����
	Vec2 positionXYArray[maxpositionarray] = {};
	//·��ÿ��ͣ��ʱ��
	float interval[maxpositionarray] = {};
	//������ʵ�ʴ�ŵ�����������0��ʼ���������Ѿ����ĵ���
	int pointNum = -1, pointNow;
	//��������ʵ��xy��������
	std::vector<Vec2> positionXYNow;
	//��������ʵ������λ������
	Vec2 positionNow;
	Employee* isBlockedBy = NULL;
protected:
	std::string name;
	//�������ֵ�����������ٶȡ�����/����
	int healthMAX, attrack, attrackSpeed, damageType;
	//�ƶ��ٶȡ����������Զ�̹����뾶����������
	float moveSpeed, attrackInterval, attrackR;
	//�Ƿ�ֻ�б��赲ʱ�Ź�����·�����Ƿ����ͣ��	
	bool onlyAttrackWhenBlocked, withInterval = false;
	//�����Ĺ�����Ա
	Vector<Employee*> selectedEmployee;
	//����
	Animation* attack1keep, *attack2keep, * attack1once, * attack2once, *move1, *move2, *idle1, *idle2, *die1, *die2;
	//֡��
	int attackNum, moveNum, idleNum, dieNum;
	//������Ч֡��
	int attackReachNum;
	CC_SYNTHESIZE(int, health, Health);//��ǰ����ֵ
	CC_SYNTHESIZE(int, defend, Defend);//��
	CC_SYNTHESIZE(int, blockNumber, BlockNumber);//�����赲����������
	CC_SYNTHESIZE(int, magicDefend, MagicDefend);//����
	CC_SYNTHESIZE(int, positionType, PositionType);//����/��̨
	CC_SYNTHESIZE(EnemyState, lastState, LastState);
	CC_SYNTHESIZE(EnemyState, presentState, PresentState);
	CC_SYNTHESIZE(bool, isadded, Isadded);//�Ƿ���ӵ���ͼ
	CC_SYNTHESIZE(bool, isblocked, Isblocked);//�Ƿ��赲
	CC_SYNTHESIZE(bool, ismoving, Ismoving);//�Ƿ����ƶ�
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