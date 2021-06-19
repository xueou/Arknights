#include "Employee.h"
#include "MapInformation.h"
#include "Range.h"

bool Employee::initWithFile(const char* filename)
{
    if (!Sprite::initWithFile(filename))
    {
        return false;
    }
    setLastState(employeeStateNone);
    setPresentState(employeeStateStart);

    loadingBlood();
    loadingSP();
    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate),1.0f);

    return true;
}

void Employee::initAnimation()
{
    this->start1 = Employee::createAnimate(1, name.c_str(), "start", startNum, 1, 0.04f);
    this->start2 = Employee::createAnimate(2, name.c_str(), "start", startNum, 1, 0.04f);
    this->attack1 = Employee::createAnimate(1, name.c_str(), "attack", attackNum, -1, attrackInterval / attackNum);
    this->attack2 = Employee::createAnimate(2, name.c_str(), "attack", attackNum, -1, attrackInterval/ attackNum);
    this->idle1 = Employee::createAnimate(1, name.c_str(), "idle", idleNum, -1, 0.04f);
    this->idle2 = Employee::createAnimate(2, name.c_str(), "idle", idleNum, -1, 0.04f);
    this->die1 = Employee::createAnimate(1, name.c_str(), "die", dieNum, 1, 0.04f);
    this->die2 = Employee::createAnimate(2, name.c_str(), "die", dieNum, 1, 0.04f);
    start1->retain();
    start2->retain();
    attack1->retain();
    attack2->retain();
    idle1->retain();
    idle2->retain();
    die1->retain();
    die2->retain();

    /*ValueMap info;
    info["FrameId"] = Value(StringUtils::format("Frame%d", startNum));
    start1->getFrames().at(startNum - 1)->setUserInfo(info);
    start2->getFrames().at(startNum - 1)->setUserInfo(info);
    auto _employeeStateStartListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
        {
            auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
            this->presentState = employeeStateIdle;
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_employeeStateStartListener, this);*/

    ValueMap info2;
    info2["FrameId"] = Value(StringUtils::format("Frame%d", attackReachNum));
    attack1->getFrames().at(attackReachNum - 1)->setUserInfo(info2);
    attack2->getFrames().at(attackReachNum - 1)->setUserInfo(info2);
    auto _employeeStateAttackListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
        {
            auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
            attrackSelectedEnemy();
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_employeeStateAttackListener, this);

    //ValueMap info3;
    //info3["FrameId"] = Value(StringUtils::format("Frame%d", dieNum));   
    //die1->getFrames().at(dieNum - 1)->setUserInfo(info3);
    //die2->getFrames().at(dieNum - 1)->setUserInfo(info3);
    //auto _employeeStateDieListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
       // {
           // auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
            /*************干员死亡**************/
            //auto map = dynamic_cast<MapScene*>(this->getParent());
            //this->removeFromParent();
            //auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
            //auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

           // map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
            /*******************再部署时间******************/
            //employeelist->setOpacity(255);
            //employeelist->setIsadded(false);
            //employeelist->setReputNum(employeelist->getReputNum() + 1);
       // });
   // _eventDispatcher->addEventListenerWithSceneGraphPriority(_employeeStateDieListener, this);
}

void Employee::releaseAnimation()
{
    start1->release();
    start2->release();
    attack1->release();
    attack2->release();
    idle1->release();
    idle2->release();
    die1->release();
    die2->release();
}

void Employee::loadingBlood()
{
    auto bar = Sprite::create("gray.png");
    bar->setAnchorPoint(Vec2(0.5f, 1.0f));
    bar->setPosition(Vec2(this->getContentSize().width / 2.0f, this->getContentSize().height / 4.5f));
    this->addChild(bar);
    bar->setGlobalZOrder(100);

    auto blood = Sprite::create("blue.png");
    auto progress = ProgressTimer::create(blood);
    progress->setType(ProgressTimer::Type::BAR);
    progress->setAnchorPoint(Vec2(0.5f, 1.0f));
    progress->setPosition(Vec2(this->getContentSize().width / 2.0f, this->getContentSize().height / 4.5f));

    progress->setMidpoint(Vec2(0.f, 0.5f));
    progress->setBarChangeRate(Point(1, 0));
    progress->setTag(50);
    this->addChild(progress);
    progress->setGlobalZOrder(101);

    schedule(CC_SCHEDULE_SELECTOR(Employee::bloodUpdate));
}

