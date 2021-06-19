#pragma once
#include "cocos2d.h"
class Enemy;

#define down 0//地面
#define up 1//高台
#define upanddown 3//空中和地面
#define upthandown 4//优先空中
#define nurse 2//奶
#define phisical 0//物伤
#define magical 1//法伤
#define left 1
#define right 2
#define front 3
#define Back 4

#define DANFA 1
#define ZHONGZHUANG 2

#define getLength(vec) static_cast<float>(std::sqrt(static_cast<double>(vec.x)*vec.x+static_cast<double>(vec.y)*vec.y))

typedef enum {
    employeeStateNone = 0, //无状态
    employeeStateStart,
    employeeStateIdle,
    employeeStateAttack,
    employeeStateBeforeSkill,
    employeeStateDuringSkill,
    employeeStateAfterSkill,
    employeeStateSkill,
    employeeStateDie
}EmployeeState;

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

#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__

class Employee : public cocos2d::Sprite
{
public:
    virtual bool initWithFile(const char* filename);
    void initAnimation();
    void releaseAnimation();
    virtual void initSkillAnimation() = 0;
    virtual void skill() = 0;
    void loadingBlood();
    void loadingSP();
    void choosingMin(Enemy* p);
    void addSkillList();

    Animation* createAnimate(int direction, const char* name, const char* action, int num, int loop, float delayPerUnit);
    void attrackSelectedEnemy();
    bool searchEnemy();
    void searchForBlock();
    void deleteBlockedEnemy(Enemy* m);
    void releaseAllBlockedEnemy();
    bool searchEnemyByType(Vec2 range[12],int rangeNum);
    int getEmployeeListType();

    
    void spUpdate(float dt);
    void skillButtonUpdate(float dt);
    void spIncreaseUpdate(float dt);
    void bloodUpdate(float dt);
    void blockUpdate(float dt);
    void stateUpdate(float dt);
    void update(float dt);
protected:
    std::string name;
    //最大生命值、最大技能值、攻、阻挡数、同时攻击数、攻击速度、攻击范围类型
    int healthMAX, spMAX, attrack, blockNumber, attrackNumber, attrackSpeed, attrackRange;
    //攻击间隔、技能持续时间
    float attrackInterval, skillTime;
    //格子位置坐标
    Vec2 positionXY;
    //地面/高台、法伤/物伤/奶、能攻击的敌人类型、能阻挡的敌人类型
    int positionType, damageType, selectedType, blockedType;
    //锁定的攻击敌人
    Vector<Enemy*> selectedEnemy;   
    //阻挡的敌人
    Vector<Enemy*> blockedEnemy;
    //动作
    Animation* attack1, * attack2, * start1, * start2, * idle1, * idle2, * die1, * die2;
    Animation* beforeskill1, * beforeskill2, * duringskill1, * duringskill2, * afterskill1, * afterskill2, * skill1, * skill2;
    //帧数
    int attackNum, startNum, idleNum, dieNum;
    int beforeskillNum, duringskillNum, afterskillNum, skillNum;
    int attackReachNum;//攻击生效帧数
    CC_SYNTHESIZE(int, health, Health);//当前生命值
    CC_SYNTHESIZE(int, sp, SP);//当前技能值
    CC_SYNTHESIZE(int, defend, Defend);//防御
    CC_SYNTHESIZE(int, magicDefend, MagicDefend);//法抗
    CC_SYNTHESIZE(int, remainBlockNumber, RemainBlockNumber);//剩余阻挡数
    CC_SYNTHESIZE(int, direction0, Direction0);//放置方向
    CC_SYNTHESIZE(EmployeeState, lastState, LastState);
    CC_SYNTHESIZE(EmployeeState, presentState, PresentState);
};

class Aiyafala :public Employee
{
public:
    static Aiyafala* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Aiyafala);
    void update(float dt);

    void skillSPUpdate(float dt);
    void skillAttrackUpdate(float dt);
    void skillHealthUpdate(float dt);
    void skillOverUpdate(float dt);
};

class Xingxiong :public Employee
{
public:
    static Xingxiong* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Xingxiong);
    void update(float dt);

    void skillSPUpdate(float dt);
    void skillAttrackUpdate(float dt);
    void skillHealthUpdate(float dt);
    void skillOverUpdate(float dt);
};

#endif
