#pragma once
#include "MapScene.h"
#include"MapInformation.h"
#include "AudioEngine.h"

#define aiyafala 1
#define xingxiong 2

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
template<class T>
class employeeList :public cocos2d::Sprite
{
public:
    bool initWithFile(const char* filename);
    static employeeList<T>* createSprite(const char* filename,int type,float reputTime,int fee, int positionType, T* pScene);
    void showPuttingPosition();
    Vec2 judgePuttingPosition(Vec2 finalPosition, Vec2& positionXY);
    void deletePuttingPosition();
    void directionChoosing();
    void reputtingLoading();

    Vector<Sprite*> puttingPosition;
    Vector<Sprite*> puttingPositionXY;
    //Sprite* getEmployeeMove();
    void employeeCreate(int direction0, Vec2 position, Vec2 positionXY);
    CREATE_SPIRITE(employeeList);

    T* map1 = NULL;
    //Sprite* move = NULL;

    /*bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);*/
    /*void onMouseDown(Event* event);
    void onMouseUp(Event* event);
    void onMouseMove(Event* event);*/

    void update(float dt);
    void reputUpdate(float dt);

    void frontChooseCallback(cocos2d::Ref* pSender);
    void backChooseCallback(cocos2d::Ref* pSender);
    void leftChooseCallback(cocos2d::Ref* pSender);
    void rightChooseCallback(cocos2d::Ref* pSender);
    void giveupChooseCallback(cocos2d::Ref* pSender);


    CC_SYNTHESIZE(bool, isadded, Isadded);
    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(int, fee, Fee);
    CC_SYNTHESIZE(float, reputTime, ReputTime);
    CC_SYNTHESIZE(int, reputNum, ReputNum);
    CC_SYNTHESIZE(int, positionType, PositionType);
    CC_SYNTHESIZE(float, reputTimeNow, ReputTimeNow);
};

template<class T>
bool employeeList<T>::initWithFile(const char* filename)
{
    if (!Sprite::initWithFile(filename))
    {
        return false;
    }

    reputNum = 0;

    /*auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(employeeList::onMouseMove, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(employeeList::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(employeeList::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);*/
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch, Event* event)
    {
        int realFee = this->getFee() + (this->getReputNum() >= 2 ? (this->getFee()) : (this->getReputNum() == 1 ? (this->getFee() / 2) : (0)));
        if (map1->getC() >= realFee && map1->getRemainPuttingNumber() > 0 && !this->getIsadded() &&
            Rect(this->getPosition().x, this->getPosition().y, 
                this->getContentSize().width, this->getContentSize().height).containsPoint(touch->getLocation()))
        {
            auto target = static_cast<employeeList*>(event->getCurrentTarget());
            auto p = Sprite::create(StringUtils::format(".\\employeelist\\selected%d.png", type).c_str());
            target->setTexture(p->getTexture());
            target->setAnchorPoint(Vec2(0.5, 0));
            target->setPosition(touch->getLocation());

            showPuttingPosition();
            
            return true;
        }
        return false;
    };
    listener->onTouchMoved = [](Touch* touch, Event* event)
    {
        auto target = static_cast<employeeList*>(event->getCurrentTarget());
        target->setPosition(touch->getLocation());
    };
    listener->onTouchEnded = [this](Touch* touch, Event* event)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        auto target = static_cast<employeeList*>(event->getCurrentTarget());
        
        Vec2 position, positionXY;
        position = judgePuttingPosition(touch->getLocation(), positionXY);
        if (position != Vec2::ZERO)
        {
            deletePuttingPosition();
            target->setPosition(position);
            auto positionXYsaveing = Sprite::create();
            positionXYsaveing->setPosition(positionXY);
            target->addChild(positionXYsaveing, 0, 0);

            directionChoosing();

            target->setOpacity(0);
            target->setIsadded(true);
        }
        else
        {            
            deletePuttingPosition();
        }
        auto p = Sprite::create(StringUtils::format(".\\employeelist\\%d.png", type).c_str());
        target->setTexture(p->getTexture());
        target->setAnchorPoint(Vec2::ZERO);
        target->setPosition(Vec2(origin.x + visibleSize.width - target->getContentSize().width * target->type, origin.y));
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //this->schedule(schedule_selector(HelloWorld::updatePoint));
    

    scheduleUpdate();

    return true;
}


template<class T>
employeeList<T>* employeeList<T>::createSprite(const char* filename, int type, float reputTime, int fee, int positionType, T* pScene)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = employeeList::create(filename);

    p->setIsadded(false);
    p->setType(type);
    p->setFee(fee);
    p->setReputTime(reputTime);
    p->setReputNum(0);
    p->setPositionType(positionType);
    p->map1 = pScene;
    return p;
}

