#include "Enemy.h"
#include "MapInformation.h"

bool Enemy::initWithFile(const char* filename)             /********************销毁敌人时记得release所有动作********************/
{ 
    if (!Sprite::initWithFile(filename))                        /******！！！！！！！！！**********************************/
    {
        return false;
    }
    setLastState(enemyStateNone);
    setPresentState(enemyStateNone);
    /*AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    log("fuck");*/
    

    return true;
}

void Enemy::loadingBlood()
{
    auto bar = Sprite::create("gray.png");
    bar->setAnchorPoint(Vec2(0.5f, 1.0f));
    bar->setPosition(Vec2(this->getContentSize().width / 2.0f, this->getContentSize().height / 4.5f));
    this->addChild(bar);
    bar->setGlobalZOrder(100);

    auto blood = Sprite::create("red.png");
    auto progress = ProgressTimer::create(blood);
    progress->setType(ProgressTimer::Type::BAR); 
    progress->setAnchorPoint(Vec2(0.5f, 1.0f));
    progress->setPosition(Vec2(this->getContentSize().width / 2.0f, this->getContentSize().height / 4.5f));
    
    progress->setMidpoint(Vec2(0.f, 0.5f)); 
    progress->setBarChangeRate(Point(1, 0));
    progress->setTag(MapInformation::getInstance()->allEnemyInMap.getIndex(this));
    this->addChild(progress);
    progress->setGlobalZOrder(101);

    schedule(CC_SCHEDULE_SELECTOR(Enemy::bloodUpdate));
}

void Enemy::getIsBlockedBy(Employee* p)
{
    this->isBlockedBy = p;
}

void Enemy::initAnimation()
{
    this->move1 = Enemy::createAnimate(1, name.c_str(), "move", moveNum, -1, 0.04f);
    this->move2 = Enemy::createAnimate(2, name.c_str(), "move", moveNum, -1, 0.04f);
    this->attack1keep = Enemy::createAnimate(1, name.c_str(), "attack", attackNum, 1, attrackInterval / attackNum);
    this->attack2keep = Enemy::createAnimate(2, name.c_str(), "attack", attackNum, 1, attrackInterval / attackNum);
    this->attack1once = Enemy::createAnimate(1, name.c_str(), "attack", attackNum, 1, 0.04f);
    this->attack2once = Enemy::createAnimate(2, name.c_str(), "attack", attackNum, 1, 0.04f);
    this->idle1 = Enemy::createAnimate(1, name.c_str(), "idle", idleNum, -1, 0.04f);
    this->idle2 = Enemy::createAnimate(2, name.c_str(), "idle", idleNum, -1, 0.04f);
    this->die1 = Enemy::createAnimate(1, name.c_str(), "die", dieNum, 1, 0.04f);
    this->die2 = Enemy::createAnimate(2, name.c_str(), "die", dieNum, 1, 0.04f);
    move1->retain();
    move2->retain();
    attack1keep->retain();
    attack2keep->retain();
    attack1once->retain();
    attack2once->retain();
    idle1->retain();
    idle2->retain();
    die1->retain();
    die2->retain();

    
    /*ValueMap info8;
    info8["FrameId"] = Value(StringUtils::format("Frame%d", dieNum));
    die1->getFrames().at(dieNum - 1)->setUserInfo(info8);
    die2->getFrames().at(dieNum - 1)->setUserInfo(info8);
    auto _enemyStateDieListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
        {
            auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
            auto topUpdate1 = "topUpdate1";
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("topUpdate1", static_cast<void*>(&topUpdate1));

            this->removeFromParent();
            this->setIsadded(false);
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_enemyStateDieListener, this);*/
}

bool Enemy::searchEmployee()
{
    this->selectedEmployee.clear();
    int index = -1;   
    float singleSquareLength = getLength((positionArray[pointNow + 1] - positionArray[pointNow])) / getLength((positionXYArray[pointNow + 1] - positionXYArray[pointNow]));
    float length = singleSquareLength * attrackR;
    for (Employee* employee0 : MapInformation::getInstance()->allEmployeeInMap)
    {
        if (getLength((employee0->getPosition() - this->positionNow)) < length)
        {
            length = getLength((employee0->getPosition() - this->positionNow));
            index = MapInformation::getInstance()->allEmployeeInMap.getIndex(employee0);
        }
    }
    if (index != -1) 
    {
        selectedEmployee.pushBack(MapInformation::getInstance()->allEmployeeInMap.at(index));
        return true;
    }
    else
        return false;
}

void Enemy::attrackBlocked()
{
    if (damageType == magical)
    {
        isBlockedBy->setHealth(isBlockedBy->getHealth() - this->attrack * (100 - isBlockedBy->getMagicDefend()) / 100);
    }
    else if (damageType == phisical)
    {
        if (this->attrack - isBlockedBy->getDefend() > this->attrack * 5 / 100)
            isBlockedBy->setHealth(isBlockedBy->getHealth() - (this->attrack - isBlockedBy->getDefend()));
        else
            isBlockedBy->setHealth(isBlockedBy->getHealth() - this->attrack * 5 / 100);
    }
}

void Enemy::attrackSelected(Employee* p)
{
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
}

void Enemy::releaseAnimation()
{
    move1->release();
    move2->release();
    attack1keep->release();
    attack2keep->release();
    attack1once->retain();
    attack2once->retain();
    idle1->release();
    idle2->release();
    die1->release();
    die2->release();
}

void Enemy::getPositionArray(Vec2 a[maxpositionarray], Vec2 b[maxpositionarray])
{
    for (int i = 0; i < maxpositionarray && (a[i] != Vec2::ZERO); i++)
    {
        positionArray[i] = a[i];
        positionXYArray[i] = b[i];
        pointNum++;
    }
}

void Enemy::getIntervalArray(float p[maxpositionarray])
{
    for (int i = 0; i < maxpositionarray; i++)
        interval[i] = p[i];
}