void Employee::loadingSP()
{
    auto bar2 = Sprite::create("gray.png");
    bar2->setAnchorPoint(Vec2(0.5f, 1.0f));
    bar2->setPosition(Vec2(this->getContentSize().width / 2.0f, this->getContentSize().height / 4.5f - bar2->getContentSize().height));
    this->addChild(bar2);
    bar2->setGlobalZOrder(100);

    auto sp = Sprite::create("green.png");
    auto progress2 = ProgressTimer::create(sp);
    progress2->setType(ProgressTimer::Type::BAR);
    progress2->setAnchorPoint(Vec2(0.5f, 1.0f));
    progress2->setPosition(Vec2(this->getContentSize().width / 2.0f, this->getContentSize().height / 4.5f - bar2->getContentSize().height));

    progress2->setMidpoint(Vec2(0.f, 0.5f));
    progress2->setBarChangeRate(Point(1, 0));
    progress2->setTag(51);
    this->addChild(progress2);
    progress2->setGlobalZOrder(101);

    schedule(CC_SCHEDULE_SELECTOR(Employee::spUpdate));
}

void Employee::choosingMin(Enemy* p)
{
    float length=0.0f;
    int deltaPoint=0;
    int index;
    for (Enemy* m : this->selectedEnemy)
        if ((m->pointNum-m->pointNow) > deltaPoint || ((m->pointNum - m->pointNow) == deltaPoint &&getLength((m->positionArray[m->pointNow+1] - m->getPosition())) > length))
        {
            length = getLength((m->positionArray[m->pointNow + 1] - m->getPosition()));
            deltaPoint = m->pointNum - m->pointNow;
            index = this->selectedEnemy.getIndex(m);
        }
    if ((p->pointNum - p->pointNow) < deltaPoint ||((p->pointNum - p->pointNow) == deltaPoint && getLength((p->positionArray[p->pointNow + 1] - p->getPosition())) < length))
    {
        this->selectedEnemy.replace(index, p);
    }
}

