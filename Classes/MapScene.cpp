#include"MapScene.h"
#include"MapInformation.h"
#include "employeeList.h"
#include "AudioEngine.h"

#define getrealposition(x,y) Vec2(static_cast<float>(mapangle[0][0] + (mapangle[2][0] - mapangle[0][0]) / 3 * y + ((mapangle[1][0] - (mapangle[1][0] - mapangle[3][0]) / 3 * y) - (mapangle[0][0] + (mapangle[2][0] - mapangle[0][0]) / 3 * y)) / 6 * x), static_cast<float>(mapangle[0][1] + (mapangle[2][1] - mapangle[0][1]) / 3 * y))

USING_NS_CC;



// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MapScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    /*************************/
    c = 0;
    remainPuttingNumber = 8;
    /**************************/

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto exit = MenuItemImage::create(
        "exit.png",
        "exit.png",
        CC_CALLBACK_1(MapScene::mapCloseCallback, this));
    if (exit == nullptr ||
        exit->getContentSize().width <= 0 ||
        exit->getContentSize().height <= 0)
    {
        problemLoading("'exit.png' and 'exit.png'");
    }
    else
    {
        float x = origin.x + exit->getContentSize().width / 1.5f;
        float y = origin.y + visibleSize.height - exit->getContentSize().height / 1.5f;
        exit->setPosition(Vec2(x, y));
        exit->setOpacity(210);
    }

    auto pause = MenuItemImage::create(
        "pause.png",
        "pause.png",
        CC_CALLBACK_1(MapScene::mapPauseCallback, this));
    if (pause == nullptr ||
        pause->getContentSize().width <= 0 ||
        pause->getContentSize().height <= 0)
    {
        problemLoading("'pause.png' and 'pause.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - pause->getContentSize().width / 1.5f;
        float y = origin.y + visibleSize.height - pause->getContentSize().height / 1.5f;
        pause->setPosition(Vec2(x, y));
        pause->setOpacity(210);
    }

    auto acc1= MenuItemImage::create(
        "acc1.png",
        "acc1.png");
    acc1->setOpacity(210);
    auto acc2 = MenuItemImage::create(
        "acc2.png",
        "acc2.png");
    acc2->setOpacity(210);
    auto acc= MenuItemToggle::createWithCallback(CC_CALLBACK_1(MapScene::mapAccCallback, this),
        acc1, acc2, NULL);
    acc->setPosition(Vec2(origin.x + visibleSize.width - pause->getContentSize().width - acc1->getContentSize().width / 1.5f, origin.y + visibleSize.height - acc1->getContentSize().height / 1.5f));
    

    // create menu, it's an autorelease object
    auto menu = Menu::create(exit, pause, acc, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 500);

    auto top = Sprite::create("top.png");
    top->setAnchorPoint(Vec2(0.5, 1));
    top->setPosition(Vec2(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height));
    top->setOpacity(210);
    this->addChild(top, 495);
    
    //顶部文字
    std::string enemyNum = std::to_string(killedNumber) + "/" + std::to_string(enemyTotalNember);
    std::string enemyTotal = std::to_string(remainDefendNumber);
    auto enemyNumLabel = Label::createWithTTF(enemyNum, "fonts/arial.ttf", 24);
    auto enemyTotalLabel = Label::createWithTTF(enemyTotal, "fonts/arial.ttf", 24);
    enemyNumLabel->setAnchorPoint(Vec2(0, 1));
    enemyTotalLabel->setAnchorPoint(Vec2(0, 1));
    enemyNumLabel->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - top->getContentSize().width / 4.0f, origin.y + visibleSize.height));
    enemyTotalLabel->setPosition(Vec2(origin.x + visibleSize.width / 2.0f + top->getContentSize().width / 4.0f, origin.y + visibleSize.height));
    enemyTotalLabel->setColor(Color3B(255, 0, 0));
    this->addChild(enemyNumLabel, 496, 100);
    this->addChild(enemyTotalLabel, 496, 101);

    auto _topCustom1 = EventListenerCustom::create("topUpdate1", CC_CALLBACK_1(MapScene::topUpdate1, this));
    auto _topCustom2 = EventListenerCustom::create("topUpdate2", CC_CALLBACK_1(MapScene::topUpdate2, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_topCustom2, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_topCustom1, this);

    //费用显示
    auto C = Sprite::create("c.png");
    C->setAnchorPoint(Vec2(1, 0));
    C->setPosition(Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height / 5.0f));
    C->setOpacity(200);
    this->addChild(C, 495);

    std::string cc = std::to_string(c);
    auto cLabel = Label::createWithTTF(cc, "fonts/arial.ttf", 30);
    cLabel->setAnchorPoint(Vec2::ZERO);
    cLabel->setPosition(Vec2(origin.x + visibleSize.width - C->getContentSize().width/2.0f, origin.y + visibleSize.height / 5.0f));
    this->addChild(cLabel, 496,102);

    
    

    schedule(CC_SCHEDULE_SELECTOR(MapScene::cUpdate), 1.0f);

    return true;
}


