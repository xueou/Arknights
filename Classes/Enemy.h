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
	enemyPingYi//��״ֻ̬Ϊ�˸�ƽ�ƶ�����tag
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

	//��������ƶ�·��
	void getPositionArray(Vec2 a[maxpositionarray],Vec2 b[maxpositionarray]);
	//��ö���
	Animation* createAnimate(int direction, const char* name, const char* action, int num, int loop, float delayPerUnit);
	void loadingBlood();
	Employee* searchEmployee();
	void getIsBlockedBy(Employee* p);
	void attrackBlocked();
	void attrackSelected(Employee* p);
	
	void movingAttrackUpdate(float dt);
	void bloodUpdate(float dt);
	void positionUpdate(float dt);
	void positionXYUpdate(float dt);
	void stateUpdate(float dt);
	void update(float dt);
	
	//�ƶ���������飨ʵ���������꣩
	Vec2 positionArray[maxpositionarray] = {}; 
	//·����������xy����
	Vec2 positionXYArray[maxpositionarray] = {};
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
	//�Ƿ�ֻ�б��赲ʱ�Ź���	
	bool onlyAttrackWhenBlocked;
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
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(shibing);
	void update(float dt);
private:
	
};

class yuanshichong :public Enemy
{
public:
	static yuanshichong* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(yuanshichong);
	void update(float dt);
};
//ganranzhegaojijiuchaguan
class ganranzhegaojijiuchaguan :public Enemy
{
public:
	static ganranzhegaojijiuchaguan* createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray]);
	bool initWithFile(const char* filename);
	CREATE_SPIRITE(ganranzhegaojijiuchaguan);
	void update(float dt);
};

#endif