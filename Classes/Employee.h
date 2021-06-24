#pragma once
#include "cocos2d.h"
class Enemy;

#define down 0//����
#define up 1//��̨
#define upanddown 3//���к͵���
#define upthandown 4//���ȿ���
#define nurse 2//��
#define phisical 0//����
#define magical 1//����
#define left 1
#define right 2
#define front 3
#define Back 4

#define DANFA 1
#define ZHONGZHUANG 2
#define DANNAI 3
#define QUNNAI 4
#define NAIDUN_ATTACK 5
#define NAIDUN_CURE 6
#define FAJINWEI 7
#define HUANGHUN 8
#define QUNWEI 9
#define YUANWEI 10
#define SUJU 11
#define XIANFENG 12

#define getLength(vec) static_cast<float>(std::sqrt(static_cast<double>(vec.x)*vec.x+static_cast<double>(vec.y)*vec.y))

typedef enum {
    employeeStateNone = 0, //��״̬
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
    virtual void releaseSkillAnimation() = 0;
    virtual void initSkillAnimation() = 0;
    virtual void skill() = 0;
    void loadingBlood();
    void loadingSP();
    void choosingMin(Enemy* p);
    void addSkillList();
    void releaseSkillList();

    Animation* createAnimate(int direction, const char* name, const char* action, int num, int loop, float delayPerUnit);
    virtual void attackAnimate();
    void attrackSelectedEnemy();
    bool searchEnemy();
    void searchForBlock();
    void deleteBlockedEnemy(Enemy* m);
    void releaseAllBlockedEnemy();
    bool searchEnemyByType(Vec2 range[12],int rangeNum);
    int getEmployeeListType();

    void skillReadyShowing(float dt);
    void spUpdate(float dt);
    void skillButtonUpdate(float dt);
    void spIncreaseUpdate(float dt);
    void bloodUpdate(float dt);
    void blockUpdate(float dt);
    void stateUpdate(float dt);
    void update(float dt);
protected:
    std::string name;
    //�������ֵ�������ֵ���赲����ͬʱ�������������ٶȡ�������Χ����
    int healthMAX, spMAX, blockNumber, attrackNumber, attrackSpeed, attrackRange;
    //���ܳ���ʱ��
    float skillTime;
    //�Ƿ����Զ�����
    bool isSkillAuto;
    //����/��̨������/����/�̡��ܹ����ĵ������͡����赲�ĵ�������
    int positionType, damageType, selectedType, blockedType;
    //�����Ĺ�������
    Vector<Enemy*> selectedEnemy;   
    //�������Ƶĸ�Ա
    Vector<Employee*> selectedEmployee;
    //�赲�ĵ���
    Vector<Enemy*> blockedEnemy;
    //����
    Animation* attack1, * attack2, * start1, * start2, * idle1, * idle2, * die1, * die2;
    Animation* beforeskill1, * beforeskill2, * duringskill1, * duringskill2, * afterskill1, * afterskill2, * skill1, * skill2;
    //֡��
    int attackNum, startNum, idleNum, dieNum;
    int beforeskillNum, duringskillNum, afterskillNum, skillNum;
    int attackReachNum;//������Ч֡��
    CC_SYNTHESIZE(int, attrack, Attrack);//����
    CC_SYNTHESIZE(int, health, Health);//��ǰ����ֵ
    CC_SYNTHESIZE(int, sp, SP);//��ǰ����ֵ
    CC_SYNTHESIZE(int, defend, Defend);//����
    CC_SYNTHESIZE(int, magicDefend, MagicDefend);//����
    CC_SYNTHESIZE(float, attrackInterval, AttrackInterval);//�������
    CC_SYNTHESIZE(int, remainBlockNumber, RemainBlockNumber);//ʣ���赲��
    CC_SYNTHESIZE(int, direction0, Direction0);//���÷���
    CC_SYNTHESIZE(Vec2, positionXY, PositionXY);//����λ������
    CC_SYNTHESIZE(EmployeeState, lastState, LastState);
    CC_SYNTHESIZE(EmployeeState, presentState, PresentState);
};

class Aiyafala :public Employee
{
public:
    static Aiyafala* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    void attackAnimate();
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Aiyafala);
    void update(float dt);

    void skillSPUpdate(float dt);
    void skillAttrackUpdate(float dt);
    void skillHealthUpdate(float dt);
    void skillOverUpdate(float dt);
    void releaseSkillAnimation();
protected:
    Animation* attackeffect;
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
    void releaseSkillAnimation();
};

class Saileiya :public Employee
{
public:
    static Saileiya* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Saileiya);
    void update(float dt);

    void skillTouchAuto(float dt);
    void skillSPUpdate(float dt);
    void skillAttrackUpdate(float dt);
    void skillHealthUpdate(float dt);
    void skillOverUpdate(float dt);
    void releaseSkillAnimation();
};

class Shierteer :public Employee
{
public:
    static Shierteer* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void releaseSkillAnimation();
    void skill();

    CREATE_SPIRITE(Shierteer);
    void update(float dt);

    void shierteerStateUpdate(float dt);
    void skillHealthUpdate(float dt);
    void die(float dt);
protected:
    bool isskilled = false;
    bool suoxue = false;
};

class Huang :public Employee
{
public:
    static Huang* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Huang);
    void update(float dt);
    void skillTouchAuto(float dt);

    void skillOverUpdate(float dt);
    void recoverUpdate(float dt);
    void releaseSkillAnimation();
protected:
    bool isskilled = false;
    bool isrecovered = false;
};

class Shanling :public Employee
{
public:
    static Shanling* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Shanling);
    void update(float dt);

    void skillSPUpdate(float dt);
    void skillOverUpdate(float dt);
    void releaseSkillAnimation();
};

class Yinhui :public Employee
{
public:
    static Yinhui* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Yinhui);
    void update(float dt);

    void skillSPUpdate(float dt);
    void skillAttrackUpdate(float dt);
    void skillHealthUpdate(float dt);
    void skillOverUpdate(float dt);
    void releaseSkillAnimation();
};

class Baimianxiao :public Employee
{
public:
    static Baimianxiao* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Baimianxiao);
    void update(float dt);

    void skillSPUpdate(float dt);
    void skillAttrackUpdate(float dt);
    void skillHealthUpdate(float dt);
    void skillOverUpdate(float dt);
    void releaseSkillAnimation();
};

class Nengtianshi :public Employee
{
public:
    static Nengtianshi* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Nengtianshi);
    void update(float dt);

    void skillTouchAuto(float dt);
    void skillSPUpdate(float dt);
    void skillAttrackUpdate(float dt);
    void skillHealthUpdate(float dt);
    void skillOverUpdate(float dt);
    void releaseSkillAnimation();
};

class Dekesasi :public Employee
{
public:
    static Dekesasi* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Dekesasi);
    void update(float dt);

    void skillSPUpdate(float dt);
    void skillAttrackUpdate(float dt);
    void skillHealthUpdate(float dt);
    void skillOverUpdate(float dt);
    void releaseSkillAnimation();
};

class Taojinniang :public Employee
{
public:
    static Taojinniang* createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY);
    bool initWithFile(const char* filename);
    void initSkillAnimation();
    void skill();

    CREATE_SPIRITE(Taojinniang);
    void update(float dt);

    void skillSPUpdate(float dt);
    void skillCUpdate(float dt);
    void skillHealthUpdate(float dt);
    void skillOverUpdate(float dt);
    void releaseSkillAnimation();
};

#endif