/*template<class T>
Sprite* employeeList<T>::getEmployeeMove()
{
    return Sprite::create(StringUtils::format(".\\employeelist\\selected%d.png", type).c_str());
}*/

template<class T>
void employeeList<T>::showPuttingPosition()
{
    for (int i=0;i<map1->X_MAX;i++)
        for(int j=0;j<map1->Y_MAX;j++)
            if (map1->map[i][j].positionType == this->positionType && !map1->map[i][j].isOccupyed)
            {
                auto greensquare = Sprite::create("greensquare.png");
                greensquare->setOpacity(120);
                greensquare->setAnchorPoint(Vec2(0.5f, 0.5f));
                greensquare->setPosition(map1->map[i][j].position);
                this->puttingPosition.pushBack(greensquare);
                auto p = Sprite::create();
                p->setPosition(Vec2(static_cast<float>(i), static_cast<float>(j)));  //错在这里i,j都加了1吗？？是的！！
                this->puttingPositionXY.pushBack(p);
                auto puttingLayer = dynamic_cast<Layer*>(this->getParent());
                puttingLayer->addChild(greensquare,-10);
            }
    
}

template<class T>
Vec2 employeeList<T>::judgePuttingPosition(Vec2 finalPosition, Vec2& positionXY)
{
    int index = -1;
    for (Sprite* i : this->puttingPosition)
    {
        index++;
        if (Rect(i->getPosition().x - i->getContentSize().width / 2.0f, i->getPosition().y - i->getContentSize().height / 2.0f,
            i->getContentSize().width, i->getContentSize().height).containsPoint(finalPosition))
        {
            positionXY = this->puttingPositionXY.at(index)->getPosition();
            return i->getPosition();
        }
    }

    return Vec2::ZERO;
}

template<class T>
void employeeList<T>::deletePuttingPosition()
{
    while (this->puttingPosition.size() != 0)
    {
        this->puttingPosition.back()->removeFromParent();
        this->puttingPosition.popBack();
        this->puttingPositionXY.popBack();
    }   
}

template<class T>
void employeeList<T>::directionChoosing()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto puttingLayer = dynamic_cast<Layer*>(this->getParent());

    auto covering = Sprite::create();//遮盖层，吞没其他点击
    covering->setContentSize(visibleSize);
    auto listener0 = EventListenerTouchOneByOne::create();
    listener0->setSwallowTouches(true);
    listener0->onTouchBegan = [=](Touch* touch, Event* event) {return true; };
    listener0->onTouchMoved = [](Touch* touch, Event* event) {};
    listener0->onTouchEnded = [](Touch* touch, Event* event) {};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener0, covering);
    puttingLayer->addChild(covering, 50, 100);

    auto replace = Sprite::create(StringUtils::format(".\\employeelist\\selected%d.png", this->type).c_str());
    replace->setAnchorPoint(Vec2(0.5, 0));
    replace->setPosition(this->getPosition());
    puttingLayer->addChild(replace, this->type, 101);

    auto border = Sprite::create("border.png");
    border->setPosition(this->getPosition());
    border->setOpacity(200);
    puttingLayer->addChild(border, 51, 102);

    auto frontitem = MenuItemImage::create("front.png", "front.png",CC_CALLBACK_1(employeeList<T>::frontChooseCallback, this));
    auto backitem = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(employeeList<T>::backChooseCallback, this));
    auto leftitem = MenuItemImage::create("left.png", "left.png", CC_CALLBACK_1(employeeList<T>::leftChooseCallback, this));
    auto rightitem = MenuItemImage::create("right.png", "right.png", CC_CALLBACK_1(employeeList<T>::rightChooseCallback, this));
    auto giveupitem = MenuItemImage::create("giveup.png", "giveup.png", CC_CALLBACK_1(employeeList<T>::giveupChooseCallback, this));
    frontitem->setPosition(this->getPosition() + Vec2(0, frontitem->getContentSize().height * 2.5f) + origin);
    backitem->setPosition(this->getPosition() - Vec2(0, frontitem->getContentSize().height * 2.0f) + origin); 
    leftitem->setPosition(this->getPosition() - Vec2(frontitem->getContentSize().width * 2.0f, 0) + origin);
    rightitem->setPosition(this->getPosition() + Vec2(frontitem->getContentSize().width * 2.0f, 0) + origin);
    giveupitem->setPosition(this->getPosition() + Vec2(-border->getContentSize().width / 3.0f, border->getContentSize().height / 3.0f) + origin);
    frontitem->setOpacity(190);
    backitem->setOpacity(190);
    leftitem->setOpacity(190);
    rightitem->setOpacity(190);
    giveupitem->setOpacity(225);
       
    auto puttingmenu = Menu::create(frontitem, backitem, leftitem, rightitem, giveupitem, NULL);
    puttingmenu->setPosition(Vec2::ZERO);
    puttingLayer->addChild(puttingmenu, 52, 103);
}

