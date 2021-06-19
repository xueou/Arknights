#pragma once
#include "cocos2d.h"
#include <string>

#define maxpositionarray 15//路径坐标数组存放最大坐标点数
#define up 1//高台
#define down 0//地面
#define ban -1//禁止部署

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
    int positionType;//地面，高台，禁止部署
    bool isOccupyed = false;
    cocos2d::Vec2 position;//具体地图上的x，y坐标
};

class MapScene : public cocos2d::Scene
{
public:

    virtual bool init();

    /************此处具体对象应声明singlePosition数组存储每格具体信息***************/
    /************此处具体对象应定义所需路线数组***************/

    //地图数组初始化
    virtual void mapinit(int mapangle[4][2]) = 0;

    void mapCloseCallback(cocos2d::Ref* pSender);
    void mapPauseCallback(cocos2d::Ref* pSender);
    void mapAccCallback(cocos2d::Ref* pSender);

    void topUpdate1(EventCustom* event);//更新顶部信息
    void topUpdate2(EventCustom* event);
    void cUpdate(float dt);//费用显示更新
    void remainPuttingNumUpdate(float dt);//费用显示更新

    void win();
    void lose();

    void update(float dt);

    int X_MAX, Y_MAX;
protected:
    /***************具体对象要记住定义地图长宽格子数常量**************/
    int remainDefendNumber = 3;//防御点剩余抵御数
    int killedNumber = 0;//已击杀敌人数
    int enemyTotalNember;//地图敌人总数
    int mapEnemyRemainNumber = 0;//地图当前存在敌人数
    int cSpeed;//回费速度，每cSpeed秒回一费
    CC_SYNTHESIZE(int, c, C);//部署费用   
    CC_SYNTHESIZE(int, remainPuttingNumber, RemainPuttingNumber);//剩余部署数量
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
    

    //高台地面标识初始化
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
    //地图四个角实际分辨率坐标
    int mapangle[4][2] =
    {
        {280,248},
        {1001,248},
        {340,532},
        {949,532}
    };
    //移动坐标点数组（实际像素坐标）
    Vec2 positionArray[maxpositionarray] = { Vec2(1014,342),Vec2(748,436), Vec2(534,436), Vec2(528,342), Vec2(300,342), Vec2(320,436), Vec2(213,436) };
    //路线所属格子xy坐标
    Vec2 positionXYArray[maxpositionarray] = { Vec2(7,1), Vec2(4,2), Vec2(2,2), Vec2(2,1), Vec2(0,1), Vec2(0,2), Vec2(-1,2), };
};

class MapScene2 : public MapScene
{

};

class MapScene3 : public MapScene
{

};

#endif