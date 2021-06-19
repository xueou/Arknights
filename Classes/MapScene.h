#pragma once
#include "cocos2d.h"
#include <string>

#define maxpositionarray 15//·����������������������
#define up 1//��̨
#define down 0//����
#define ban -1//��ֹ����

USING_NS_CC;

/**********************
shibing1 1
enemyNumLabel 100
enemyTotalLabel 101
cLabel 102
************************/

#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

struct singlePosition
{
    int positionType;//���棬��̨����ֹ����
    bool isOccupyed = false;
    cocos2d::Vec2 position;//�����ͼ�ϵ�x��y����
};

class MapScene : public cocos2d::Scene
{
public:

    virtual bool init();

    /************�˴��������Ӧ����singlePosition����洢ÿ�������Ϣ***************/
    /************�˴��������Ӧ��������·������***************/

    //��ͼ�����ʼ��
    virtual void mapinit(int mapangle[4][2]) = 0;

    void mapCloseCallback(cocos2d::Ref* pSender);
    void mapPauseCallback(cocos2d::Ref* pSender);
    void mapAccCallback(cocos2d::Ref* pSender);

    void topUpdate1(EventCustom* event);//���¶�����Ϣ
    void topUpdate2(EventCustom* event);
    void cUpdate(float dt);//������ʾ����
    void remainPuttingNumUpdate(float dt);//������ʾ����

    void win();
    void lose();

    void update(float dt);

    int X_MAX, Y_MAX;
protected:
    /***************�������Ҫ��ס�����ͼ�������������**************/
    int remainDefendNumber = 3;//������ʣ�������
    int killedNumber = 0;//�ѻ�ɱ������
    int enemyTotalNember;//��ͼ��������
    int mapEnemyRemainNumber = 0;//��ͼ��ǰ���ڵ�����
    int cSpeed;//�ط��ٶȣ�ÿcSpeed���һ��
    CC_SYNTHESIZE(int, c, C);//�������   
    CC_SYNTHESIZE(int, remainPuttingNumber, RemainPuttingNumber);//ʣ�ಿ������
};

class MapScene1 : public MapScene
{
public:
    static cocos2d::Scene* createScene();
    bool init();
    void mapinit(int mapangle[4][2]);
    CREATE_FUNC(MapScene1);
    void update(float dt);

    void updateYuanshichong1(float dt);
    void updateYuanshichong2(float dt);
    void updateShibing(float dt);
    

    //��̨�����ʶ��ʼ��
    singlePosition map[7][4] =
    {
        {{up},{down},{down},{up} },
        {{up} ,{down} ,{up} ,{up}},
        {{up} ,{down} ,{down} ,{up}},
        {{up} ,{up} ,{down} ,{up}},
        {{up} ,{down} ,{down} ,{up}},
        {{up} ,{down} ,{down} ,{up}},
        {{up} ,{down} ,{down} ,{up}},
    };
protected:
    //��ͼ�ĸ���ʵ�ʷֱ�������
    int mapangle[4][2] =
    {
        {280,248},
        {1001,248},
        {340,532},
        {949,532}
    };
    //�ƶ���������飨ʵ���������꣩
    Vec2 positionArray[maxpositionarray] = { Vec2(1014,342),Vec2(748,436), Vec2(534,436), Vec2(528,342), Vec2(300,342), Vec2(320,436), Vec2(213,436) };
    //·����������xy����
    Vec2 positionXYArray[maxpositionarray] = { Vec2(7,1), Vec2(4,2), Vec2(2,2), Vec2(2,1), Vec2(0,1), Vec2(0,2), Vec2(-1,2), };
};

class MapScene2 : public MapScene
{

};

class MapScene3 : public MapScene
{

};

#endif