void MapScene::topUpdate1(EventCustom* event)
{
    killedNumber++;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->removeChildByTag(100);
    auto top = Sprite::create("top.png");

    std::string enemyNum = std::to_string(killedNumber) + "/" + std::to_string(enemyTotalNember);    
    auto enemyNumLabel = Label::createWithTTF(enemyNum, "fonts/arial.ttf", 24);    
    enemyNumLabel->setAnchorPoint(Vec2(0, 1));    
    enemyNumLabel->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - top->getContentSize().width / 4.0f, origin.y + visibleSize.height));    
    this->addChild(enemyNumLabel, 496, 100);

}
void MapScene::topUpdate2(EventCustom* event)
{
    remainDefendNumber--;
    killedNumber++;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->removeChildByTag(100);
    this->removeChildByTag(101);
    auto top = Sprite::create("top.png");

    std::string enemyNum = std::to_string(killedNumber) + "/" + std::to_string(enemyTotalNember);
    std::string enemyTotal = std::to_string(remainDefendNumber);
    auto enemyNumLabel = Label::createWithTTF(enemyNum, "fonts/arial.ttf", 24);
    auto enemyTotalLabel = Label::createWithTTF(enemyTotal, "fonts/arial.ttf", 24);
    enemyNumLabel->setAnchorPoint(Vec2(0, 1));
    enemyTotalLabel->setAnchorPoint(Vec2(0, 1));
    enemyNumLabel->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - top->getContentSize().width / 4.0f, origin.y + visibleSize.height));
    enemyTotalLabel->setPosition(Vec2(origin.x + visibleSize.width / 2.0f + top->getContentSize().width / 4.0f, origin.y + visibleSize.height));
    enemyTotalLabel->setColor(Color3B(255, 0, 0));
    this->addChild(enemyNumLabel, 496, 100);
    this->addChild(enemyTotalLabel, 496, 101);
}

void MapScene::cUpdate(float dt)
{
    if (c < 99)
        c++;
    this->removeChildByTag(102);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto C = Sprite::create("c.png");

    std::string cc = std::to_string(c);
    auto cLabel = Label::createWithTTF(cc, "fonts/arial.ttf", 36);
    cLabel->setAnchorPoint(Vec2::ZERO);
    cLabel->setPosition(Vec2(origin.x + visibleSize.width - C->getContentSize().width / 2.0f, origin.y + visibleSize.height / 5.0f));
    this->addChild(cLabel, 496, 102);
}
void MapScene::update(float dt)
{
    if (remainDefendNumber == 0)
    {
        MapInformation::getInstance()->eraseAll();
        auto pScheduler = Director::getInstance()->getScheduler();
        pScheduler->setTimeScale(1.0f);
        /***********失败场景***********/
        Director::getInstance()->popScene();
    }
    if (killedNumber == enemyTotalNember)
    {
        MapInformation::getInstance()->eraseAll();
        auto pScheduler = Director::getInstance()->getScheduler();
        pScheduler->setTimeScale(1.0f);
        /***********胜利场景***********/
        Director::getInstance()->popScene();
    }
}



void MapScene1::mapinit(int mapangle[4][2])
{
    for (int x = 0; x < 7; x++)
        for (int y = 0; y < 4; y++)
            map[x][y].position = Vec2(static_cast<float>(mapangle[0][0] + (mapangle[2][0] - mapangle[0][0]) / 3 * y + ((mapangle[1][0] - (mapangle[1][0] - mapangle[3][0]) / 3 * y) - (mapangle[0][0] + (mapangle[2][0] - mapangle[0][0]) / 3 * y)) / 6 * x), static_cast<float>(mapangle[0][1] + (mapangle[2][1] - mapangle[0][1]) / 3 * y));
}