Animation* Employee::createAnimate(int direction, const char* name, const char* action, int num, int loop, float delayPerUnit)
{
    /*auto m_frameCache = SpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile(StringUtils::format(".\\employee\\%s\\%s.plist", name, name), StringUtils::format(".\\employee\\%s\\%s.pvr.ccz.pvr.ccz", name, name));
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    log(StringUtils::format(".\\employee\\%s\\%s.plist", name, name).c_str());
    Vector<SpriteFrame*> frameArray;
    for (int i = 1; i <= num; i++)
    {
        auto* frame = m_frameCache->getSpriteFrameByName(StringUtils::format("%s%d (%d).png", action, direction, i));
        log(StringUtils::format("%s%d (%d).png", action, direction, i).c_str());
        frameArray.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(loop);
    animation->setDelayPerUnit(delayPerUnit);*/
    Vector<SpriteFrame*> frameArray;
    for (int i = 1; i <= num; i++)
    {
        auto* frame = SpriteFrame::create(StringUtils::format(".\\employee\\%s\\%s%d\\%s%d (%d).png", name, action, direction, action, direction, i), Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        frame->setAnchorPoint(Vec2(0.5f, 0.25f));
        frameArray.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(loop);
    animation->setDelayPerUnit(delayPerUnit);

    return animation;
}

void Employee::attrackSelectedEnemy()
{
    for (Enemy* p : this->selectedEnemy)
    {
        /*AllocConsole();
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        log("attrack %d", this->attrack);
        log("defend %d", p->getDefend());
        log("index %d", MapInformation::getInstance()->allEnemyInMap.getIndex(p));
        log("health1: %d", p->getHealth());*/
        if (damageType == magical)
        {
            p->setHealth(p->getHealth() - this->attrack * (100 - p->getMagicDefend()) / 100);
        }
        else if (damageType == phisical)
        {
            if (this->attrack - p->getDefend() > this->attrack * 5 / 100)
                p->setHealth(p->getHealth() - (this->attrack - p->getDefend()));
            else
                p->setHealth(p->getHealth() - this->attrack * 5 / 100);
        }
        
        //log("health2: %d", p->getHealth());
    }
    
}

bool Employee::searchEnemy()
{
    switch (attrackRange)
    {
        case DANFA:
            return this->searchEnemyByType(danfa[direction0],danfaRange);
    }
    return false;
}

bool Employee::searchEnemyByType(Vec2 range[12], int rangeNum)
{
    this->selectedEnemy.clear();
    for (Enemy* enemy0: MapInformation::getInstance()->allEnemyInMap)  //此处虽然多重for嵌套，但实际上在游戏本身的机制模式下
    {                                                                  //每层循环的量级很小，总计循环次数最多时仅约几百次
        if (enemy0->getIsadded() == true)
        {                        
            if (enemy0->getPositionType() == this->selectedType || this->selectedType == upanddown)
            {
                for (int i = 0, added = 0; i < rangeNum && added == 0; i++)
                {
                    for (Vec2 p : enemy0->positionXYNow)
                        if (range[i] + this->positionXY == p)
                        {
                            if (this->selectedEnemy.size() < attrackNumber)
                            {
                                this->selectedEnemy.pushBack(enemy0);
                            }
                            else
                            {
                                choosingMin(enemy0);
                            }
                            added = 1;
                            break;
                        }
                }
            }
            else if (this->selectedType == upthandown)//只考虑了单体狙的情况
            {
                for (int i = 0, added = 0; i < rangeNum && added == 0; i++)
                {
                    for (Vec2 p : enemy0->positionXYNow)
                        if (range[i] + this->positionXY == p)
                        {
                            if (this->selectedEnemy.size() ==0)
                            {
                                this->selectedEnemy.pushBack(enemy0);
                            }
                            else if (this->selectedEnemy.at(0)->getPositionType()==down && enemy0->getPositionType() == up)
                            {
                                this->selectedEnemy.replace(0, enemy0);
                            }
                            else if(!(this->selectedEnemy.at(0)->getPositionType() == up && enemy0->getPositionType() == down))
                            {
                                choosingMin(enemy0);
                            }
                            added = 1;
                            break;
                        }
                }
            }
        }
    }
    
    if (this->selectedEnemy.size() == 0)
        return false;
    else
        return true;
}

int Employee::getEmployeeListType()                /***************记得补全**************/
{
    if (name == "aiyafala")
        return 1;
}

void Employee::addSkillList()
{
    auto p = Sprite::create("greensquare.png");
    p->setAnchorPoint(Vec2(0.5f, 0.5f));
    p->setOpacity(0);
    p->setPosition(Vec2::ZERO);
    this->addChild(p);

    auto _addSkillListListener = EventListenerTouchOneByOne::create();
    _addSkillListListener->setSwallowTouches(true);
    _addSkillListListener->onTouchBegan = [=](Touch* touch, Event* event)
    {       
        return true; 
    };
    _addSkillListListener->onTouchEnded = [this](Touch* touch, Event* event)
    {
        auto m = Sprite::create("greensquare.png");
        if (Rect(this->getPosition().x - m->getContentSize().width / 2.0f, this->getPosition().y - m->getContentSize().height / 2.0f,
            m->getContentSize().width, m->getContentSize().height).containsPoint(touch->getLocation()))
        {
            auto visibleSize = Director::getInstance()->getVisibleSize();
            auto map = dynamic_cast<MapScene*>(this->getParent());
            
            auto covering = Sprite::create();//遮盖层，吞没其他点击，单击时返回
            covering->setContentSize(visibleSize);
            auto listener0 = EventListenerTouchOneByOne::create();
            listener0->setSwallowTouches(true);
            listener0->onTouchBegan = [=](Touch* touch, Event* event) {return true; };
            listener0->onTouchEnded = [this](Touch* touch, Event* event) {
                auto map= dynamic_cast<MapScene*>(this->getParent());
                unschedule(CC_SCHEDULE_SELECTOR(Employee::skillButtonUpdate));
                map->removeChildByTag(200);
                map->removeChildByTag(201);
                map->removeChildByTag(202);
                map->removeChildByTag(203);
                map->removeChildByTag(204);
            };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener0, covering);
            map->addChild(covering, 491, 200);

            auto border2 = Sprite::create("border2.png");
            border2->setPosition(this->getPosition());
            border2->setOpacity(200);
            auto listener1 = EventListenerTouchOneByOne::create();
            listener1->setSwallowTouches(true);
            listener1->onTouchBegan = [this](Touch* touch, Event* event) {
                auto border0 = Sprite::create("border2.png");
                if (Rect(this->getPosition().x - border0->getContentSize().width / 2.0f, this->getPosition().y - border0->getContentSize().height / 2.0f,
                    border0->getContentSize().width, border0->getContentSize().height).containsPoint(touch->getLocation()))
                {
                    return true;
                }
                else
                    return false;
            };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, border2);
            map->addChild(border2, 492, 201);

            auto retreat = Sprite::create("retreat.png");
            retreat->setPosition(this->getPosition() + Vec2(-border2->getContentSize().width / 3.8f, border2->getContentSize().height / 3.8f));
            auto listener2 = EventListenerTouchOneByOne::create();
            listener2->setSwallowTouches(true);
            listener2->onTouchBegan = [retreat](Touch* touch, Event* event) {
                if (Rect(retreat->getPosition().x - retreat->getContentSize().width / 2.0f, retreat->getPosition().y - retreat->getContentSize().height / 2.0f,
                    retreat->getContentSize().width, retreat->getContentSize().height).containsPoint(touch->getLocation()))
                    return true;
                else
                    return false;
            };
            listener2->onTouchEnded = [this](Touch* touch, Event* event) {
                auto map = dynamic_cast<MapScene*>(this->getParent());
                unschedule(CC_SCHEDULE_SELECTOR(Employee::skillButtonUpdate));
                map->removeChildByTag(200);
                map->removeChildByTag(201);
                map->removeChildByTag(202);
                map->removeChildByTag(203);
                map->removeChildByTag(204);
                /***********************干员 撤退*****************************/
                this->removeFromParent();
                auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
                auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));
                
                int m = map->getC() + (employeelist->getFee() + (employeelist->getReputNum() >= 2 ? (employeelist->getFee()) : (employeelist->getReputNum() == 1 ? (employeelist->getFee() / 2) : (0)))) / 2;
                map->setC((m) > 99 ? (99) : (m));
                map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
                /*******************再部署时间******************/
                employeelist->reputtingLoading();

                employeelist->setOpacity(100);
                employeelist->setIsadded(false);
                employeelist->setReputNum(employeelist->getReputNum() + 1);
            };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, retreat);
            map->addChild(retreat, 493, 202);

            auto skillbackground = Sprite::create(StringUtils::format(".\\employee\\%s\\skill.png", name.c_str()));
            auto skill = Sprite::create(StringUtils::format(".\\employee\\%s\\skill.png", name.c_str()));
            skillbackground->setOpacity(100);
            skillbackground->setPosition(this->getPosition() + Vec2(border2->getContentSize().width / 4.8f, -border2->getContentSize().height / 4.8f));
            auto listener3 = EventListenerTouchOneByOne::create();
            listener3->setSwallowTouches(true);
            listener3->onTouchBegan = [this,skillbackground](Touch* touch, Event* event) {
                if (Rect(skillbackground->getPosition().x - skillbackground->getContentSize().width / 2.0f, skillbackground->getPosition().y - skillbackground->getContentSize().height / 2.0f,
                    skillbackground->getContentSize().width, skillbackground->getContentSize().height).containsPoint(touch->getLocation())&&this->sp==this->spMAX)
                    return true;
                else
                    return false;
            };
            listener3->onTouchEnded = [this](Touch* touch, Event* event) {
                auto map = dynamic_cast<MapScene*>(this->getParent());
                unschedule(CC_SCHEDULE_SELECTOR(Employee::skillButtonUpdate));
                map->removeChildByTag(200);
                map->removeChildByTag(201);
                map->removeChildByTag(202);
                map->removeChildByTag(203);
                map->removeChildByTag(204);
                /***********************释放技能*****************************/
                this->skill();
            };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, skillbackground);
            map->addChild(skillbackground, 493, 203);
            auto progress = ProgressTimer::create(skill);
            progress->setType(ProgressTimer::Type::BAR);
            progress->setPosition(this->getPosition() + Vec2(border2->getContentSize().width / 4.8f, -border2->getContentSize().height / 4.8f));
            progress->setMidpoint(Vec2(0.5f, 0.f));
            progress->setBarChangeRate(Point(0, 1));
            progress->setTag(50);
            map->addChild(progress,494,204);
            
            schedule(CC_SCHEDULE_SELECTOR(Employee::skillButtonUpdate));
            
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_addSkillListListener, p);
}