template<class T>
void employeeList<T>::reputtingLoading()
{
    reputTimeNow = reputTime + 0.1f;
    
    auto reput0 = Sprite::create("reputloading.png");
    reput0->setOpacity(120);
    reput0->setAnchorPoint(Vec2::ZERO);
    auto _reputListener = EventListenerTouchOneByOne::create();
    _reputListener->setSwallowTouches(true);
    _reputListener->onTouchBegan = [reput0,this](Touch* touch, Event* event)
    {
        if (Rect(this->getPosition().x, this->getPosition().y,
            reput0->getContentSize().width, reput0->getContentSize().height).containsPoint(touch->getLocation()))
            return true;
        else
            return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_reputListener, reput0);
    this->addChild(reput0,1,1);

    auto reput = Sprite::create("reputloading.png");
    auto progress = ProgressTimer::create(reput);
    progress->setType(ProgressTimer::Type::RADIAL);
    progress->setAnchorPoint(Vec2::ZERO);
    progress->setReverseDirection(true);
    
    this->addChild(progress, 1, 2);
    schedule(CC_SCHEDULE_SELECTOR(employeeList<T>::reputUpdate),0.1f);
}

template<class T>
void employeeList<T>::employeeCreate(int direction0, Vec2 position, Vec2 positionXY)
{
    auto mapscene = dynamic_cast<T*>(dynamic_cast<Layer*>(this->getParent())->getParent());
    switch (this->type)
    {
        case aiyafala: {
            auto aiyafala0 = Aiyafala::createSprite(StringUtils::format(".\\employee\\aiyafala\\aiyafala%d.png", ((direction0 == left || direction0 == front) ? (1) : (2))).c_str(), direction0, position, positionXY);
            aiyafala0->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEmployeeInMap.pushBack(aiyafala0);
            AudioEngine::play2d(".\\employee\\aiyafala\\putting.mp3");
            mapscene->addChild(aiyafala0); }
            break;
        case xingxiong: {
            auto xingxiong0 = Xingxiong::createSprite(StringUtils::format(".\\employee\\xingxiong\\xingxiong%d.png", ((direction0 == left || direction0 == front) ? (1) : (2))).c_str(), direction0, position, positionXY);
            xingxiong0->setAnchorPoint(Vec2(0.5f, 0.25f));
            MapInformation::getInstance()->allEmployeeInMap.pushBack(xingxiong0);
            AudioEngine::play2d(".\\employee\\xingxiong\\putting.mp3");
            mapscene->addChild(xingxiong0); }
            break;
    }
    mapscene->setRemainPuttingNumber(mapscene->getRemainPuttingNumber() - 1);
    int realFee = this->getFee() + (this->getReputNum() >= 2 ? (this->getFee()) : (this->getReputNum() == 1 ? (this->getFee() / 2) : (0)));
    mapscene->setC(mapscene->getC() - realFee);

}

template<class T>
void employeeList<T>::update(float dt)
{

}

template<class T>
void employeeList<T>::reputUpdate(float dt)
{
    auto progress = (ProgressTimer*)(this->getChildByTag(2));
    reputTimeNow -= 0.1f;
    progress->setPercentage(reputTimeNow / reputTime * 100);
    if (progress->getPercentage() <= 0)
    {
        unschedule(CC_SCHEDULE_SELECTOR(employeeList<T>::reputUpdate));
        this->removeChildByTag(1);
        this->removeChildByTag(2);
        this->setOpacity(255);
    }
}

template<class T>
void employeeList<T>::frontChooseCallback(cocos2d::Ref* pSender)
{
    auto puttingLayer = dynamic_cast<Layer*>(this->getParent());
    puttingLayer->removeChildByTag(100);    
    puttingLayer->removeChildByTag(102);
    puttingLayer->removeChildByTag(103);

    auto replace = dynamic_cast<Sprite*>(puttingLayer->getChildByTag(101));
    auto positionXYsaveing= dynamic_cast<Sprite*>(this->getChildByTag(0));
    this->employeeCreate(front, replace->getPosition(), positionXYsaveing->getPosition());
    replace->removeFromParent();
    positionXYsaveing->removeFromParent();
}

