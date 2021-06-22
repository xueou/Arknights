#include "MapInformation.h"

MapInformation* MapInformation::instance;

MapInformation* MapInformation::getInstance()
{
	if (instance == NULL)
		instance = new MapInformation();
	return instance;
}

void MapInformation::addEnemy(int type, int direction, Vec2 positionArray[maxpositionarray], Vec2 positionXYArray[maxpositionarray])
{
    switch (type)
    {
        case SHIBING: {
            auto shibing = shibing::createSprite(StringUtils::format(".\\enemy\\shibing\\shibing%d.png", direction).c_str(), positionArray, positionXYArray);
            shibing->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(shibing);
            shibing->loadingBlood(); }
            break;
        case YUANSHICHONG: {
            auto yuanshichong = yuanshichong::createSprite(StringUtils::format(".\\enemy\\yuanshichong\\yuanshichong%d.png", direction).c_str(), positionArray, positionXYArray);
            yuanshichong->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(yuanshichong);
            yuanshichong->loadingBlood(); }
            break;
        case GANRANZHEGAOJIJIUCHAGUAN: {
            auto ganranzhegaojijiuchaguan = ganranzhegaojijiuchaguan::createSprite(StringUtils::format(".\\enemy\\ganranzhegaojijiuchaguan\\ganranzhegaojijiuchaguan%d.png", direction).c_str(), positionArray, positionXYArray);
            ganranzhegaojijiuchaguan->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(ganranzhegaojijiuchaguan);
            ganranzhegaojijiuchaguan->loadingBlood(); }
            break;
        case WUSASILIESHOUZUMU: {
            auto wusasilieshouzumu = wusasilieshouzumu::createSprite(StringUtils::format(".\\enemy\\wusasilieshouzumu\\wusasilieshouzumu%d.png", direction).c_str(), positionArray, positionXYArray);
            wusasilieshouzumu->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(wusasilieshouzumu);
            wusasilieshouzumu->loadingBlood(); }
            break;
        case WUSASIGAOJIZHUOKAISHUSHI: {
            auto wusasigaojizhuokaishushi = wusasigaojizhuokaishushi::createSprite(StringUtils::format(".\\enemy\\wusasigaojizhuokaishushi\\wusasigaojizhuokaishushi%d.png", direction).c_str(), positionArray, positionXYArray);
            wusasigaojizhuokaishushi->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(wusasigaojizhuokaishushi);
            wusasigaojizhuokaishushi->loadingBlood(); }
            break;
        case HUANGDIDELIREN: {
            auto huangdideliren = huangdideliren::createSprite(StringUtils::format(".\\enemy\\huangdideliren\\huangdideliren%d.png", direction).c_str(), positionArray, positionXYArray);
            huangdideliren->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(huangdideliren);
            huangdideliren->loadingBlood(); }
            break;
        case DIGUOQIANFENGJINGRUI: {
            auto diguoqianfengjingrui = diguoqianfengjingrui::createSprite(StringUtils::format(".\\enemy\\diguoqianfengjingrui\\diguoqianfengjingrui%d.png", direction).c_str(), positionArray, positionXYArray);
            diguoqianfengjingrui->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(diguoqianfengjingrui);
            diguoqianfengjingrui->loadingBlood(); }
            break;
        case DIGUOQIANFENGBAIZHANJINGRUI: {
            auto diguoqianfengbaizhanjingrui = diguoqianfengbaizhanjingrui::createSprite(StringUtils::format(".\\enemy\\diguoqianfengbaizhanjingrui\\diguoqianfengbaizhanjingrui%d.png", direction).c_str(), positionArray, positionXYArray);
            diguoqianfengbaizhanjingrui->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(diguoqianfengbaizhanjingrui);
            diguoqianfengbaizhanjingrui->loadingBlood(); }
            break;
        case DIGUOPAOHUOZHONGSHUXIANZHAOZHE: {
            auto diguopaohuozhongshuxianzhaozhe = diguopaohuozhongshuxianzhaozhe::createSprite(StringUtils::format(".\\enemy\\diguopaohuozhongshuxianzhaozhe\\diguopaohuozhongshuxianzhaozhe%d.png", direction).c_str(), positionArray, positionXYArray);
            diguopaohuozhongshuxianzhaozhe->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(diguopaohuozhongshuxianzhaozhe);
            diguopaohuozhongshuxianzhaozhe->loadingBlood(); }
            break;
    }
}

