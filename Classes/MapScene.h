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
public:
    static cocos2d::Scene* createScene();
    bool init();
    void mapinit(int mapangle[4][2]);
    CREATE_FUNC(MapScene3);
    void update(float dt);

    void updateGanranzhegaojijiuchaguan1(float dt);
    void updateGanranzhegaojijiuchaguan2(float dt);
    void updateGanranzhegaojijiuchaguan3(float dt);

    void updateWusasilieshouzumu1(float dt);
    void updateWusasilieshouzumu2(float dt);
    void updateWusasilieshouzumu3(float dt);
    void updateWusasilieshouzumu4(float dt);
    void updateWusasilieshouzumu5(float dt);
    void updateWusasilieshouzumu6(float dt);
    void updateWusasilieshouzumu7(float dt);

    void updateHuangdideliren(float dt);

    //高台地面标识初始化
    singlePosition map[11][8] =
    {
        {{down},{down},{down},{down},{down},{ban},{ban},{ban} },
        {{down} ,{up} ,{up},{ban},{up} ,{up},{ban},{ban}},
        {{down} ,{up} ,{down} ,{down} ,{down} ,{up},{ban},{ban}},
        {{down} ,{up} ,{down} ,{up},{down} ,{up},{ban},{ban}},
        {{down} ,{down} ,{down} ,{up} ,{down},{ban},{ban},{ban}},
        {{ban} ,{down} ,{down} ,{down} ,{down},{ban},{ban},{ban}},
        {{down} ,{down} ,{down} ,{up} ,{down},{ban},{ban},{ban}},
        {{down} ,{up} ,{down} ,{up},{down} ,{up},{ban},{ban}},
        {{down} ,{up} ,{down} ,{down} ,{down} ,{up},{ban},{ban}},
        {{down} ,{up} ,{up},{ban},{up} ,{up},{ban},{ban}},
        {{down},{down},{down},{down},{down},{ban},{ban},{ban} }
    };
protected:
    //地图四个角实际分辨率坐标
    int mapangle[4][2] =
    {
        {150,146},//左下
        {1139,146},//右下
        {274,640},//左上
        {1012,640}//右上
    };
    //像素路径与格子坐标路径
    Vec2 positionArray1[maxpositionarray] = { Vec2(639,732),Vec2(637,648),Vec2(640,564), Vec2(640,146) };
    Vec2 positionXYArray1[maxpositionarray] = { Vec2(5,7), Vec2(5,6), Vec2(5,5), Vec2(5,0) };
    
    Vec2 positionArray2[maxpositionarray] = { Vec2(565,732), Vec2(560,648) ,Vec2(559,564), Vec2(554,480) ,Vec2(386,480), Vec2(366,313) ,Vec2(548,313), Vec2(640,146) };
    Vec2 positionXYArray2[maxpositionarray] = { Vec2(4,7), Vec2(4,6),Vec2(4,5), Vec2(4,4),Vec2(2,4), Vec2(2,2),Vec2(4,2), Vec2(5,0) };
    
    Vec2 positionArray3[maxpositionarray] = { Vec2(713,732), Vec2(714,648) ,Vec2(721,564), Vec2(722,480) ,Vec2(890,480), Vec2(912,313) ,Vec2(730,313), Vec2(640,146) };
    Vec2 positionXYArray3[maxpositionarray] = { Vec2(6,7), Vec2(6,6),Vec2(6,5), Vec2(6,4),Vec2(8,4), Vec2(8,2),Vec2(6,2), Vec2(5,0) };
    
    
    
    Vec2 positionArray4[maxpositionarray] = { Vec2(274,732), Vec2(252,648), Vec2(235,564), Vec2(150,146), Vec2(640,146) };
    Vec2 positionXYArray4[maxpositionarray] = { Vec2(0,7), Vec2(0,6), Vec2(0,5), Vec2(0,0), Vec2(5,0) };
    float interval4[maxpositionarray] = { 0.f,3.0f };

    Vec2 positionArray5[maxpositionarray] = { Vec2(1012,732), Vec2(1022,648), Vec2(1045,564), Vec2(1139,146), Vec2(640,146) };
    Vec2 positionXYArray5[maxpositionarray] = { Vec2(10,7), Vec2(10,6), Vec2(10,5), Vec2(10,0), Vec2(5,0) };
    float interval5[maxpositionarray] = { 0.f,3.0f };

    Vec2 positionArray6[maxpositionarray] = { Vec2(639,732), Vec2(640,564) ,Vec2(722,480), Vec2(890,480) ,Vec2(912,313), Vec2(366,313), Vec2(386,480) ,Vec2(638,480), Vec2(641,397), Vec2(640,146) };
    Vec2 positionXYArray6[maxpositionarray] = { Vec2(5,7), Vec2(5,5),Vec2(6,4), Vec2(8,4),Vec2(8,2), Vec2(2,2) , Vec2(2,4),Vec2(5,4), Vec2(5,3), Vec2(5,0) };
    //float interval6[maxpositionarray] = { 0.f,40.f,0.f,69.f,93.f,132.f,156.f,0.f,30.f };
    float interval6[maxpositionarray] = { 0.f,4.f,0.f,6.f,9.f,13.f,15.f,0.f,3.f };
};

#endif