template<class T>
void employeeList<T>::backChooseCallback(cocos2d::Ref* pSender)
{
    auto puttingLayer = dynamic_cast<Layer*>(this->getParent());
    puttingLayer->removeChildByTag(100);
    puttingLayer->removeChildByTag(102);
    puttingLayer->removeChildByTag(103);

    auto replace = dynamic_cast<Sprite*>(puttingLayer->getChildByTag(101));
    auto positionXYsaveing = dynamic_cast<Sprite*>(this->getChildByTag(0));
    this->employeeCreate(Back, replace->getPosition(), positionXYsaveing->getPosition());
    replace->removeFromParent();
    positionXYsaveing->removeFromParent();
}

template<class T>
void employeeList<T>::leftChooseCallback(cocos2d::Ref* pSender)
{
    auto puttingLayer = dynamic_cast<Layer*>(this->getParent());
    puttingLayer->removeChildByTag(100);
    puttingLayer->removeChildByTag(102);
    puttingLayer->removeChildByTag(103);

    auto replace = dynamic_cast<Sprite*>(puttingLayer->getChildByTag(101));
    auto positionXYsaveing = dynamic_cast<Sprite*>(this->getChildByTag(0));
    this->employeeCreate(left, replace->getPosition(), positionXYsaveing->getPosition());
    replace->removeFromParent();
    positionXYsaveing->removeFromParent();
}

template<class T>
void employeeList<T>::rightChooseCallback(cocos2d::Ref* pSender)
{
    auto puttingLayer = dynamic_cast<Layer*>(this->getParent());
    puttingLayer->removeChildByTag(100);
    puttingLayer->removeChildByTag(102);
    puttingLayer->removeChildByTag(103);

    auto replace = dynamic_cast<Sprite*>(puttingLayer->getChildByTag(101));
    auto positionXYsaveing = dynamic_cast<Sprite*>(this->getChildByTag(0));
    this->employeeCreate(right, replace->getPosition(), positionXYsaveing->getPosition());
    replace->removeFromParent();
    positionXYsaveing->removeFromParent();
}

template<class T>
void employeeList<T>::giveupChooseCallback(cocos2d::Ref* pSender)
{
    auto puttingLayer = dynamic_cast<Layer*>(this->getParent());
    puttingLayer->removeChildByTag(100);
    puttingLayer->removeChildByTag(101);
    puttingLayer->removeChildByTag(102);
    puttingLayer->removeChildByTag(103);
    this->setOpacity(255);
    this->setIsadded(false);
    this->removeChildByTag(0);
}

/*template<class T>
bool employeeList<T>::onTouchBegan(Touch* touch, Event* event)
{
    if (map1->getC() >= this->fee && map1->getRemainPuttingNumber() > 0 && Rect(this->getPosition().x, this->getPosition().y, this->move->getContentSize().width, this->move->getContentSize().height).containsPoint(touch->getLocation()))
    {
        auto target = static_cast<employeeList*>(event->getCurrentTarget());
        target->retain();
        auto puttingLayer = dynamic_cast<Layer*>(target->getParent());
        target->removeFromParent();


        target->move->setPosition(touch->getLocation());
        puttingLayer->addChild(target->move);

        //target->isSelected = true;
        return true;
    }
    return false;
}

template<class T>
void employeeList<T>::onTouchMoved(Touch* touch, Event* event)
{
    auto target = static_cast<employeeList*>(event->getCurrentTarget());
    target->move->setPosition(touch->getLocation());

}*/

/*template<class T>
void employeeList<T>::onMouseDown(Event* event)
{
    EventMouse* e = (EventMouse*)event;
    if (map1->getC() >= this->fee && map1->getRemainPuttingNumber() > 0 && Rect(this->getPosition().x, this->getPosition().y,this->move->getContentSize().width, this->move->getContentSize().height).containsPoint(Vec2(e->getCursorX(), e->getCursorY())))
    {
        this->retain();
        auto puttingLayer= dynamic_cast<Layer*>(this->getParent());
        this->removeFromParent();
        
        
        this->move->setPosition(Vec2(e->getCursorX(), e->getCursorY()));
        puttingLayer->addChild(this->move);

        isSelected = true;
        
    }
}

template<class T>
void employeeList<T>::onMouseUp(Event* event)
{
    
}

template<class T>
void employeeList<T>::onMouseMove(Event* event) 
{
    
    if (isSelected)
    {
        EventMouse* e = (EventMouse*)event;
        this->move->setPosition(Vec2(e->getCursorX(), e->getCursorY()));
        AllocConsole();
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        log("fuck2");
    }
}*/