Animation* Enemy::createAnimate(int direction, const char* name, const char* action, int num, int loop, float delayPerUnit, float yPlus)
{
    /*auto m_frameCache = SpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile(StringUtils::format(".\\enemy\\%s\\%s.plist", name,name), StringUtils::format(".\\enemy\\%s\\%s.pvr.ccz.pvr.ccz", name, name));
    Vector<SpriteFrame*> frameArray;
    for (int i = 1; i <= num; i++)
    { 
        auto* frame = m_frameCache->getSpriteFrameByName(StringUtils::format("%s%d (%d).png", action, direction, i));
        frameArray.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(loop);
    animation->setDelayPerUnit(delayPerUnit);*/
    Vector<SpriteFrame*> frameArray;
    for (int i = 1; i <= num; i++)
    {
        auto* frame = SpriteFrame::create(StringUtils::format(".\\enemy\\%s\\%s%d\\%s%d (%d).png", name, action, direction,action, direction, i),Rect(0,0,this->getContentSize().width, this->getContentSize().height));
        frame->setAnchorPoint(Vec2(0.5f, 0.25f+yPlus));
        frameArray.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(loop);
    animation->setDelayPerUnit(delayPerUnit);

    return animation;
}

void Enemy::idleForInterval(float ddt)
{
    unschedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
    presentState = enemyStateIdle;

    scheduleOnce(CC_SCHEDULE_SELECTOR(Enemy::recoverPositionUpdate), ddt);
}

void Enemy::recoverPositionUpdate(float dt)
{
    schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
}

void Enemy::movingAttrackUpdate(float dt)
{
    if (searchEmployee())
    {
        /*if (isblocked == false)
        {
            stopActionByTag(enemyPingYi);
            stopActionByTag(enemyStateMove);
        }
        
        auto animation0 = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (attack1once) : (attack2once));
        auto callbackAttrack = CallFunc::create([this,goal]() {
            this->attrackSelected(goal);
            this->ismoving = false;
            this->setLastState(enemyStateNone);
            if(this->isblocked==true)
                this->setPresentState(enemyStateNone);
            });
        auto animation = Sequence::create(animation0, callbackAttrack, nullptr);
        this->runAction(animation);*/
        if (presentState == enemyStateIdle)
        {
            presentState = enemyStateAttackOnce;
        }
        else if (presentState == enemyStateMove)
        {
            this->stopActionByTag(enemyPingYi);
            presentState = enemyStateAttackOnce;
        }
    }
}

void Enemy::bloodUpdate(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(MapInformation::getInstance()->allEnemyInMap.getIndex(this));
    progress->setPercentage((static_cast<float>(health) / healthMAX) * 100);
    if (progress->getPercentage() <= 0) {
        this->unschedule(CC_SCHEDULE_SELECTOR(Enemy::bloodUpdate));
    }
    
}

void Enemy::positionUpdate(float dt)
{
    if (isadded)
    {
        if (isblocked == false && ismoving == false && pointNow < pointNum)
        {
            Vec2 realXY = positionArray[pointNow + 1] - positionNow;
            Vec2 theoryRealXY = positionArray[pointNow + 1] - positionArray[pointNow];
            Vec2 theorySquareNum = positionXYArray[pointNow + 1] - positionXYArray[pointNow];
            auto map1moveto1 = MoveTo::create(realSquareNum(realXY, theoryRealXY, theorySquareNum) / moveSpeed * 2, positionArray[pointNow + 1]);
            map1moveto1->setTag(enemyPingYi);
            this->runAction(map1moveto1);
            ismoving = true;
            presentState = enemyStateMove;
            /*auto move = Animate::create(move1);
            //auto move = Animate::create((Enemy::createAnimate(1, name.c_str(), "move", 23,-1,0.04f)));
            this->runAction(move);
            move->setTag(1);*/
        }
        positionNow = this->getPosition();
        if (positionNow == positionArray[pointNow + 1])
        {
            pointNow++;
            ismoving = false;
            presentState = enemyStateNone;

            if (withInterval == true)
            {
                if (interval[pointNow] != 0)
                {
                    idleForInterval(interval[pointNow]);
                }
            }
            //this->stopActionByTag(1);
            if (pointNow == pointNum)
            {
                auto topUpdate2 = "topUpdate2";
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("topUpdate2", static_cast<void*>(&topUpdate2));
                //MapInformation::getInstance()->allEnemyInMap.eraseObject(this);

                this->removeFromParent();
                this->setIsadded(false);
            }
        }
    }
}

void Enemy::positionXYUpdate(float dt)
{
    if (isadded)
    {
        positionXYNow.clear();
        int x1, x2, y1, y2, xNum = abs(static_cast<int>((positionXYArray[pointNow + 1] - positionXYArray[pointNow]).x)), yNum = abs(static_cast<int>((positionXYArray[pointNow + 1] - positionXYArray[pointNow]).y));
        Vec2 realXY = positionArray[pointNow + 1] - positionNow;
        Vec2 theoryRealXY = positionArray[pointNow + 1] - positionArray[pointNow];
        if (xNum == 0)
            x1 = x2 = static_cast<int>(positionXYArray[pointNow + 1].x);
        else
        {
            for (int i = 0; i <= xNum * 2; i++)
            {
                if ((2 * i - 1 <= realXY.x / theoryRealXY.x * xNum * 4) && (realXY.x / theoryRealXY.x * xNum * 4 < 2 * i + 1))
                {
                    if (i % 2 == 0)
                        x1 = x2 = static_cast<int>(positionXYArray[pointNow + 1].x) - i / 2 * (static_cast<int>((positionXYArray[pointNow + 1] - positionXYArray[pointNow]).x) > 0 ? (1) : (-1));
                    else
                    {
                        x1 = static_cast<int>(positionXYArray[pointNow + 1].x) - (i + 1) / 2 * (static_cast<int>((positionXYArray[pointNow + 1] - positionXYArray[pointNow]).x) > 0 ? (1) : (-1));
                        x2 = x1 + 1 * (static_cast<int>((positionXYArray[pointNow + 1] - positionXYArray[pointNow]).x) > 0 ? (1) : (-1));
                    }
                    break;
                }
            }
        }

        if (yNum == 0)
            y1 = y2 = static_cast<int>(positionXYArray[pointNow + 1].y);
        else
        {
            for (int i = 0; i <= yNum * 2; i++)
            {
                if ((2 * i - 1 <= realXY.y / theoryRealXY.y * yNum * 4) && (realXY.y / theoryRealXY.y * yNum * 4 < 2 * i + 1))
                {
                    if (i % 2 == 0)
                        y1 = y2 = static_cast<int>(positionXYArray[pointNow + 1].y) - i / 2 * (static_cast<int>((positionXYArray[pointNow + 1] - positionXYArray[pointNow]).y) > 0 ? (1) : (-1));
                    else
                    {
                        y1 = static_cast<int>(positionXYArray[pointNow + 1].y) - (i + 1) / 2 * (static_cast<int>((positionXYArray[pointNow + 1] - positionXYArray[pointNow]).y) > 0 ? (1) : (-1));
                        y2 = y1 + 1 * (static_cast<int>((positionXYArray[pointNow + 1] - positionXYArray[pointNow]).y) > 0 ? (1) : (-1));
                    }
                    break;
                }
            }
        }

        if (x1 == x2)
        {
            y1 == y2 ? (positionXYNow.push_back(Vec2(static_cast<float>(x1), static_cast<float>(y1)))) :
                (positionXYNow.push_back(Vec2(static_cast<float>(x1), static_cast<float>(y1))), positionXYNow.push_back(Vec2(static_cast<float>(x1), static_cast<float>(y2))));
        }
        else
        {
            y1 == y2 ? (positionXYNow.push_back(Vec2(static_cast<float>(x1), static_cast<float>(y1))), positionXYNow.push_back(Vec2(static_cast<float>(x2), static_cast<float>(y1)))) :
                (positionXYNow.push_back(Vec2(static_cast<float>(x1), static_cast<float>(y1))), positionXYNow.push_back(Vec2(static_cast<float>(x2), static_cast<float>(y1))), positionXYNow.push_back(Vec2(static_cast<float>(x1), static_cast<float>(y2))), positionXYNow.push_back(Vec2(static_cast<float>(x2), static_cast<float>(y2))));
        }
    }
}

void Enemy::stateUpdate(float dt)
{
    if (isadded)
    {
        if (this->getPresentState() != enemyStateDie)
        {
            if (this->health <= 0)
                this->setPresentState(enemyStateDie);
            else
            {
                if (this->onlyAttrackWhenBlocked == true)
                {
                    if (isblocked == true)
                    {
                        presentState = enemyStateAttackKeep;
                        stopActionByTag(enemyPingYi);
                    }
                }
                else
                {
                    if (isblocked == true && (lastState!= enemyStateAttackOnce))
                    {
                        presentState = enemyStateIdle;
                        if (lastState == enemyStateMove)
                            stopActionByTag(enemyPingYi);
                    }
                }
            }

        }
    }
}

void Enemy::update(float dt)
{
    if (isadded)
    {
        /*if (isblocked == false && ismoving == false && pointNow < pointNum)
        {
            Vec2 realXY = positionArray[pointNow + 1] - positionNow;
            Vec2 theoryRealXY = positionArray[pointNow + 1] - positionArray[pointNow];
            Vec2 theorySquareNum = positionXYArray[pointNow + 1] - positionXYArray[pointNow];
            auto map1moveto1 = MoveTo::create(realSquareNum(realXY, theoryRealXY, theorySquareNum) / moveSpeed * 2, positionArray[pointNow + 1]);
            this->runAction(map1moveto1);
            ismoving = true;

            auto move = Animate::create(move1);
            //auto move = Animate::create((Enemy::createAnimate(1, name.c_str(), "move", 23,-1,0.04f)));
            this->runAction(move);
            move->setTag(1);
        }
        positionNow = this->getPosition();
        if (positionNow == positionArray[pointNow + 1])
        {
            pointNow++;
            ismoving = false;
            this->stopActionByTag(1);
            if (pointNow == pointNum)
            {
                auto topUpdate2 = "topUpdate2";
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("topUpdate2", static_cast<void*>(&topUpdate2));
                //MapInformation::getInstance()->allEnemyInMap.eraseObject(this);
                
                this->removeFromParent();
                this->setIsadded(false);
            }
        }*/
        if (lastState != presentState)
        {           
            
            switch (presentState)
            {
                case enemyStateNone:
                    this->stopActionByTag(lastState);
                    break;
                case enemyStateIdle: {
                    if (lastState != enemyStateNone)
                        this->stopActionByTag(lastState);
                    auto animation = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (idle1) : (idle2));
                    animation->setTag(enemyStateIdle);
                    this->runAction(animation); }
                    break;
                case enemyStateMove: {
                    if(lastState!= enemyStateNone)
                        this->stopActionByTag(lastState);
                    auto animation = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (move1) : (move2));
                    animation->setTag(enemyStateMove);
                    this->runAction(animation); }
                    break;
                case enemyStateAttackOnce:{
                    if (lastState != enemyStateNone)
                        this->stopActionByTag(lastState);
                    auto animation0 = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (attack1once) : (attack2once));
                    auto callbackAttackOnce = CallFunc::create([this]() {
                        this->attrackSelected(selectedEmployee.at(0));
                        this->ismoving = false;
                        if (this->isblocked == true)
                            this->setPresentState(enemyStateIdle);
                        });
                    auto animation = Sequence::create(animation0, callbackAttackOnce, nullptr);
                    animation->setTag(enemyStateAttackOnce);
                    this->runAction(animation);}
                    break;
                case enemyStateAttackKeep: {
                    if (lastState != enemyStateNone)
                        this->stopActionByTag(lastState);
                    auto animation0 = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (attack1keep) : (attack2keep));
                    auto callbackAttackKeep = CallFunc::create([this]() {
                        this->attrackBlocked();
                        }); 
                    auto animation1 = Sequence::create(animation0, callbackAttackKeep, nullptr);
                    auto animation = RepeatForever::create(animation1);
                    animation->setTag(enemyStateAttackKeep);
                    this->runAction(animation); }
                    break;
                case enemyStateDie: {
                    this->stopAllActions();
                    //ValueMap info;
                    //info["FrameId"] = Value(StringUtils::format("Frame%d", dieNum));
                    auto animation0 = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (die1) : (die2));
                    //animation0->getFrames().at(dieNum - 1)->setUserInfo(info);
                    auto callbackDie = CallFunc::create([this]() {
                        auto topUpdate1 = "topUpdate1";
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("topUpdate1", static_cast<void*>(&topUpdate1));

                        if (isblocked == true)
                        {
                            this->isBlockedBy->deleteBlockedEnemy(this);
                            this->isBlockedBy->setRemainBlockNumber(this->isBlockedBy->getRemainBlockNumber() + this->blockNumber);
                        }

                        this->unscheduleAllCallbacks();
                        this->removeFromParent();
                        this->setIsadded(false);
                        });
                    auto animation = Sequence::create(animation0, callbackDie, nullptr);
                    this->runAction(animation);

                    /*auto _frameDisplayedListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
                        {
                            auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
                            auto topUpdate1 = "topUpdate1";
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("topUpdate1", static_cast<void*>(&topUpdate1));

                            this->removeFromParent();
                            this->setIsadded(false);
                        });
                    _eventDispatcher->addEventListenerWithSceneGraphPriority(_frameDisplayedListener, this);*/ }
                    break;
            }
            lastState = presentState;
        }

    }
}