void Employee::spUpdate(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(51);
    progress->setPercentage((static_cast<float>(sp) / spMAX) * 100);
}

void Employee::skillButtonUpdate(float dt)
{
    auto map = dynamic_cast<MapScene*>(this->getParent());
    auto progress = (ProgressTimer*)map->getChildByTag(204);
    progress->setPercentage((static_cast<float>(sp) / spMAX) * 100);
}

void Employee::spIncreaseUpdate(float dt)
{
    if (sp < spMAX)
        sp++;
}

void Employee::bloodUpdate(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(50);
    progress->setPercentage((static_cast<float>(health) / healthMAX) * 100);
}

void Employee::stateUpdate(float dt)
{
    if (this->getPresentState() != employeeStateStart && this->getPresentState() != employeeStateDie)
    {
        if (this->health <= 0)
            this->setPresentState(employeeStateDie);
        else if (searchEnemy())
            this->setPresentState(employeeStateAttack);
        else
            this->setPresentState(employeeStateIdle);
    }
}

void Employee::update(float dt)
{
    if (lastState != presentState)
    {        
        switch (presentState)
        {
            case employeeStateStart: {
                //ValueMap info;
                //info["FrameId"] = Value(StringUtils::format("Frame%d",startNum));
                auto animation0 = Animate::create((direction0 == left || direction0 == front) ? (start1) : (start2));
                //animation->getFrames().at(startNum-1)->setUserInfo(info);
                auto callbackStart = CallFunc::create([this]() {
                    this->presentState = employeeStateIdle;
                    });
                auto animation = Sequence::create(animation0, callbackStart, nullptr);
                animation->setTag(employeeStateStart);
                this->runAction(animation);
                
                /*auto _employeeStateStartListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
                    {
                        auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
                        this->presentState = employeeStateIdle;
                    });
                _eventDispatcher->addEventListenerWithSceneGraphPriority(_employeeStateStartListener, this);*/ }
                break;
            case employeeStateIdle: {
                this->stopActionByTag(lastState);
                //_eventDispatcher->removeEventListenersForTarget(this);

                //_eventDispatcher->removeAllEventListeners();
                auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
                animation->setTag(employeeStateIdle);
                this->runAction(animation); }
                break;
            case employeeStateAttack: {
                this->stopActionByTag(lastState);
                //_eventDispatcher->removeAllEventListeners();
                //_eventDispatcher->removeEventListenersForTarget(this);
                //ValueMap info;
                //info["FrameId"] = Value(StringUtils::format("Frame%d", attackReachNum));
                //auto animation0 = (direction0 == left || direction0 == front) ? (attack1) : (attack2);
                //animation0->getFrames().at(attackReachNum - 1)->setUserInfo(info);
                auto animation = Animate::create((direction0 == left || direction0 == front) ? (attack1) : (attack2));
                animation->setTag(employeeStateAttack);
                this->runAction(animation); 
            
                /*auto _employeeStateAttackListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
                    {
                        auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
                        attrackSelectedEnemy();
                        
                    });                
                _eventDispatcher->addEventListenerWithSceneGraphPriority(_employeeStateAttackListener, this);*/ }
                break;            
            case employeeStateDie: {
                this->stopAllActions();
                //_eventDispatcher->remove
                //ValueMap info;
                //info["FrameId"] = Value(StringUtils::format("Frame%d", dieNum));
                //auto animation0 = (direction0 == left || direction0 == front) ? (die1) : (die2);
                //animation0->getFrames().at(dieNum - 1)->setUserInfo(info);
                auto animation = Animate::create((direction0 == left || direction0 == front) ? (die1) : (die2));
                auto callbackDie = CallFunc::create([this]() {
                    auto map = dynamic_cast<MapScene*>(this->getParent());
                    this->removeFromParent();
                    auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
                    auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

                    map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
                    /*******************再部署时间******************/
                    employeelist->reputtingLoading();

                    employeelist->setOpacity(100);
                    employeelist->setIsadded(false);
                    employeelist->setReputNum(employeelist->getReputNum() + 1);
                    });
                this->runAction(Sequence::create(animation, callbackDie, nullptr));

                /*auto _employeeStateDieListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
                    {
                        auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());

                    });
                _eventDispatcher->addEventListenerWithSceneGraphPriority(_employeeStateDieListener, this);*/ }
                break;
        }
        lastState = presentState;
    }
}