void MapScene::mapCloseCallback(cocos2d::Ref* pSender)
{
    MapInformation::getInstance()->eraseAll();
    auto pScheduler = Director::getInstance()->getScheduler();
    pScheduler->setTimeScale(1.0f);
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->popScene();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MapScene::mapPauseCallback(cocos2d::Ref* pSender)
{
    static bool isStopped = false;
    if (!isStopped)
    {
        Director::getInstance()->stopAnimation();
        isStopped = true;
    }
    else
    { 
        Director::getInstance()->startAnimation();
        isStopped = false;
    }
}
 
void MapScene::mapAccCallback(cocos2d::Ref* pSender)
{
    //static bool isAcc1 = true;
    auto pScheduler = Director::getInstance()->getScheduler();
    if (pScheduler->getTimeScale() == 1.0f || pScheduler->getTimeScale() == 0.1f)
    {
        pScheduler->setTimeScale(pScheduler->getTimeScale() * 2);
    }
    else if(pScheduler->getTimeScale() == 2.0f || pScheduler->getTimeScale() == 0.2f)
    {
        pScheduler->setTimeScale(pScheduler->getTimeScale() / 2);
    }
    //isAcc1 = !isAcc1;
}

Scene* MapScene1::createScene()
{
    return MapScene1::create();
}

bool MapScene1::init()
{
    
    /**************基础数据初始化**************/
    mapinit(mapangle);
    enemyTotalNember = 11;
    cSpeed = 1;
    X_MAX = 7;
    Y_MAX = 4;
    /******************************************/
    if (!MapScene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto Map1 = Sprite::create("Map1Scene1.png");
    if (Map1 == nullptr)
    {
        problemLoading("'Map1Scene1.png'");
    }
    else
    {
        Map1->setAnchorPoint(Vec2::ZERO);
        Map1->setPosition(Vec2(origin.x, origin.y));

        // add the sprite as a child to this layer
        this->addChild(Map1, 0);
    }

    //放置干员层
    auto employeePuttingLayer = Layer::create();
    float time[10] = { 4.0f, 5.0f ,70.0f};
    int fee[10] = { 2,3 ,2};
    int positionType[10] = { up, down , down};
    for (int i = 1; i <= 3; i++)
    {               
        auto list = employeeList<MapScene1>::createSprite(StringUtils::format(".\\employeelist\\%d.png", i).c_str(), i, time[i - 1], fee[i - 1], positionType[i - 1], this);
        list->setAnchorPoint(Vec2::ZERO);
        list->setPosition(Vec2(origin.x + visibleSize.width - list->getContentSize().width * i, origin.y));
        employeePuttingLayer->addChild(list, 0, i);
        //MapInformation::getInstance()->addList(list);
    }
    this->addChild(employeePuttingLayer, 490, 103);

    for (int i = 0; i < 10; i++)//10个源石虫
    {
        MapInformation::getInstance()->addEnemy(YUANSHICHONG, left, positionArray, positionXYArray);
    }
                               //1个士兵
    {
        MapInformation::getInstance()->addEnemy(SHIBING, left, positionArray, positionXYArray);
    }
    
    
    schedule(CC_SCHEDULE_SELECTOR(MapScene1::updateYuanshichong1), 8.0f, 4, 2.0f);
    schedule(CC_SCHEDULE_SELECTOR(MapScene1::updateYuanshichong2), 8.0f, 4, 3.0f);
    scheduleOnce(CC_SCHEDULE_SELECTOR(MapScene1::updateShibing), 45.0f);
    
    
    scheduleUpdate();
    
    return true;
}

void MapScene1::update(float dt)
{
    MapScene::update(dt);

}

void MapScene1::updateYuanshichong1(float dt)
{
    static int num = 0;
    MapInformation::getInstance()->allEnemyInMap.at(num)->setIsadded(true);
    this->addChild(MapInformation::getInstance()->allEnemyInMap.at(num));
    num += 2;
    if (num == 10)
        num = 0;
}

void MapScene1::updateYuanshichong2(float dt)
{
    static int num = 1;
    MapInformation::getInstance()->allEnemyInMap.at(num)->setIsadded(true);
    this->addChild(MapInformation::getInstance()->allEnemyInMap.at(num));
    num += 2;
    if (num == 11)
        num = 1;
}

void MapScene1::updateShibing(float dt)
{
    MapInformation::getInstance()->allEnemyInMap.at(10)->setIsadded(true);       //
    this->addChild(MapInformation::getInstance()->allEnemyInMap.at(10));       //记得改回10！！！！！！
}