bool shibing::initWithFile(const char* filename)
{
    if (!Enemy::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "shibing";
    healthMAX = 1650;
    health = 1650;
    attrack = 200;
    defend = 100;
    magicDefend = 0;
    blockNumber = 1;
    attrackSpeed = 100;
    attrackInterval = 2;
    moveSpeed = 1.1f;
    attrackR = 0.f;
    positionType = down;
    damageType = phisical;
    onlyAttrackWhenBlocked = true;
    isblocked = false;
    ismoving = false;
    attackNum = 26;
    dieNum = 18;
    idleNum = 17;
    moveNum = 23;
    attackReachNum = 15;
    /***********************************/
    
    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
    schedule(CC_SCHEDULE_SELECTOR(Enemy::positionXYUpdate));
    schedule(CC_SCHEDULE_SELECTOR(Enemy::stateUpdate));
    scheduleUpdate();

    if(onlyAttrackWhenBlocked==false)
        schedule(CC_SCHEDULE_SELECTOR(Enemy::movingAttrackUpdate), attrackInterval);

    return true;
}

 shibing* shibing::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray])
{
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     auto p = shibing::create(filename);
     p->getPositionArray(a, b);
     p->pointNow = 0;
     p->setPosition(Vec2(origin.x, origin.y) + p->positionArray[0]);
     p->positionNow = Vec2(origin.x, origin.y) + p->positionArray[0];
     return p;
}

 shibing* shibing::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray])
 {
     auto p = createSprite(filename, a, b);
     p->withInterval = true;
     p->getIntervalArray(interval);
     return p;
 }

 void shibing::update(float dt)
 {
     Enemy::update(dt);
     
 }



 bool yuanshichong::initWithFile(const char* filename)
 {
     if (!Enemy::initWithFile(filename))
     {
         return false;
     }
     /************基础数据初始化*********/
     name = "yuanshichong";
     healthMAX = 1050;
     health = 1050;
     attrack = 185;
     defend = 0;
     magicDefend = 0;
     blockNumber = 1;
     attrackSpeed = 100;
     attrackInterval = 1.7f;
     moveSpeed = 1.0f;
     attrackR = 0.f;
     positionType = down;
     damageType = phisical;
     onlyAttrackWhenBlocked = true;
     isblocked = false;
     ismoving = false;
     attackNum = 19;
     dieNum = 6;
     idleNum = 40;
     moveNum = 32;
     attackReachNum = 16;
     /***********************************/

     initAnimation();

     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionXYUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::stateUpdate));
     scheduleUpdate();

     if (onlyAttrackWhenBlocked == false)
         schedule(CC_SCHEDULE_SELECTOR(Enemy::movingAttrackUpdate), attrackInterval);

     return true;
 }

 yuanshichong* yuanshichong::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray])
 {
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     auto p = yuanshichong::create(filename);
     p->getPositionArray(a, b);
     p->pointNow = 0;
     p->setPosition(Vec2(origin.x, origin.y) + p->positionArray[0]);
     p->positionNow = Vec2(origin.x, origin.y) + p->positionArray[0];
     return p;
 }

 yuanshichong* yuanshichong::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray])
 {
     auto p = createSprite(filename, a, b);
     p->withInterval = true;
     p->getIntervalArray(interval);
     return p;
 }

 void yuanshichong::update(float dt)
 {
     Enemy::update(dt);

 }



 bool ganranzhegaojijiuchaguan::initWithFile(const char* filename)
 {
     if (!Enemy::initWithFile(filename))
     {
         return false;
     }
     /************基础数据初始化*********/
     name = "ganranzhegaojijiuchaguan";
     healthMAX = 4300;
     health = 4300;
     attrack = 400;
     defend = 150;
     magicDefend = 20;
     blockNumber = 1;
     attrackSpeed = 100;
     attrackInterval = 2.0f;
     moveSpeed = 1.1f;
     attrackR = 0.f;
     positionType = down;
     damageType = phisical;
     onlyAttrackWhenBlocked = true;
     isblocked = false;
     ismoving = false;
     attackNum = 21;
     dieNum = 13;
     idleNum = 19;
     moveNum = 9;
     attackReachNum = 13;
     /***********************************/

     initAnimation();

     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionXYUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::stateUpdate));
     scheduleUpdate();

     if (onlyAttrackWhenBlocked == false)
         schedule(CC_SCHEDULE_SELECTOR(Enemy::movingAttrackUpdate), attrackInterval);

     return true;
 }

 ganranzhegaojijiuchaguan* ganranzhegaojijiuchaguan::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray])
 {
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     auto p = ganranzhegaojijiuchaguan::create(filename);
     p->getPositionArray(a, b);
     p->pointNow = 0;
     p->setPosition(Vec2(origin.x, origin.y) + p->positionArray[0]);
     p->positionNow = Vec2(origin.x, origin.y) + p->positionArray[0];
     return p;
 }

 ganranzhegaojijiuchaguan* ganranzhegaojijiuchaguan::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray])
 {
     auto p = createSprite(filename, a, b);
     p->withInterval = true;
     p->getIntervalArray(interval);
     return p;
 }

 void ganranzhegaojijiuchaguan::update(float dt)
 {
     Enemy::update(dt);

 }



 bool wusasilieshouzumu::initWithFile(const char* filename)
 {
     if (!Enemy::initWithFile(filename))
     {
         return false;
     }
     /************基础数据初始化*********/
     name = "wusasilieshouzumu";
     healthMAX = 4600;
     health = 4600;
     attrack = 450;
     defend = 100;
     magicDefend = 20;
     blockNumber = 1;
     attrackSpeed = 100;
     attrackInterval = 1.5f;
     moveSpeed = 1.7f;
     attrackR = 0.f;
     positionType = down;
     damageType = phisical;
     onlyAttrackWhenBlocked = true;
     isblocked = false;
     ismoving = false;
     attackNum = 27;
     dieNum = 16;
     idleNum = 53;
     moveNum = 24;
     attackReachNum = 16;
     /***********************************/

     initAnimation();

     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionXYUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::stateUpdate));
     scheduleUpdate();

     if (onlyAttrackWhenBlocked == false)
         schedule(CC_SCHEDULE_SELECTOR(Enemy::movingAttrackUpdate), attrackInterval);

     return true;
 }

 wusasilieshouzumu* wusasilieshouzumu::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray])
 {
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     auto p = wusasilieshouzumu::create(filename);
     p->getPositionArray(a, b);
     p->pointNow = 0;
     p->setPosition(Vec2(origin.x, origin.y) + p->positionArray[0]);
     p->positionNow = Vec2(origin.x, origin.y) + p->positionArray[0];
     return p;
 }

 wusasilieshouzumu* wusasilieshouzumu::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray])
 {
     auto p = createSprite(filename, a, b);
     p->withInterval = true;
     p->getIntervalArray(interval);
     return p;
 }

 void wusasilieshouzumu::update(float dt)
 {
     Enemy::update(dt);

 }




 bool wusasigaojizhuokaishushi::initWithFile(const char* filename)
 {
     if (!Enemy::initWithFile(filename))
     {
         return false;
     }
     /************基础数据初始化*********/
     name = "wusasigaojizhuokaishushi";
     healthMAX = 6500;
     health = 6500;
     attrack = 420;
     defend = 500;
     magicDefend = 50;
     blockNumber = 1;
     attrackSpeed = 100;
     attrackInterval = 2.8f;
     moveSpeed = 0.9f;
     attrackR = 2.2f;
     positionType = down;
     damageType = magical;
     onlyAttrackWhenBlocked = false;
     isblocked = false;
     ismoving = false;
     attackNum = 34;
     dieNum = 14;
     idleNum = 37;
     moveNum = 13;
     attackReachNum = 25;
     /***********************************/

     initAnimation();

     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionXYUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::stateUpdate));
     scheduleUpdate();

     if (onlyAttrackWhenBlocked == false)
         schedule(CC_SCHEDULE_SELECTOR(Enemy::movingAttrackUpdate), attrackInterval);

     return true;
 }

 wusasigaojizhuokaishushi* wusasigaojizhuokaishushi::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray])
 {
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     auto p = wusasigaojizhuokaishushi::create(filename);
     p->getPositionArray(a, b);
     p->pointNow = 0;
     p->setPosition(Vec2(origin.x, origin.y) + p->positionArray[0]);
     p->positionNow = Vec2(origin.x, origin.y) + p->positionArray[0];
     return p;
 }

 wusasigaojizhuokaishushi* wusasigaojizhuokaishushi::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray])
 {
     auto p = createSprite(filename, a, b);
     p->withInterval = true;
     p->getIntervalArray(interval);
     return p;
 }

 void wusasigaojizhuokaishushi::update(float dt)
 {
     Enemy::update(dt);

 }




 bool diguoqianfengjingrui::initWithFile(const char* filename)
 {
     if (!Enemy::initWithFile(filename))
     {
         return false;
     }
     /************基础数据初始化*********/
     name = "diguoqianfengjingrui";
     healthMAX = 12000;
     health = 12000;
     attrack = 900;
     defend = 800;
     magicDefend = 50;
     blockNumber = 1;
     attrackSpeed = 100;
     attrackInterval = 4.5f;
     moveSpeed = 0.7f;
     attrackR = 1.5f;
     positionType = down;
     damageType = phisical;
     onlyAttrackWhenBlocked = false;
     isblocked = false;
     ismoving = false;
     attackNum = 45;
     dieNum = 14;
     idleNum = 95;
     moveNum = 57;
     attackReachNum = 26;
     /***********************************/

     initAnimation();

     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionXYUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::stateUpdate));
     scheduleUpdate();

     if (onlyAttrackWhenBlocked == false)
         schedule(CC_SCHEDULE_SELECTOR(Enemy::movingAttrackUpdate), attrackInterval);

     schedule(CC_SCHEDULE_SELECTOR(diguoqianfengjingrui::attrackIncreasing));

     return true;
 }

 diguoqianfengjingrui* diguoqianfengjingrui::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray])
 {
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     auto p = diguoqianfengjingrui::create(filename);
     p->getPositionArray(a, b);
     p->pointNow = 0;
     p->setPosition(Vec2(origin.x, origin.y) + p->positionArray[0]);
     p->positionNow = Vec2(origin.x, origin.y) + p->positionArray[0];
     return p;
 }

 diguoqianfengjingrui* diguoqianfengjingrui::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray])
 {
     auto p = createSprite(filename, a, b);
     p->withInterval = true;
     p->getIntervalArray(interval);
     return p;
 }

 void diguoqianfengjingrui::update(float dt)
 {
     Enemy::update(dt);

 }

 void diguoqianfengjingrui::attrackIncreasing(float dt)
 {
     if (health < healthMAX)
     {
         attrack = attrack * 2;
         unschedule(CC_SCHEDULE_SELECTOR(diguoqianfengjingrui::attrackIncreasing));
     }
 }




 bool diguoqianfengbaizhanjingrui::initWithFile(const char* filename)
 {
     if (!Enemy::initWithFile(filename))
     {
         return false;
     }
     /************基础数据初始化*********/
     name = "diguoqianfengbaizhanjingrui";
     healthMAX = 15000;
     health = 15000;
     attrack = 1200;
     defend = 800;
     magicDefend = 50;
     blockNumber = 1;
     attrackSpeed = 100;
     attrackInterval = 4.5f;
     moveSpeed = 0.7f;
     attrackR = 1.5f;
     positionType = down;
     damageType = phisical;
     onlyAttrackWhenBlocked = false;
     isblocked = false;
     ismoving = false;
     attackNum = 43;
     dieNum = 13;
     idleNum = 99;
     moveNum = 18;
     attackReachNum = 25;
     /***********************************/

     initAnimation();

     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionXYUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::stateUpdate));
     scheduleUpdate();

     if (onlyAttrackWhenBlocked == false)
         schedule(CC_SCHEDULE_SELECTOR(Enemy::movingAttrackUpdate), attrackInterval);

     schedule(CC_SCHEDULE_SELECTOR(diguoqianfengbaizhanjingrui::attrackIncreasing));

     return true;
 }

 diguoqianfengbaizhanjingrui* diguoqianfengbaizhanjingrui::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray])
 {
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     auto p = diguoqianfengbaizhanjingrui::create(filename);
     p->getPositionArray(a, b);
     p->pointNow = 0;
     p->setPosition(Vec2(origin.x, origin.y) + p->positionArray[0]);
     p->positionNow = Vec2(origin.x, origin.y) + p->positionArray[0];
     return p;
 }

 diguoqianfengbaizhanjingrui* diguoqianfengbaizhanjingrui::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray])
 {
     auto p = createSprite(filename, a, b);
     p->withInterval = true;
     p->getIntervalArray(interval);
     return p;
 }

 void diguoqianfengbaizhanjingrui::update(float dt)
 {
     Enemy::update(dt);

 }

 void diguoqianfengbaizhanjingrui::attrackIncreasing(float dt)
 {
     if (health < healthMAX)
     {
         attrack = attrack * 2;
         unschedule(CC_SCHEDULE_SELECTOR(diguoqianfengbaizhanjingrui::attrackIncreasing));
     }
 }




 bool diguopaohuozhongshuxianzhaozhe::initWithFile(const char* filename)
 {
     if (!Enemy::initWithFile(filename))
     {
         return false;
     }
     /************基础数据初始化*********/
     name = "diguopaohuozhongshuxianzhaozhe";
     healthMAX = 16000;
     health = 16000;
     attrack = 1200;
     defend = 800;
     magicDefend = 50;
     blockNumber = 1;
     attrackSpeed = 100;
     attrackInterval = 5.0f;
     moveSpeed = 0.5f;
     attrackR = 2.0f;
     positionType = up;
     damageType = phisical;
     onlyAttrackWhenBlocked = false;
     isblocked = false;
     ismoving = false;
     attackNum = 24;
     dieNum = 14;
     idleNum = 30;
     moveNum = 26;
     attackReachNum = 20;
     /***********************************/

     initAnimation();

     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionXYUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::stateUpdate));
     scheduleUpdate();

     if (onlyAttrackWhenBlocked == false)
         schedule(CC_SCHEDULE_SELECTOR(Enemy::movingAttrackUpdate), attrackInterval);

     return true;
 }

 diguopaohuozhongshuxianzhaozhe* diguopaohuozhongshuxianzhaozhe::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray])
 {
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     auto p = diguopaohuozhongshuxianzhaozhe::create(filename);
     p->getPositionArray(a, b);
     p->pointNow = 0;
     p->setPosition(Vec2(origin.x, origin.y) + p->positionArray[0]);
     p->positionNow = Vec2(origin.x, origin.y) + p->positionArray[0];
     return p;
 }

 diguopaohuozhongshuxianzhaozhe* diguopaohuozhongshuxianzhaozhe::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray])
 {
     auto p = createSprite(filename, a, b);
     p->withInterval = true;
     p->getIntervalArray(interval);
     return p;
 }

 void diguopaohuozhongshuxianzhaozhe::update(float dt)
 {
     Enemy::update(dt);

 }




 Vec2 guoduRange[13] = { Vec2(0,0),Vec2(0,1),Vec2(0,-1),Vec2(-1,0),Vec2(-1,1),Vec2(-1,-1),Vec2(1,0),Vec2(1,1),Vec2(1,-1),Vec2(-2,0),Vec2(2,0) ,Vec2(0,2),Vec2(0,-2) };
 bool huangdideliren::initWithFile(const char* filename)
 {
     if (!Enemy::initWithFile(filename))
     {
         return false;
     }
     /************基础数据初始化*********/
     name = "huangdideliren";
     healthMAX = 40000;
     health = 40000;
     attrack = 700;
     defend = 400;
     magicDefend = 40;
     blockNumber = 2;
     attrackSpeed = 100;
     attrackInterval = 4.0f;
     moveSpeed = 0.6f;
     attrackR = 2.0f;
     positionType = down;
     damageType = phisical;
     onlyAttrackWhenBlocked = true;
     isblocked = false;
     ismoving = false;
     attackNum = 27;
     dieNum = 51;
     idleNum = 28;
     moveNum = 24;
     attackReachNum = 16;

     guoduNum = 153;
     skillNum = 31;
     beforerecoverNum = 56;
     duringrecoverNum = 33;
     afterrecoverNum = 43;
     recoverTime = 8.0f;
     guoduTime = 6.0f;
     skillTime = 10.0f;
     /***********************************/

     initAnimation();

     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
     schedule(CC_SCHEDULE_SELECTOR(Enemy::positionXYUpdate));
     schedule(CC_SCHEDULE_SELECTOR(huangdideliren::stateUpdate));
     scheduleUpdate();

     if (onlyAttrackWhenBlocked == false)
         schedule(CC_SCHEDULE_SELECTOR(Enemy::movingAttrackUpdate));

     schedule(CC_SCHEDULE_SELECTOR(huangdideliren::skillTansuo),skillTime);
     schedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduRecover),1.0f);
     schedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduUpdate1));

     return true;
 }

 huangdideliren* huangdideliren::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray])
 {
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     auto p = huangdideliren::create(filename);
     p->getPositionArray(a, b);
     p->pointNow = 0;
     p->setPosition(Vec2(origin.x, origin.y) + p->positionArray[0]);
     p->positionNow = Vec2(origin.x, origin.y) + p->positionArray[0];
     return p;
 }

 huangdideliren* huangdideliren::createSprite(const char* filename, Vec2 a[maxpositionarray], Vec2 b[maxpositionarray], float interval[maxpositionarray])
 {
     auto p = createSprite(filename, a, b);
     p->withInterval = true;
     p->getIntervalArray(interval);
     return p;
 }

 void huangdideliren::initAnimation()
 {
     this->move1 = Enemy::createAnimate(1, name.c_str(), "move", moveNum, -1, 0.04f, 0.1f);
     this->move2 = Enemy::createAnimate(2, name.c_str(), "move", moveNum, -1, 0.04f, 0.1f);
     this->attack1keep = Enemy::createAnimate(1, name.c_str(), "attack", attackNum, 1, attrackInterval / attackNum, 0.1f);
     this->attack2keep = Enemy::createAnimate(2, name.c_str(), "attack", attackNum, 1, attrackInterval / attackNum, 0.1f);
     this->attack1once = Enemy::createAnimate(1, name.c_str(), "attack", attackNum, 1, 0.04f, 0.1f);
     this->attack2once = Enemy::createAnimate(2, name.c_str(), "attack", attackNum, 1, 0.04f, 0.1f);
     this->idle1 = Enemy::createAnimate(1, name.c_str(), "idle", idleNum, -1, 0.04f, 0.1f);
     this->idle2 = Enemy::createAnimate(2, name.c_str(), "idle", idleNum, -1, 0.04f, 0.1f);
     this->die1 = Enemy::createAnimate(1, name.c_str(), "die", dieNum, 1, 0.04f, 0.1f);
     this->die2 = Enemy::createAnimate(2, name.c_str(), "die", dieNum, 1, 0.04f, 0.1f);
     move1->retain();
     move2->retain();
     attack1keep->retain();
     attack2keep->retain();
     attack1once->retain();
     attack2once->retain();
     idle1->retain();
     idle2->retain();
     die1->retain();
     die2->retain();
     this->guodu1 = Enemy::createAnimate(1, name.c_str(), "guodu", guoduNum, 1, guoduTime/ guoduNum, 0.1f);
     this->guodu2 = Enemy::createAnimate(2, name.c_str(), "guodu", guoduNum, 1, guoduTime / guoduNum, 0.1f);
     this->skill1 = Enemy::createAnimate(1, name.c_str(), "skill", skillNum, 1, 0.04f, 0.1f);
     this->skill2 = Enemy::createAnimate(2, name.c_str(), "skill", skillNum, 1, 0.04f, 0.1f);
     this->beforerecover1 = Enemy::createAnimate(1, name.c_str(), "beforerecover", beforerecoverNum, 1, 0.04f, 0.1f);
     this->beforerecover2 = Enemy::createAnimate(2, name.c_str(), "beforerecover", beforerecoverNum, 1, 0.04f, 0.1f);
     this->duringrecover1 = Enemy::createAnimate(1, name.c_str(), "duringrecover", duringrecoverNum, 3, 0.04f, 0.1f);
     this->duringrecover2 = Enemy::createAnimate(2, name.c_str(), "duringrecover", duringrecoverNum, 3, 0.04f, 0.1f);
     this->afterrecover1 = Enemy::createAnimate(1, name.c_str(), "afterrecover", afterrecoverNum, 1, 0.04f, 0.1f);
     this->afterrecover2 = Enemy::createAnimate(2, name.c_str(), "afterrecover", afterrecoverNum, 1, 0.04f, 0.1f);
     guodu1->retain();
     guodu2->retain();
     skill1->retain();
     skill2->retain();
     beforerecover1->retain();
     beforerecover2->retain();
     duringrecover1->retain();
     duringrecover2->retain();
     afterrecover1->retain();
     afterrecover2->retain();
 }

 void huangdideliren::releaseAnimation()
 {
     Enemy::releaseAnimation();
     guodu1->release();
     guodu2->release();
     skill1->release();
     skill2->release();
     beforerecover1->release();
     beforerecover2->release();
     duringrecover1->release();
     duringrecover2->release();
     afterrecover1->release();
     afterrecover2->release();
 }

 void huangdideliren::attrackBlocked()
 {
     if (isrecovered == true)
     {
         if (this->attrack * 5 / 2 - isBlockedBy->getDefend() > this->attrack * 5 / 100)
             isBlockedBy->setHealth(isBlockedBy->getHealth() - (this->attrack * 5 / 2 - isBlockedBy->getDefend()) );
         else
             isBlockedBy->setHealth(isBlockedBy->getHealth() - this->attrack * 5 / 100 * 5 / 2);
     }
     else
     {
         if (this->attrack - isBlockedBy->getDefend() > this->attrack * 5 / 100)
             isBlockedBy->setHealth(isBlockedBy->getHealth() - (this->attrack - isBlockedBy->getDefend()));
         else
             isBlockedBy->setHealth(isBlockedBy->getHealth() - this->attrack * 5 / 100);
     }
 }

 void huangdideliren::update(float dt)
 {
     Enemy::update(dt);

 }

 Vec2 huangdideliren::searchForGuodu()
 {
     int searchAttrack = 0, index = -1;
     for (Employee* m : MapInformation::getInstance()->allEmployeeInMap)
     {
         if (m->getAttrack() > searchAttrack)
         {
             searchAttrack = m->getAttrack();
             index = MapInformation::getInstance()->allEmployeeInMap.getIndex(m);
         }
     }
     if (index != -1)
         return MapInformation::getInstance()->allEmployeeInMap.at(index)->getPositionXY();
     else
         return this->positionXYNow.at(0);
 }

 bool huangdideliren::searchForEmployee()
 {
     this->selectedEmployee.clear();
     int index = -1;
     float singleSquareLength = getLength((positionArray[pointNow + 1] - positionArray[pointNow])) / getLength((positionXYArray[pointNow + 1] - positionXYArray[pointNow]));
     float length = singleSquareLength * attrackR;
     for (Employee* employee0 : MapInformation::getInstance()->allEmployeeInMap)
     {
         if (getLength((employee0->getPosition() - this->positionNow)) < length)
         {
             this->selectedEmployee.pushBack(employee0);
         }
     }
     if (this->selectedEmployee.size()!=0)
         return true;
     else
         return false;
 }

 void huangdideliren::skillGuodu(Vec2 center)
 {
     
     if (presentState != enemyStateIdle)
     {
         unschedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
         ismoving = false;
     }
     unschedule(CC_SCHEDULE_SELECTOR(huangdideliren::stateUpdate));
     unscheduleUpdate();

     this->stopAllActions();
     auto animation1 = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (guodu1) : (guodu2));
     auto callbackGuodu = CallFunc::create([this,center]() {
         auto map3 = dynamic_cast<MapScene3*>(this->getParent());
         for (auto p : guoduRange)
         {
             if ((p + center).x >= 0.f && (p + center).x < 11.0f && (p + center).y >= 0.f && (p + center).y < 8.0f)
             {
                 auto green = Sprite::create("greensquare.png");
                 auto black = Sprite::create("guodu.png");
                 black->setOpacity(120);
                 black->setAnchorPoint(Vec2(0.5f, 0.f));
                 black->setPosition(map3->map[static_cast<int>((p + center).x)][static_cast<int>((p + center).y)].position - Vec2(0.f, green->getContentSize().height/2.0f));
                 map3->addChild(black, 1);
             }
         }

         for (auto p : MapInformation::getInstance()->allEmployeeInMap)
         {
             float singleSquareLength = getLength((positionArray[pointNow + 1] - positionArray[pointNow])) / getLength((positionXYArray[pointNow + 1] - positionXYArray[pointNow]));
             float length = singleSquareLength * attrackR;
             if (getLength((center - p->getPositionXY())) < length)
             {
                 p->setHealth(p->getHealth() - this->attrack * (100 - p->getMagicDefend()) / 100);
                 //p->setAttrackInterval(p->getAttrackInterval() * 2);
                 p->setAttrack(p->getAttrack() * 5 / 6);
             }
         }
         });
     auto animation = Sequence::create(callbackGuodu, animation1, nullptr);
     this->runAction(animation);
     

     scheduleOnce(CC_SCHEDULE_SELECTOR(huangdideliren::skillOverUpdate), guoduTime);
 }

 void huangdideliren::skillTansuo(float dt)
 {
     if (searchForEmployee())
     {
         if (presentState != enemyStateIdle)
         {
             unschedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
             ismoving = false;
         }
         unschedule(CC_SCHEDULE_SELECTOR(huangdideliren::stateUpdate));
         unscheduleUpdate();

         this->stopAllActions();
         auto animation1 = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (skill1) : (skill2));
         auto callbackTansuo = CallFunc::create([this]() {
             auto map3 = dynamic_cast<MapScene3*>(this->getParent());
             
             for (auto p : selectedEmployee)
             {
                 bool isInGuodu = false;
                 for (auto center : guoduCenter)
                 {
                     if (center != Vec2(-1, -1))
                     {
                         for (auto range : guoduRange)
                         {
                             if (range + center == p->getPositionXY())
                                 isInGuodu = true;
                         }
                     }
                 }
                 if (isInGuodu)
                     p->setHealth(0);
                 else
                     p->setHealth(p->getHealth() - this->attrack * (100 - p->getMagicDefend()) / 100);
             }
             });
         auto animation = Sequence::create(animation1, callbackTansuo, nullptr);
         this->runAction(animation);


         scheduleOnce(CC_SCHEDULE_SELECTOR(huangdideliren::skillOverUpdate), skillNum * 0.04f);
     }
 }

 void huangdideliren::skillRecover()
 {
     unschedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
     ismoving = false;
     unschedule(CC_SCHEDULE_SELECTOR(Enemy::bloodUpdate));
     unschedule(CC_SCHEDULE_SELECTOR(huangdideliren::stateUpdate));
     unscheduleUpdate();
     unschedule(CC_SCHEDULE_SELECTOR(huangdideliren::skillTansuo));
     unschedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduRecover));

     this->stopAllActions();
     auto animation1 = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (beforerecover1) : (beforerecover2));
     auto animation2 = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (duringrecover1) : (duringrecover2));
     auto animation3 = Animate::create((getDirection(positionNow.x, positionArray[pointNow + 1].x) == left) ? (afterrecover1) : (afterrecover2));
     auto callbackRecover = CallFunc::create([this]() {
         for (auto employee0 : MapInformation::getInstance()->allEmployeeInMap)
         {
             bool isInGuodu = false;
             for (auto center : guoduCenter)
             {
                 if (center != Vec2(-1, -1))
                 {
                     for (auto range : guoduRange)
                     {
                         if (range + center == employee0->getPositionXY())
                             isInGuodu = true;
                     }
                 }
             }
             if (isInGuodu)
                 employee0->setHealth(0);
             else
                 employee0->setHealth(employee0->getHealth() - this->attrack * (100 - employee0->getMagicDefend()) / 100);
         }

         attrack = 1050;
         health = 50000;
         healthMAX = 50000;
         //加个无敌图标
         auto progress = (ProgressTimer*)this->getChildByTag(MapInformation::getInstance()->allEnemyInMap.getIndex(this));
         progress->setPercentage(100.f);
         schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
         schedule(CC_SCHEDULE_SELECTOR(huangdideliren::stateUpdate));
         scheduleUpdate();
         schedule(CC_SCHEDULE_SELECTOR(huangdideliren::skillTansuo), skillTime);
         schedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduRecover), 1.0f);

         scheduleOnce(CC_SCHEDULE_SELECTOR(huangdideliren::unbeatableOver), 10.0f);
         });
     auto animation = Sequence::create(animation1, animation2, animation3, callbackRecover, nullptr);
     this->runAction(animation);
 }

 void huangdideliren::unbeatableOver(float dt)
 {
     health = 50000;
     schedule(CC_SCHEDULE_SELECTOR(Enemy::bloodUpdate));
     schedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduUpdate2));
 }

 void huangdideliren::guoduRecover(float dt)
 {
     bool isInGuodu = false;
     for (auto center : guoduCenter)
     {
         if (center != Vec2(-1, -1))
         {
             for (auto range : guoduRange)
             {
                 for (auto p : positionXYNow)
                     if (range + center == p)
                         isInGuodu = true;
             }
         }
     }
     if (isInGuodu)
         health = (health + 200 >= healthMAX) ? (healthMAX) : (health + 200);
 }

 void huangdideliren::guoduUpdate1(float dt)
 {
     if (health < healthMAX / 2)
     {
         guoduCenter[0] = searchForGuodu();   
         skillGuodu(guoduCenter[0]);
         unschedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduUpdate1));
     }

 }

 void huangdideliren::guoduUpdate2(float dt)
 {
     if (health < healthMAX * 3 / 4)
     {
         guoduCenter[1] = searchForGuodu();
         skillGuodu(guoduCenter[1]);
         unschedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduUpdate2));
         schedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduUpdate3));
     }

 }

 void huangdideliren::guoduUpdate3(float dt)
 {
     if (health < healthMAX / 2)
     {
         guoduCenter[2] = searchForGuodu();
         skillGuodu(guoduCenter[2]);
         unschedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduUpdate3));
         schedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduUpdate4));
     }

 }

 void huangdideliren::guoduUpdate4(float dt)
 {
     if (health < healthMAX / 4)
     {
         guoduCenter[3] = searchForGuodu();
         skillGuodu(guoduCenter[3]);
         unschedule(CC_SCHEDULE_SELECTOR(huangdideliren::guoduUpdate4));
     }

 }
 
 void huangdideliren::skillOverUpdate(float dt)
 {
     lastState = enemyStateNone;
     if (presentState != enemyStateIdle)
         schedule(CC_SCHEDULE_SELECTOR(Enemy::positionUpdate));
     schedule(CC_SCHEDULE_SELECTOR(huangdideliren::stateUpdate));
     scheduleUpdate();
 }

 void huangdideliren::stateUpdate(float dt)
 {
     if (isadded)
     {
         if (this->getPresentState() != enemyStateDie)
         {
             if (this->health <= 0)
             {
                 if (isrecovered == false)
                 {
                     skillRecover();
                     isrecovered = true;
                 }
                 else
                     this->setPresentState(enemyStateDie);
             }
             else
             {
                 if (this->onlyAttrackWhenBlocked == true)
                 {
                     if (isblocked == true)
                     {
                         presentState = enemyStateAttackKeep;
                         stopActionByTag(enemyPingYi);
                     }
                 }
             }

         }
     }
 }