bool Aiyafala::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "aiyafala";
    healthMAX = 1743;
    health = 1743;
    spMAX = 80;
    sp = 70;
    attrack = 914;
    defend = 122;
    magicDefend = 20;
    blockNumber = 1;
    remainBlockNumber = 1;
    attrackNumber = 1;
    attrackSpeed = 100;
    attrackRange = DANFA;
    attrackInterval = 1.6f;
    skillTime = 15.0f;
    positionType = up;
    damageType = magical;
    selectedType = upanddown;
    attackNum = 24;
    dieNum = 16;
    idleNum = 45;
    startNum = 16;
    attackReachNum = 18;
    //技能参数不同干员需要哪些单独初始化
    beforeskillNum = 21;
    duringskillNum = 24;
    afterskillNum = 78;
    /***********************************/
    
    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

    return true;
}

Aiyafala* Aiyafala::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Aiyafala::create(filename);
    
    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;
    
    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Aiyafala::initSkillAnimation()
{
    this->beforeskill1 = Employee::createAnimate(1, name.c_str(), "beforeskill", beforeskillNum, 1, 0.04f);
    this->beforeskill2 = Employee::createAnimate(2, name.c_str(), "beforeskill", beforeskillNum, 1, 0.04f);
    this->duringskill1 = Employee::createAnimate(1, name.c_str(), "duringskill", duringskillNum, 12, 0.04f);
    this->duringskill2 = Employee::createAnimate(2, name.c_str(), "duringskill", duringskillNum, 12, 0.04f);
    this->afterskill1 = Employee::createAnimate(1, name.c_str(), "afterskill", afterskillNum, 1, 0.04f);
    this->afterskill2 = Employee::createAnimate(2, name.c_str(), "afterskill", afterskillNum, 1, 0.04f);
    beforeskill1->retain();
    beforeskill2->retain();
    duringskill1->retain();
    duringskill2->retain();
    afterskill1->retain();
    afterskill2->retain();
}


