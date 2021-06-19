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
    }
}

/*void MapInformation::addList(employeeList* list)
{
    MapInformation::getInstance()->allEmployeeInList.pushBack(list); 
}*/

void MapInformation::eraseAll()
{
    for (Enemy* p : instance->allEnemyInMap)
        p->unschedule(CC_SCHEDULE_SELECTOR(Enemy::bloodUpdate));
    instance->allEmployeeInMap.clear();
	instance->allEnemyInMap.clear();
    //instance->allEmployeeInList.clear();
}