void MapInformation::addEnemy(int type, int direction, Vec2 positionArray[maxpositionarray], Vec2 positionXYArray[maxpositionarray], float interval[maxpositionarray])
{
    switch (type)
    {
        case SHIBING: {
            auto shibing = shibing::createSprite(StringUtils::format(".\\enemy\\shibing\\shibing%d.png", direction).c_str(), positionArray, positionXYArray, interval);
            shibing->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(shibing);
            shibing->loadingBlood(); }
            break;
        case YUANSHICHONG: {
            auto yuanshichong = yuanshichong::createSprite(StringUtils::format(".\\enemy\\yuanshichong\\yuanshichong%d.png", direction).c_str(), positionArray, positionXYArray, interval);
            yuanshichong->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(yuanshichong);
            yuanshichong->loadingBlood(); }
            break;
        case GANRANZHEGAOJIJIUCHAGUAN: {
            auto ganranzhegaojijiuchaguan = ganranzhegaojijiuchaguan::createSprite(StringUtils::format(".\\enemy\\ganranzhegaojijiuchaguan\\ganranzhegaojijiuchaguan%d.png", direction).c_str(), positionArray, positionXYArray, interval);
            ganranzhegaojijiuchaguan->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(ganranzhegaojijiuchaguan);
            ganranzhegaojijiuchaguan->loadingBlood(); }
            break;
        case WUSASILIESHOUZUMU: {
            auto wusasilieshouzumu = wusasilieshouzumu::createSprite(StringUtils::format(".\\enemy\\wusasilieshouzumu\\wusasilieshouzumu%d.png", direction).c_str(), positionArray, positionXYArray, interval);
            wusasilieshouzumu->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(wusasilieshouzumu);
            wusasilieshouzumu->loadingBlood(); }
            break;
        case WUSASIGAOJIZHUOKAISHUSHI: {
            auto wusasigaojizhuokaishushi = wusasigaojizhuokaishushi::createSprite(StringUtils::format(".\\enemy\\wusasigaojizhuokaishushi\\wusasigaojizhuokaishushi%d.png", direction).c_str(), positionArray, positionXYArray, interval);
            wusasigaojizhuokaishushi->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(wusasigaojizhuokaishushi);
            wusasigaojizhuokaishushi->loadingBlood(); }
            break;
        case HUANGDIDELIREN: {
            auto huangdideliren = huangdideliren::createSprite(StringUtils::format(".\\enemy\\huangdideliren\\huangdideliren%d.png", direction).c_str(), positionArray, positionXYArray, interval);
            huangdideliren->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(huangdideliren);
            huangdideliren->loadingBlood(); }
            break;
        case DIGUOQIANFENGJINGRUI: {
            auto diguoqianfengjingrui = diguoqianfengjingrui::createSprite(StringUtils::format(".\\enemy\\diguoqianfengjingrui\\diguoqianfengjingrui%d.png", direction).c_str(), positionArray, positionXYArray, interval);
            diguoqianfengjingrui->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(diguoqianfengjingrui);
            diguoqianfengjingrui->loadingBlood(); }
            break;
        case DIGUOQIANFENGBAIZHANJINGRUI: {
            auto diguoqianfengbaizhanjingrui = diguoqianfengbaizhanjingrui::createSprite(StringUtils::format(".\\enemy\\diguoqianfengbaizhanjingrui\\diguoqianfengbaizhanjingrui%d.png", direction).c_str(), positionArray, positionXYArray, interval);
            diguoqianfengbaizhanjingrui->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(diguoqianfengbaizhanjingrui);
            diguoqianfengbaizhanjingrui->loadingBlood(); }
            break;
        case DIGUOPAOHUOZHONGSHUXIANZHAOZHE: {
            auto diguopaohuozhongshuxianzhaozhe = diguopaohuozhongshuxianzhaozhe::createSprite(StringUtils::format(".\\enemy\\diguopaohuozhongshuxianzhaozhe\\diguopaohuozhongshuxianzhaozhe%d.png", direction).c_str(), positionArray, positionXYArray, interval);
            diguopaohuozhongshuxianzhaozhe->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEnemyInMap.pushBack(diguopaohuozhongshuxianzhaozhe);
            diguopaohuozhongshuxianzhaozhe->loadingBlood(); }
            break;
    }
}

void MapInformation::eraseAll()
{
    for (Enemy* p : instance->allEnemyInMap)
    {
        p->unschedule(CC_SCHEDULE_SELECTOR(Enemy::bloodUpdate));
        p->releaseAnimation();
    }
    instance->allEmployeeInMap.clear();
	instance->allEnemyInMap.clear();
    //instance->allEmployeeInList.clear();
}