void Aiyafala::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    unscheduleUpdate();

    attrack = 1905;
    attrackNumber = 6;
    attrackInterval = 0.5f;
    this->stopAllActions();
    auto animation1 = Animate::create((direction0 == left || direction0 == front) ? (beforeskill1) : (beforeskill2));
    auto animation2 = Animate::create((direction0 == left || direction0 == front) ? (duringskill1) : (duringskill2));
    auto animation3 = Animate::create((direction0 == left || direction0 == front) ? (afterskill1) : (afterskill2));
    auto animation = Sequence::create(animation1, animation2, animation3, nullptr);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillSPUpdate),0.1875f);
    schedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillAttrackUpdate), attrackInterval);
    schedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillHealthUpdate));

    scheduleOnce(CC_SCHEDULE_SELECTOR(Aiyafala::skillOverUpdate),15.0f);
}

void Aiyafala::update(float dt)
{
    Employee::update(dt);
}

void Aiyafala::skillSPUpdate(float dt)
{
    if (sp > 0)
        sp--;
}

void Aiyafala::skillAttrackUpdate(float dt)
{
    if (searchEnemyByType(huoshan, huoshanRange))
        attrackSelectedEnemy();
}

void Aiyafala::skillHealthUpdate(float dt)
{
    if (health <= 0)
    {
        this->stopAllActions();
        auto animation = Animate::create((direction0 == left || direction0 == front) ? (die1) : (die2));
        this->runAction(animation);
    }
}

void Aiyafala::skillOverUpdate(float dt)
{
    attrack = 914;
    attrackNumber = 1;
    attrackInterval = 1.6f;

    unschedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillSPUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillAttrackUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillHealthUpdate));

    beforeskill1->release();
    beforeskill2->release();
    duringskill1->release();
    duringskill2->release();
    afterskill1->release();
    afterskill2->release();

    lastState = employeeStateIdle;
    presentState = employeeStateIdle;
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
    animation->setTag(employeeStateIdle);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate),1.0f);
    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();
    
}