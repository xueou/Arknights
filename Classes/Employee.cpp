#include "Employee.h"
#include "MapInformation.h"
#include "Range.h"
#include "AudioEngine.h"

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

    schedule(CC_SCHEDULE_SELECTOR(Employee::blockUpdate));

    return true;
}

void Employee::initAnimation()
{
    this->start1 = Employee::createAnimate(1, name.c_str(), "start", startNum, 1, 0.04f);
    this->start2 = Employee::createAnimate(2, name.c_str(), "start", startNum, 1, 0.04f);
    this->attack1 = Employee::createAnimate(1, name.c_str(), "attack", attackNum, 1, attrackInterval / attackNum);
    this->attack2 = Employee::createAnimate(2, name.c_str(), "attack", attackNum, 1, attrackInterval/ attackNum);
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
    /**********************************************************    帧事件，狗都不用，浪费大好青春！！！！！！！
    ValueMap info2;                              绝对不是因为我不会用，因为根本哪里都没有教程，我咋能自己编出来。。。
    info2["FrameId"] = Value(StringUtils::format("Frame%d", attackReachNum));
    attack1->getFrames().at(attackReachNum - 1)->setUserInfo(info2);
    attack2->getFrames().at(attackReachNum - 1)->setUserInfo(info2);
    auto _employeeStateAttackListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
        {
            auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
            attrackSelectedEnemy();
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_employeeStateAttackListener, this);
                                  ******************************************************/
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

    releaseSkillAnimation();
}

void Employee::releaseSkillAnimation()
{

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
    AudioEngine::play2d(".\\employee\\"+name+"\\attackeffect.mp3");
    if ((attrackRange != DANNAI) && (attrackRange != QUNNAI))//医疗干员特判
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
                p->setHealth(p->getHealth() - this->attrack * (100 - (p->getMagicDefend()-(this->name=="shierteer"?(20):(0)))) / 100);//简化逻辑，直接加入史尔特尔天赋特判
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
    else
    {
        for (Employee* p : this->selectedEmployee)
        {
            p->health = (p->health + this->attrack > p->healthMAX) ? (p->healthMAX) : (p->health + this->attrack);
        }
    }
}

bool Employee::searchEnemy()
{
    switch (attrackRange)
    {
        case DANFA:
            return this->searchEnemyByType(danfa[direction0],danfaRange);
        case ZHONGZHUANG:
            return this->searchEnemyByType(zhongzhuang[direction0], zhongzhuangRange);
        case NAIDUN_ATTACK:
            return this->searchEnemyByType(naidunattrack[direction0], naidunattrackRange);
        case FAJINWEI:
            return this->searchEnemyByType(fajinwei[direction0], fajinweiRange);
        case HUANGHUN:
            return this->searchEnemyByType(huanghun[direction0], huanghunRange);
        case QUNWEI:
            return this->searchEnemyByType(qunwei[direction0], qunweiRange);
        case DANNAI:
            return this->searchEnemyByType(dannai[direction0], dannaiRange);
        case YUANWEI:
            return this->searchEnemyByType(yuanwei[direction0], yuanweiRange);
        case QUNNAI:
            return this->searchEnemyByType(qunnai[direction0], qunnaiRange);
        case SUJU:
            return this->searchEnemyByType(suju[direction0], sujuRange);
        case XIANFENG:
            return this->searchEnemyByType(xianfeng[direction0], xianfengRange);
    }
    return false;
}

void Employee::searchForBlock()
{
    if (remainBlockNumber > 0)
    {
        Vector<Enemy*> temporary;
        for (Enemy* enemy0 : MapInformation::getInstance()->allEnemyInMap)
        {
            if (enemy0->getIsadded() == true && enemy0->getIsblocked()==false)
            {
                if (enemy0->getPositionType() == this->blockedType || this->blockedType == upanddown)
                {
                    for (Vec2 p : enemy0->positionXYNow)
                    {
                        if (this->positionXY == p)
                        {
                            if (remainBlockNumber >= enemy0->getBlockNumber())
                            {
                                temporary.pushBack(enemy0);
                            }
                            break;
                        }
                    }
                }
            }
        }

        if (temporary.size() != 0)
        {
            float length = 3000.0f;
            int deltaPoint = 100;
            int index;
            for (Enemy* m : temporary)
            {
                if ((m->pointNum - m->pointNow) < deltaPoint || ((m->pointNum - m->pointNow) == deltaPoint && getLength((m->positionArray[m->pointNow + 1] - m->getPosition())) < length))
                {
                    length = getLength((m->positionArray[m->pointNow + 1] - m->getPosition()));
                    deltaPoint = m->pointNum - m->pointNow;
                    index = temporary.getIndex(m);
                }
            }

            blockedEnemy.pushBack(temporary.at(index));
            temporary.at(index)->setIsblocked(true);
            temporary.at(index)->isBlockedBy = this;
            temporary.at(index)->setIsmoving(false);
            remainBlockNumber -= temporary.at(index)->getBlockNumber();
        }
    }
}

void Employee::deleteBlockedEnemy(Enemy* m)
{
    blockedEnemy.eraseObject(m);
}

void Employee::releaseAllBlockedEnemy()
{
    for (Enemy* m : blockedEnemy)
    {
        m->setIsblocked(false);
        m->isBlockedBy = NULL;
    }
}

bool Employee::searchEnemyByType(Vec2 range[12], int rangeNum)
{
    if ((attrackRange != DANNAI) && (attrackRange != QUNNAI))//医疗干员特判
    {
        this->selectedEnemy.clear();
        for (Enemy* enemy0 : MapInformation::getInstance()->allEnemyInMap)  //此处虽然多重for嵌套，但实际上在游戏本身的机制模式下
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
                                if (this->selectedEnemy.size() == 0)
                                {
                                    this->selectedEnemy.pushBack(enemy0);
                                }
                                else if (this->selectedEnemy.at(0)->getPositionType() == down && enemy0->getPositionType() == up)
                                {
                                    this->selectedEnemy.replace(0, enemy0);
                                }
                                else if (!(this->selectedEnemy.at(0)->getPositionType() == up && enemy0->getPositionType() == down))
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

        if (blockedEnemy.size() != 0)//优先攻击阻挡的单位
        {
            for (Enemy* m : blockedEnemy)
            {
                if (selectedEnemy.contains(m) == false)
                {
                    for (Enemy* p : selectedEnemy)
                    {
                        if (blockedEnemy.contains(p) == false)
                            selectedEnemy.replace(selectedEnemy.getIndex(p), m);
                    }
                }
            }
        }

        if (this->selectedEnemy.size() == 0)
            return false;
        else
            return true;
    }
    else
    {
        this->selectedEmployee.clear();
        for (Employee* employee0 : MapInformation::getInstance()->allEmployeeInMap)
        {
            for (int i = 0; i < rangeNum; i++)
            {
                if ((range[i] + this->positionXY == employee0->positionXY) && (employee0->health< employee0->healthMAX))
                {
                    if (this->selectedEmployee.size() < attrackNumber)
                    {
                        this->selectedEmployee.pushBack(employee0);
                    }
                    else
                    {
                        int index;
                        int health1 = 0;
                        for (Employee* employee1 : this->selectedEmployee)
                        {
                            if (employee1->health > health1)
                            {
                                health1 = employee1->health;
                                index = this->selectedEmployee.getIndex(employee1);
                            }
                        }
                        if (employee0->health < health1)
                            this->selectedEmployee.replace(index, employee0);
                    }
                    break;
                }
            }
        }
        if (this->selectedEmployee.size() == 0)
            return false;
        else
            return true;
    }
}

int Employee::getEmployeeListType()                /***************记得补全**************/
{
    if (name == "aiyafala")
        return 1;
    else if (name == "xingxiong")
        return 2;
    else if (name == "saileiya")
        return 3;
    else if (name == "shierteer")
        return 4;
    else if (name == "huang")
        return 5;
    else if (name == "shanling")
        return 6;
    else if (name == "yinhui")
        return 7;
    else if (name == "baimianxiao")
        return 8;
    else if (name == "nengtianshi")
        return 9;
    else if (name == "dekesasi")
        return 10;
    else if (name == "taojinniang")
        return 11;
}
/**********************************菜单状态下的死亡处理*****************************************/
void Employee::addSkillList()
{
    auto p = Sprite::create("greensquare.png");
    p->setAnchorPoint(Vec2(0.5f, 0.5f));
    p->setOpacity(0);
    p->setPosition(Vec2::ZERO);
    this->addChild(p);

    auto _addSkillListListener = EventListenerTouchOneByOne::create();
    _addSkillListListener->setSwallowTouches(true);
    _addSkillListListener->onTouchBegan = [p,this](Touch* touch, Event* event)
    {       
        if (Rect(this->getPosition().x - p->getContentSize().width / 2.0f, this->getPosition().y - p->getContentSize().height / 2.0f,
            p->getContentSize().width, p->getContentSize().height).containsPoint(touch->getLocation()))
            return true;
        else
            return false;
    };
    _addSkillListListener->onTouchEnded = [this](Touch* touch, Event* event)
    {
        AudioEngine::play2d(".\\employee\\"+name+"\\selected.mp3");
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
                this->releaseAnimation();
                this->removeFromParent();
                
                auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
                auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));               

                int m = map->getC() + (employeelist->getFee() + (employeelist->getReputNum() >= 2 ? (employeelist->getFee()) : (employeelist->getReputNum() == 1 ? (employeelist->getFee() / 2) : (0)))) / 2;
                map->setC((m) > 99 ? (99) : (m));
                map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
                /*******************再部署时间******************/
                employeelist->reputtingLoading();

                releaseAllBlockedEnemy();//释放阻挡敌人

                employeelist->setOpacity(100);
                employeelist->setIsadded(false);
                employeelist->setReputNum(employeelist->getReputNum() + 1);

                MapInformation::getInstance()->allEmployeeInMap.eraseObject(this);
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
                    skillbackground->getContentSize().width, skillbackground->getContentSize().height).containsPoint(touch->getLocation()) && this->sp==this->spMAX && this->isSkillAuto==false)
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
                AudioEngine::play2d(".\\employee\\" + name + "\\skill.mp3");
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

void Employee::blockUpdate(float dt)
{
    this->searchForBlock();
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

                auto animation0 = Animate::create((direction0 == left || direction0 == front) ? (attack1) : (attack2));
                auto callbackAttack = CallFunc::create([this]() {
                    attrackSelectedEnemy();
                    });
                auto animation1 = Sequence::create(animation0, callbackAttack, nullptr);
                auto animation = RepeatForever::create(animation1);
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
                    this->releaseAnimation();
                    this->removeFromParent();
                    
                    auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
                    auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

                    map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
                    /*******************再部署时间******************/
                    employeelist->reputtingLoading();

                    releaseAllBlockedEnemy();//释放阻挡敌人

                    employeelist->setOpacity(100);
                    employeelist->setIsadded(false);
                    employeelist->setReputNum(employeelist->getReputNum() + 1);

                    MapInformation::getInstance()->allEmployeeInMap.eraseObject(this);
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
    isSkillAuto = false;
    positionType = up;
    damageType = magical;
    selectedType = upanddown;
    blockedType = up;
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
    AudioEngine::play2d(".\\employee\\aiyafala\\beforeskilleffect.mp3");
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

    schedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillSPUpdate), skillTime/static_cast<float>(spMAX));
    schedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillAttrackUpdate), attrackInterval);
    schedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillHealthUpdate));

    scheduleOnce(CC_SCHEDULE_SELECTOR(Aiyafala::skillOverUpdate),skillTime);
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
    {
        AudioEngine::play2d(".\\employee\\aiyafala\\skillattrackeffect.mp3");
        attrackSelectedEnemy();
    }
}

void Aiyafala::skillHealthUpdate(float dt)
{
    if (health <= 0)
    {
        this->stopAllActions();
        auto animation = Animate::create((direction0 == left || direction0 == front) ? (die1) : (die2));
        auto callbackDie = CallFunc::create([this]() {
            auto map = dynamic_cast<MapScene*>(this->getParent());
            this->releaseAnimation();
            this->removeFromParent();
            
            auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
            auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

            map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
            /*******************再部署时间******************/
            employeelist->reputtingLoading();

            releaseAllBlockedEnemy();//释放阻挡敌人

            employeelist->setOpacity(100);
            employeelist->setIsadded(false);
            employeelist->setReputNum(employeelist->getReputNum() + 1);

            MapInformation::getInstance()->allEmployeeInMap.eraseObject(this);
            });
        this->runAction(Sequence::create(animation, callbackDie, nullptr));
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

    

    lastState = employeeStateIdle;
    presentState = employeeStateIdle;
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
    animation->setTag(employeeStateIdle);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate),1.0f);
    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();
    
}

void Aiyafala::releaseSkillAnimation()
{
    beforeskill1->release();
    beforeskill2->release();
    duringskill1->release();
    duringskill2->release();
    afterskill1->release();
    afterskill2->release();
}




bool Xingxiong::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "xingxiong";
    healthMAX = 3850;
    health = 3850;
    spMAX = 50;
    sp = 30;
    attrack = 490;
    defend = 813;
    magicDefend = 0;
    blockNumber = 3;
    remainBlockNumber = 3;
    attrackNumber = 1;
    attrackSpeed = 100;
    attrackRange = ZHONGZHUANG;
    attrackInterval = 1.2f;
    skillTime = 25.0f;
    isSkillAuto = false;
    positionType = down;
    damageType = phisical;
    selectedType = down;
    blockedType = down;
    attackNum = 38;
    dieNum = 28;
    idleNum = 86;
    startNum = 14;
    attackReachNum = 30;
    //技能参数不同干员需要哪些单独初始化
    beforeskillNum = 19;
    duringskillNum = 9;
    afterskillNum = 6;
    /***********************************/

    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

    return true;
}

Xingxiong* Xingxiong::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Xingxiong::create(filename);

    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;

    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Xingxiong::initSkillAnimation()
{
    this->beforeskill1 = Employee::createAnimate(1, name.c_str(), "beforeskill", beforeskillNum, 1, 0.04f);
    this->beforeskill2 = Employee::createAnimate(2, name.c_str(), "beforeskill", beforeskillNum, 1, 0.04f);
    this->duringskill1 = Employee::createAnimate(1, name.c_str(), "duringskill", duringskillNum, 67, 0.04f);
    this->duringskill2 = Employee::createAnimate(2, name.c_str(), "duringskill", duringskillNum, 67, 0.04f);
    this->afterskill1 = Employee::createAnimate(1, name.c_str(), "afterskill", afterskillNum, 1, 0.04f);
    this->afterskill2 = Employee::createAnimate(2, name.c_str(), "afterskill", afterskillNum, 1, 0.04f);
    beforeskill1->retain();
    beforeskill2->retain();
    duringskill1->retain();
    duringskill2->retain();
    afterskill1->retain();
    afterskill2->retain();
}

void Xingxiong::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    unscheduleUpdate();

    attrack = 1176;
    attrackNumber = 20;
    defend = 1544;
    this->stopAllActions();
    auto animation1 = Animate::create((direction0 == left || direction0 == front) ? (beforeskill1) : (beforeskill2));
    auto animation2 = Animate::create((direction0 == left || direction0 == front) ? (duringskill1) : (duringskill2));
    auto animation3 = Animate::create((direction0 == left || direction0 == front) ? (afterskill1) : (afterskill2));
    auto animation = Sequence::create(animation1, animation2, animation3, nullptr);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Xingxiong::skillSPUpdate), skillTime / static_cast<float>(spMAX));
    schedule(CC_SCHEDULE_SELECTOR(Xingxiong::skillAttrackUpdate), attrackInterval);
    schedule(CC_SCHEDULE_SELECTOR(Xingxiong::skillHealthUpdate));

    scheduleOnce(CC_SCHEDULE_SELECTOR(Xingxiong::skillOverUpdate), skillTime);
}

void Xingxiong::update(float dt)
{
    Employee::update(dt);
}

void Xingxiong::skillSPUpdate(float dt)
{
    if (sp > 0)
        sp--;
}

void Xingxiong::skillAttrackUpdate(float dt)
{
    if (searchEnemyByType(lizhiju[direction0], lizhijuRange))
        attrackSelectedEnemy();
}

void Xingxiong::skillHealthUpdate(float dt)
{
    if (health <= 0)
    {
        this->stopAllActions();
        auto animation = Animate::create((direction0 == left || direction0 == front) ? (die1) : (die2));
        auto callbackDie = CallFunc::create([this]() {
            auto map = dynamic_cast<MapScene*>(this->getParent());
            this->releaseAnimation();
            this->removeFromParent();
            
            auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
            auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

            map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
            /*******************再部署时间******************/
            employeelist->reputtingLoading();

            releaseAllBlockedEnemy();//释放阻挡敌人

            employeelist->setOpacity(100);
            employeelist->setIsadded(false);
            employeelist->setReputNum(employeelist->getReputNum() + 1);

            MapInformation::getInstance()->allEmployeeInMap.eraseObject(this);
            });
        this->runAction(Sequence::create(animation, callbackDie, nullptr));
    }
}

void Xingxiong::skillOverUpdate(float dt)
{
    attrack = 490;
    attrackNumber = 1;
    defend = 813;

    unschedule(CC_SCHEDULE_SELECTOR(Xingxiong::skillSPUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Xingxiong::skillAttrackUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Xingxiong::skillHealthUpdate));



    lastState = employeeStateIdle;
    presentState = employeeStateIdle;
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
    animation->setTag(employeeStateIdle);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

}

void Xingxiong::releaseSkillAnimation()
{
    beforeskill1->release();
    beforeskill2->release();
    duringskill1->release();
    duringskill2->release();
    afterskill1->release();
    afterskill2->release();
}




bool Saileiya::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "saileiya";
    healthMAX = 3150;
    health = 3150;
    spMAX = 7;
    sp = 0;
    attrack = 535;
    defend = 682;
    magicDefend = 10;
    blockNumber = 3;
    remainBlockNumber = 3;
    attrackNumber = 1;
    attrackSpeed = 100;
    attrackRange = NAIDUN_ATTACK;
    attrackInterval = 1.2f;
    skillTime = 1.0f;
    isSkillAuto = true;
    positionType = down;
    damageType = phisical;
    selectedType = down;
    blockedType = down;
    attackNum = 31;
    dieNum = 18;
    idleNum = 37;
    startNum = 13;
    attackReachNum = 22;
    //技能参数不同干员需要哪些单独初始化
    skillNum = 25;

    /***********************************/

    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    schedule(CC_SCHEDULE_SELECTOR(Saileiya::skillTouchAuto));
    scheduleUpdate();

    return true;
}

Saileiya* Saileiya::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Saileiya::create(filename);

    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;

    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Saileiya::initSkillAnimation()
{
    this->skill1 = Employee::createAnimate(1, name.c_str(), "skill", skillNum, 1, 0.04f);
    this->skill2 = Employee::createAnimate(2, name.c_str(), "skill", skillNum, 1, 0.04f);
    skill1->retain();
    skill2->retain();
}

void Saileiya::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Saileiya::skillTouchAuto));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    unscheduleUpdate();

    attrack = 749;
    attrackNumber = 20;
    this->stopActionByTag(presentState);
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (skill1) : (skill2));
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Saileiya::skillSPUpdate), skillTime / static_cast<float>(spMAX));
    scheduleOnce(CC_SCHEDULE_SELECTOR(Saileiya::skillAttrackUpdate), 0.8f);
    schedule(CC_SCHEDULE_SELECTOR(Saileiya::skillHealthUpdate));

    scheduleOnce(CC_SCHEDULE_SELECTOR(Saileiya::skillOverUpdate), skillTime);
}

void Saileiya::update(float dt)
{
    Employee::update(dt);
}

void Saileiya::skillTouchAuto(float dt)
{
    if (sp == spMAX)
    {
        attrackRange = QUNNAI;
        if (searchEnemyByType(naiduncure, naiduncureRange))
        {
            AudioEngine::play2d(".\\employee\\" + name + "\\skill.mp3");
            this->skill();
        }
        attrackRange = NAIDUN_ATTACK;
    }
}

void Saileiya::skillSPUpdate(float dt)
{
    if (sp > 0)
        sp--;
}

void Saileiya::skillAttrackUpdate(float dt)
{
    attrackRange = QUNNAI;
    attrackSelectedEnemy();
    attrackRange = NAIDUN_ATTACK;
}

void Saileiya::skillHealthUpdate(float dt)
{
    if (health <= 0)
    {
        this->stopAllActions();
        auto animation = Animate::create((direction0 == left || direction0 == front) ? (die1) : (die2));
        auto callbackDie = CallFunc::create([this]() {
            auto map = dynamic_cast<MapScene*>(this->getParent());
            this->releaseAnimation();
            this->removeFromParent();

            auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
            auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

            map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
            /*******************再部署时间******************/
            employeelist->reputtingLoading();

            releaseAllBlockedEnemy();//释放阻挡敌人

            employeelist->setOpacity(100);
            employeelist->setIsadded(false);
            employeelist->setReputNum(employeelist->getReputNum() + 1);

            MapInformation::getInstance()->allEmployeeInMap.eraseObject(this);
            });
        this->runAction(Sequence::create(animation, callbackDie, nullptr));
    }
}

void Saileiya::skillOverUpdate(float dt)
{
    attrack = 535;
    attrackNumber = 1;

    unschedule(CC_SCHEDULE_SELECTOR(Saileiya::skillSPUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Saileiya::skillAttrackUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Saileiya::skillHealthUpdate));



    lastState = employeeStateIdle;
    presentState = employeeStateIdle;
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
    animation->setTag(employeeStateIdle);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    schedule(CC_SCHEDULE_SELECTOR(Saileiya::skillTouchAuto));
    scheduleUpdate();

}

void Saileiya::releaseSkillAnimation()
{
    skill1->release();
    skill2->release();
}




bool Shierteer::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "shierteer";
    healthMAX = 2916;
    health = 2916;
    spMAX = 5;
    sp = 0;
    attrack = 800;
    defend = 414;
    magicDefend = 15;
    blockNumber = 1;
    remainBlockNumber = 1;
    attrackNumber = 1;
    attrackSpeed = 100;
    attrackRange = FAJINWEI;
    attrackInterval = 1.25f;
    skillTime = 9999.0f;
    isSkillAuto = false;
    positionType = down;
    damageType = magical;
    selectedType = down;
    blockedType = down;
    attackNum = 34;
    dieNum = 11;
    idleNum = 51;
    startNum = 13;
    attackReachNum = 13;
    /***********************************/

    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

    return true;
}

Shierteer* Shierteer::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Shierteer::create(filename);

    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;

    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Shierteer::initSkillAnimation()
{

}

void Shierteer::releaseSkillAnimation()
{

}

void Shierteer::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    //unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    schedule(CC_SCHEDULE_SELECTOR(Shierteer::shierteerStateUpdate));
    sp = 4;
    isskilled = true;
    attrack = 3440;
    attrackNumber = 3;
    healthMAX = 7916;
    health = 7896;
    remainBlockNumber += 2;

    attackNum = 38;
    idleNum = 56;
    attackReachNum = 18;
    attrackRange = HUANGHUN;
    this->stopActionByTag(presentState);
    lastState = employeeStateNone;
    this->attack1 = Employee::createAnimate(1, name.c_str(), "skillattack", attackNum, 1, attrackInterval / attackNum);
    this->attack2 = Employee::createAnimate(2, name.c_str(), "skillattack", attackNum, 1, attrackInterval / attackNum);
    this->idle1 = Employee::createAnimate(1, name.c_str(), "skillidle", idleNum, -1, 0.04f);
    this->idle2 = Employee::createAnimate(2, name.c_str(), "skillidle", idleNum, -1, 0.04f);
    attack1->retain();
    attack2->retain();
    idle1->retain();
    idle2->retain();
    /*ValueMap info2;
    info2["FrameId"] = Value(StringUtils::format("Frame%d", attackReachNum));
    attack1->getFrames().at(attackReachNum - 1)->setUserInfo(info2);
    attack2->getFrames().at(attackReachNum - 1)->setUserInfo(info2);
    auto _employeeStateAttackListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
        {
            auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
            attrackSelectedEnemy();
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_employeeStateAttackListener, this);*/
    //auto animation1 = Animate::create((direction0 == left || direction0 == front) ? (beforeskill1) : (beforeskill2));
    //auto animation2 = Animate::create((direction0 == left || direction0 == front) ? (duringskill1) : (duringskill2));
    //auto animation3 = Animate::create((direction0 == left || direction0 == front) ? (afterskill1) : (afterskill2));
    //auto animation = Sequence::create(animation1, animation2, animation3, nullptr);
    //this->runAction(animation);

    //schedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillSPUpdate), skillTime / static_cast<float>(spMAX));
    //schedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillAttrackUpdate), attrackInterval);
    schedule(CC_SCHEDULE_SELECTOR(Shierteer::skillHealthUpdate),0.2f);

    //scheduleOnce(CC_SCHEDULE_SELECTOR(Aiyafala::skillOverUpdate), skillTime);
}

void Shierteer::shierteerStateUpdate(float dt)
{
    if (this->getPresentState() != employeeStateStart && this->getPresentState() != employeeStateDie)
    {
        if (this->health <= 0 && suoxue == false)
        {
            suoxue = true;
            scheduleOnce(CC_SCHEDULE_SELECTOR(Shierteer::die), 9.0f);
        }
        else if (searchEnemy())
            this->setPresentState(employeeStateAttack);
        else
            this->setPresentState(employeeStateIdle);
    }
}

void Shierteer::update(float dt)
{
    Employee::update(dt);
}

void Shierteer::skillHealthUpdate(float dt)
{
    health -= (healthMAX - health) / 20;
}

void Shierteer::die(float dt)
{
    this->presentState = employeeStateDie;
}




bool Huang::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "huang";
    healthMAX = 2821;
    health = 2821;
    spMAX = 70;
    sp = 0;
    attrack = 853;
    defend = 415;
    magicDefend = 0;
    blockNumber = 3;
    remainBlockNumber = 3;
    attrackNumber = 1;
    attrackSpeed = 100;
    attrackRange = FAJINWEI;
    attrackInterval = 1.2f;
    skillTime = 9999.0f;
    isSkillAuto = true;
    positionType = down;
    damageType = phisical;
    selectedType = down;
    blockedType = down;
    attackNum = 18;
    dieNum = 15;
    idleNum = 30;
    startNum = 10;
    attackReachNum = 14;

    beforeskillNum = 39;
    /***********************************/

    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    schedule(CC_SCHEDULE_SELECTOR(Huang::skillTouchAuto));
    schedule(CC_SCHEDULE_SELECTOR(Huang::recoverUpdate));
    scheduleUpdate();

    return true;
}

Huang* Huang::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Huang::create(filename);

    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;

    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Huang::initSkillAnimation()
{
    this->beforeskill1 = Employee::createAnimate(1, name.c_str(), "beforeskill", beforeskillNum, 1, 0.04f);
    this->beforeskill2 = Employee::createAnimate(2, name.c_str(), "beforeskill", beforeskillNum, 1, 0.04f);
    beforeskill1->retain();
    beforeskill2->retain();
}

void Huang::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Huang::skillTouchAuto));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    unscheduleUpdate();
    sp = 69;
    isskilled = true;
    attrack = 1706;
    attrackNumber = 3;
    defend = 560;

    this->stopAllActions();
    auto animation1 = Animate::create((direction0 == left || direction0 == front) ? (beforeskill1) : (beforeskill2));
    this->runAction(animation1);

    attackNum = 14;
    idleNum = 14;
    attackReachNum = 10;
    attrackRange = QUNWEI;
    this->attack1 = Employee::createAnimate(1, name.c_str(), "duringskill", attackNum, 1, attrackInterval / attackNum);
    this->attack2 = Employee::createAnimate(2, name.c_str(), "duringskill", attackNum, 1, attrackInterval / attackNum);
    this->idle1 = Employee::createAnimate(1, name.c_str(), "duringskill", idleNum, -1, 0.04f);
    this->idle2 = Employee::createAnimate(2, name.c_str(), "duringskill", idleNum, -1, 0.04f);
    attack1->retain();
    attack2->retain();
    idle1->retain();
    idle2->retain();
    /*ValueMap info2;
    info2["FrameId"] = Value(StringUtils::format("Frame%d", attackReachNum));
    attack1->getFrames().at(attackReachNum - 1)->setUserInfo(info2);
    attack2->getFrames().at(attackReachNum - 1)->setUserInfo(info2);
    auto _employeeStateAttackListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [this](EventCustom* event)
        {
            auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
            attrackSelectedEnemy();
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_employeeStateAttackListener, this);*/
    //auto animation1 = Animate::create((direction0 == left || direction0 == front) ? (beforeskill1) : (beforeskill2));
    //auto animation2 = Animate::create((direction0 == left || direction0 == front) ? (duringskill1) : (duringskill2));
    //auto animation3 = Animate::create((direction0 == left || direction0 == front) ? (afterskill1) : (afterskill2));
    //auto animation = Sequence::create(animation1, animation2, animation3, nullptr);
    //this->runAction(animation);

    //schedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillSPUpdate), skillTime / static_cast<float>(spMAX));
    //schedule(CC_SCHEDULE_SELECTOR(Aiyafala::skillAttrackUpdate), attrackInterval);
    scheduleOnce(CC_SCHEDULE_SELECTOR(Huang::skillOverUpdate), 1.56f);

    //scheduleOnce(CC_SCHEDULE_SELECTOR(Aiyafala::skillOverUpdate), skillTime);
}

void Huang::update(float dt)
{
    Employee::update(dt);
}

void Huang::skillTouchAuto(float dt)
{
    if (sp == spMAX)
    {
        AudioEngine::play2d(".\\employee\\" + name + "\\skill.mp3");
        this->skill();
    }
}

void Huang::skillOverUpdate(float dt)
{       
    lastState = employeeStateIdle;
    presentState = employeeStateIdle;
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
    animation->setTag(employeeStateIdle);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();
}

void Huang::recoverUpdate(float dt)
{
    if (health < healthMAX / 4)
    {
        health += healthMAX / 2;
        unschedule(CC_SCHEDULE_SELECTOR(Huang::recoverUpdate));
    }
}

void Huang::releaseSkillAnimation()
{
    beforeskill1->release();
    beforeskill2->release();
}




bool Shanling::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "shanling";
    healthMAX = 1613;
    health = 1613;
    spMAX = 120;
    sp = 115;
    attrack = 610;
    defend = 183;
    magicDefend = 0;
    blockNumber = 1;
    remainBlockNumber = 1;
    attrackNumber = 1;
    attrackSpeed = 100;
    attrackRange = DANNAI;
    attrackInterval = 2.85f;
    skillTime = 60.0f;
    isSkillAuto = false;
    positionType = up;
    damageType = nurse;
    selectedType = upanddown;
    blockedType = up;
    attackNum = 26;
    dieNum = 19;
    idleNum = 81;
    startNum = 9;
    attackReachNum = 26;
    //技能参数不同干员需要哪些单独初始化

    /***********************************/

    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

    return true;
}

Shanling* Shanling::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Shanling::create(filename);

    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;

    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Shanling::initSkillAnimation()
{

}

void Shanling::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    //unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    //unscheduleUpdate();

    attrack = 915;


    schedule(CC_SCHEDULE_SELECTOR(Shanling::skillSPUpdate), skillTime / static_cast<float>(spMAX));


    scheduleOnce(CC_SCHEDULE_SELECTOR(Xingxiong::skillOverUpdate), skillTime);
}

void Shanling::update(float dt)
{
    Employee::update(dt);
}

void Shanling::skillSPUpdate(float dt)
{
    if (sp > 0)
        sp--;
}

void Shanling::skillOverUpdate(float dt)
{
    attrack = 610;

    unschedule(CC_SCHEDULE_SELECTOR(Shanling::skillSPUpdate));
    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate), 1.0f);
}

void Shanling::releaseSkillAnimation()
{

}




bool Yinhui::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "yinhui";
    healthMAX = 2560;
    health = 2560;
    spMAX = 90;
    sp = 75;
    attrack = 865;
    defend = 447;
    magicDefend = 10;
    blockNumber = 2;
    remainBlockNumber = 2;
    attrackNumber = 1;
    attrackSpeed = 100;
    attrackRange = YUANWEI;
    attrackInterval = 1.3f;
    skillTime = 30.0f;
    isSkillAuto = false;
    positionType = down;
    damageType = phisical;
    selectedType = upanddown;
    blockedType = down;
    attackNum = 34;
    dieNum = 19;
    idleNum = 36;
    startNum = 36;
    attackReachNum = 22;
    //技能参数不同干员需要哪些单独初始化

    duringskillNum = 17;

    /***********************************/

    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

    return true;
}

Yinhui* Yinhui::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Yinhui::create(filename);

    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;

    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Yinhui::initSkillAnimation()
{
    this->duringskill1 = Employee::createAnimate(1, name.c_str(), "duringskill", duringskillNum, 23, attrackInterval/ duringskillNum);
    this->duringskill2 = Employee::createAnimate(2, name.c_str(), "duringskill", duringskillNum, 23, attrackInterval / duringskillNum);
    duringskill1->retain();
    duringskill2->retain();
}

void Yinhui::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    unscheduleUpdate();

    attrack = 2391;
    attrackNumber = 6;
    defend = 134;
    this->stopAllActions();
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (duringskill1) : (duringskill2));
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Yinhui::skillSPUpdate), skillTime / static_cast<float>(spMAX));
    schedule(CC_SCHEDULE_SELECTOR(Yinhui::skillAttrackUpdate), attrackInterval);
    schedule(CC_SCHEDULE_SELECTOR(Yinhui::skillHealthUpdate));

    scheduleOnce(CC_SCHEDULE_SELECTOR(Yinhui::skillOverUpdate), skillTime);
}

void Yinhui::update(float dt)
{
    Employee::update(dt);
}

void Yinhui::skillSPUpdate(float dt)
{
    if (sp > 0)
        sp--;
}

void Yinhui::skillAttrackUpdate(float dt)
{
    if (searchEnemyByType(zhenyinzhan[direction0], zhenyinzhanRange))
        attrackSelectedEnemy();
}

void Yinhui::skillHealthUpdate(float dt)
{
    if (health <= 0)
    {
        this->stopAllActions();
        auto animation = Animate::create((direction0 == left || direction0 == front) ? (die1) : (die2));
        auto callbackDie = CallFunc::create([this]() {
            auto map = dynamic_cast<MapScene*>(this->getParent());
            this->releaseAnimation();
            this->removeFromParent();

            auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
            auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

            map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
            /*******************再部署时间******************/
            employeelist->reputtingLoading();

            releaseAllBlockedEnemy();//释放阻挡敌人

            employeelist->setOpacity(100);
            employeelist->setIsadded(false);
            employeelist->setReputNum(employeelist->getReputNum() + 1);

            MapInformation::getInstance()->allEmployeeInMap.eraseObject(this);
            });
        this->runAction(Sequence::create(animation, callbackDie, nullptr));
    }
}

void Yinhui::skillOverUpdate(float dt)
{
    attrack = 865;
    attrackNumber = 1;
    defend = 447;

    unschedule(CC_SCHEDULE_SELECTOR(Yinhui::skillSPUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Yinhui::skillAttrackUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Yinhui::skillHealthUpdate));



    lastState = employeeStateIdle;
    presentState = employeeStateIdle;
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
    animation->setTag(employeeStateIdle);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

}

void Yinhui::releaseSkillAnimation()
{
    duringskill1->release();
    duringskill2->release();
}




bool Baimianxiao::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "baimianxiao";
    healthMAX = 1610;
    health = 1610;
    spMAX = 100;
    sp = 85;
    attrack = 411;
    defend = 150;
    magicDefend = 0;
    blockNumber = 1;
    remainBlockNumber = 1;
    attrackNumber = 3;
    attrackSpeed = 100;
    attrackRange = QUNNAI;
    attrackInterval = 2.85f;
    skillTime = 40.0f;
    isSkillAuto = false;
    positionType = up;
    damageType = nurse;
    selectedType = upanddown;
    blockedType = up;
    attackNum = 23;
    dieNum = 15;
    idleNum = 25;
    startNum = 12;
    attackReachNum = 16;
    //技能参数不同干员需要哪些单独初始化

    duringskillNum = 11;

    /***********************************/

    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

    return true;
}

Baimianxiao* Baimianxiao::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Baimianxiao::create(filename);

    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;

    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Baimianxiao::initSkillAnimation()
{
    this->duringskill1 = Employee::createAnimate(1, name.c_str(), "duringskill", duringskillNum, 53, 0.75f / duringskillNum);
    this->duringskill2 = Employee::createAnimate(2, name.c_str(), "duringskill", duringskillNum, 53, 0.75f / duringskillNum);
    duringskill1->retain();
    duringskill2->retain();
}

void Baimianxiao::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    unscheduleUpdate();

    attrackInterval = 0.75f;
    
    this->stopAllActions();
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (duringskill1) : (duringskill2));
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Baimianxiao::skillSPUpdate), skillTime / static_cast<float>(spMAX));
    schedule(CC_SCHEDULE_SELECTOR(Baimianxiao::skillAttrackUpdate), attrackInterval);
    schedule(CC_SCHEDULE_SELECTOR(Baimianxiao::skillHealthUpdate));

    scheduleOnce(CC_SCHEDULE_SELECTOR(Baimianxiao::skillOverUpdate), skillTime);
}

void Baimianxiao::update(float dt)
{
    Employee::update(dt);
}

void Baimianxiao::skillSPUpdate(float dt)
{
    if (sp > 0)
        sp--;
}

void Baimianxiao::skillAttrackUpdate(float dt)
{
    if (searchEnemyByType(naofeitai[direction0], naofeitaiRange))
        attrackSelectedEnemy();
}

void Baimianxiao::skillHealthUpdate(float dt)
{
    if (health <= 0)
    {
        this->stopAllActions();
        auto animation = Animate::create((direction0 == left || direction0 == front) ? (die1) : (die2));
        auto callbackDie = CallFunc::create([this]() {
            auto map = dynamic_cast<MapScene*>(this->getParent());
            this->releaseAnimation();
            this->removeFromParent();

            auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
            auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

            map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
            /*******************再部署时间******************/
            employeelist->reputtingLoading();

            releaseAllBlockedEnemy();//释放阻挡敌人

            employeelist->setOpacity(100);
            employeelist->setIsadded(false);
            employeelist->setReputNum(employeelist->getReputNum() + 1);

            MapInformation::getInstance()->allEmployeeInMap.eraseObject(this);
            });
        this->runAction(Sequence::create(animation, callbackDie, nullptr));
    }
}

void Baimianxiao::skillOverUpdate(float dt)
{
    attrackInterval = 2.85f;

    unschedule(CC_SCHEDULE_SELECTOR(Baimianxiao::skillSPUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Baimianxiao::skillAttrackUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Baimianxiao::skillHealthUpdate));



    lastState = employeeStateIdle;
    presentState = employeeStateIdle;
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
    animation->setTag(employeeStateIdle);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

}

void Baimianxiao::releaseSkillAnimation()
{
    duringskill1->release();
    duringskill2->release();
}




bool Nengtianshi::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "nengtianshi";
    healthMAX = 1673;
    health = 1673;
    spMAX = 30;
    sp = 20;
    attrack = 657;
    defend = 161;
    magicDefend = 0;
    blockNumber = 1;
    remainBlockNumber = 1;
    attrackNumber = 1;
    attrackSpeed = 100;
    attrackRange = SUJU;
    attrackInterval = 1.0f;
    skillTime = 15.0f;
    isSkillAuto = true;
    positionType = up;
    damageType = phisical;
    selectedType = upanddown;
    blockedType = up;
    attackNum = 19;
    dieNum = 12;
    idleNum = 61;
    startNum = 10;
    attackReachNum = 13;
    //技能参数不同干员需要哪些单独初始化

    duringskillNum = 19;

    /***********************************/

    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    schedule(CC_SCHEDULE_SELECTOR(Nengtianshi::skillTouchAuto));
    scheduleUpdate();

    return true;
}

Nengtianshi* Nengtianshi::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Nengtianshi::create(filename);

    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;

    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Nengtianshi::initSkillAnimation()
{
    this->duringskill1 = Employee::createAnimate(1, name.c_str(), "duringskill", duringskillNum, 15, attrackInterval / duringskillNum);
    this->duringskill2 = Employee::createAnimate(2, name.c_str(), "duringskill", duringskillNum, 15, attrackInterval / duringskillNum);
    duringskill1->retain();
    duringskill2->retain();
}

void Nengtianshi::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Nengtianshi::skillTouchAuto));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    unscheduleUpdate();


    this->stopAllActions();
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (duringskill1) : (duringskill2));
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Nengtianshi::skillSPUpdate), skillTime / static_cast<float>(spMAX));
    schedule(CC_SCHEDULE_SELECTOR(Nengtianshi::skillAttrackUpdate), attrackInterval);
    schedule(CC_SCHEDULE_SELECTOR(Nengtianshi::skillHealthUpdate));

    scheduleOnce(CC_SCHEDULE_SELECTOR(Nengtianshi::skillOverUpdate), skillTime);
}

void Nengtianshi::update(float dt)
{
    Employee::update(dt);
}

void Nengtianshi::skillTouchAuto(float dt)
{
    if (sp == spMAX)
    {
        AudioEngine::play2d(".\\employee\\" + name + "\\skill.mp3");
        this->skill();
    }
}

void Nengtianshi::skillSPUpdate(float dt)
{
    if (sp > 0)
        sp--;
}

void Nengtianshi::skillAttrackUpdate(float dt)
{
    if (searchEnemyByType(suju[direction0], sujuRange))
    {
        attrackSelectedEnemy();
        attrackSelectedEnemy();
        attrackSelectedEnemy();
        attrackSelectedEnemy();
        attrackSelectedEnemy();
    }
}

void Nengtianshi::skillHealthUpdate(float dt)
{
    if (health <= 0)
    {
        this->stopAllActions();
        auto animation = Animate::create((direction0 == left || direction0 == front) ? (die1) : (die2));
        auto callbackDie = CallFunc::create([this]() {
            auto map = dynamic_cast<MapScene*>(this->getParent());
            this->releaseAnimation();
            this->removeFromParent();

            auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
            auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

            map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
            /*******************再部署时间******************/
            employeelist->reputtingLoading();

            releaseAllBlockedEnemy();//释放阻挡敌人

            employeelist->setOpacity(100);
            employeelist->setIsadded(false);
            employeelist->setReputNum(employeelist->getReputNum() + 1);

            MapInformation::getInstance()->allEmployeeInMap.eraseObject(this);
            });
        this->runAction(Sequence::create(animation, callbackDie, nullptr));
    }
}

void Nengtianshi::skillOverUpdate(float dt)
{

    unschedule(CC_SCHEDULE_SELECTOR(Nengtianshi::skillSPUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Nengtianshi::skillAttrackUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Nengtianshi::skillHealthUpdate));



    lastState = employeeStateIdle;
    presentState = employeeStateIdle;
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
    animation->setTag(employeeStateIdle);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    schedule(CC_SCHEDULE_SELECTOR(Nengtianshi::skillTouchAuto));
    scheduleUpdate();

}

void Nengtianshi::releaseSkillAnimation()
{
    duringskill1->release();
    duringskill2->release();
}




bool Dekesasi::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "dekesasi";
    healthMAX = 1950;
    health = 1950;
    spMAX = 40;
    sp = 30;
    attrack = 594;
    defend = 343;
    magicDefend = 0;
    blockNumber = 2;
    remainBlockNumber = 2;
    attrackNumber = 1;
    attrackSpeed = 100;
    attrackRange = XIANFENG;
    attrackInterval = 1.05f;
    skillTime = 1.6f;
    isSkillAuto = false;
    positionType = down;
    damageType = phisical;
    selectedType = down;
    blockedType = down;
    attackNum = 32;
    dieNum = 9;
    idleNum = 28;
    startNum = 16;
    attackReachNum = 14;
    //技能参数不同干员需要哪些单独初始化
    duringskillNum = 40;
    /***********************************/

    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

    return true;
}

Dekesasi* Dekesasi::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Dekesasi::create(filename);

    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;

    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Dekesasi::initSkillAnimation()
{
    this->duringskill1 = Employee::createAnimate(1, name.c_str(), "duringskill", duringskillNum, 1, 0.04f);
    this->duringskill2 = Employee::createAnimate(2, name.c_str(), "duringskill", duringskillNum, 1, 0.04f);
    duringskill1->retain();
    duringskill2->retain();
}

void Dekesasi::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    unscheduleUpdate();

    attrack = 1009;
    attrackNumber = 20;
    damageType = magical;
    this->stopAllActions();

    auto map = static_cast<MapScene*>(this->getParent());
    map->setC((map->getC() + 12)>99?(99):(map->getC() + 12));

    auto animation = Animate::create((direction0 == left || direction0 == front) ? (duringskill1) : (duringskill2));

    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Dekesasi::skillSPUpdate), skillTime / static_cast<float>(spMAX));
    scheduleOnce(CC_SCHEDULE_SELECTOR(Dekesasi::skillAttrackUpdate), skillTime/2);
    schedule(CC_SCHEDULE_SELECTOR(Dekesasi::skillHealthUpdate));

    scheduleOnce(CC_SCHEDULE_SELECTOR(Dekesasi::skillOverUpdate), skillTime);
}

void Dekesasi::update(float dt)
{
    Employee::update(dt);
}

void Dekesasi::skillSPUpdate(float dt)
{
    if (sp > 0)
        sp--;
}

void Dekesasi::skillAttrackUpdate(float dt)
{
    if (searchEnemyByType(jianyu, jianyuRange))
    {
        attrackSelectedEnemy();
        attrackSelectedEnemy();
    }
}

void Dekesasi::skillHealthUpdate(float dt)
{
    if (health <= 0)
    {
        this->stopAllActions();
        auto animation = Animate::create((direction0 == left || direction0 == front) ? (die1) : (die2));
        auto callbackDie = CallFunc::create([this]() {
            auto map = dynamic_cast<MapScene*>(this->getParent());
            this->releaseAnimation();
            this->removeFromParent();

            auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
            auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

            map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
            /*******************再部署时间******************/
            employeelist->reputtingLoading();

            releaseAllBlockedEnemy();//释放阻挡敌人

            employeelist->setOpacity(100);
            employeelist->setIsadded(false);
            employeelist->setReputNum(employeelist->getReputNum() + 1);

            MapInformation::getInstance()->allEmployeeInMap.eraseObject(this);
            });
        this->runAction(Sequence::create(animation, callbackDie, nullptr));
    }
}

void Dekesasi::skillOverUpdate(float dt)
{
    attrack = 594;
    attrackNumber = 1;
    damageType = phisical;

    unschedule(CC_SCHEDULE_SELECTOR(Dekesasi::skillSPUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Dekesasi::skillHealthUpdate));



    lastState = employeeStateIdle;
    presentState = employeeStateIdle;
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
    animation->setTag(employeeStateIdle);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

}

void Dekesasi::releaseSkillAnimation()
{
    duringskill1->release();
    duringskill2->release();
}




bool Taojinniang::initWithFile(const char* filename)
{
    if (!Employee::initWithFile(filename))
    {
        return false;
    }
    /************基础数据初始化*********/
    name = "taojinniang";
    healthMAX = 1565;
    health = 1565;
    spMAX = 22;
    sp = 13;
    attrack = 520;
    defend = 323;
    magicDefend = 0;
    blockNumber = 1;
    remainBlockNumber = 1;
    attrackNumber = 1;
    attrackSpeed = 100;
    attrackRange = XIANFENG;
    attrackInterval = 1.3f;
    skillTime = 8.0f;
    isSkillAuto = false;
    positionType = down;
    damageType = phisical;
    selectedType = down;
    blockedType = down;
    attackNum = 34;
    dieNum = 18;
    idleNum = 64;
    startNum = 11;
    attackReachNum = 18;
    //技能参数不同干员需要哪些单独初始化
    beforeskillNum = 22;
    duringskillNum = 56;

    /***********************************/

    initAnimation();

    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

    return true;
}

Taojinniang* Taojinniang::createSprite(const char* filename, int direction0, Vec2 position, Vec2 positionXY)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto p = Taojinniang::create(filename);

    p->setDirection0(direction0);
    p->setPosition(Vec2(origin.x, origin.y) + position);
    p->positionXY = positionXY;

    p->initSkillAnimation();
    p->addSkillList();

    return p;
}

void Taojinniang::initSkillAnimation()
{
    this->beforeskill1 = Employee::createAnimate(1, name.c_str(), "beforeskill", beforeskillNum, 1, 0.04f);
    this->beforeskill2 = Employee::createAnimate(2, name.c_str(), "beforeskill", beforeskillNum, 1, 0.04f);
    this->duringskill1 = Employee::createAnimate(1, name.c_str(), "duringskill", duringskillNum, 3, 0.04f);
    this->duringskill2 = Employee::createAnimate(2, name.c_str(), "duringskill", duringskillNum, 3, 0.04f);
    beforeskill1->retain();
    beforeskill2->retain();
    duringskill1->retain();
    duringskill2->retain();
}

void Taojinniang::skill()
{
    unschedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    unscheduleUpdate();

    remainBlockNumber = 0;
    releaseAllBlockedEnemy();

    this->stopAllActions();
    auto animation1 = Animate::create((direction0 == left || direction0 == front) ? (beforeskill1) : (beforeskill2));
    auto animation2 = Animate::create((direction0 == left || direction0 == front) ? (duringskill1) : (duringskill2));
    auto animation = Sequence::create(animation1, animation2, nullptr);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Taojinniang::skillSPUpdate), skillTime / static_cast<float>(spMAX));
    schedule(CC_SCHEDULE_SELECTOR(Taojinniang::skillCUpdate), 0.571f);
    schedule(CC_SCHEDULE_SELECTOR(Taojinniang::skillHealthUpdate));

    scheduleOnce(CC_SCHEDULE_SELECTOR(Taojinniang::skillOverUpdate), skillTime);
}

void Taojinniang::update(float dt)
{
    Employee::update(dt);
}

void Taojinniang::skillSPUpdate(float dt)
{
    if (sp > 0)
        sp--;
}

void Taojinniang::skillCUpdate(float dt)
{
    auto map = static_cast<MapScene*>(this->getParent());
    map->setC((map->getC() + 1)>99?(99):(map->getC() + 1));
}

void Taojinniang::skillHealthUpdate(float dt)
{
    if (health <= 0)
    {
        this->stopAllActions();
        auto animation = Animate::create((direction0 == left || direction0 == front) ? (die1) : (die2));
        auto callbackDie = CallFunc::create([this]() {
            auto map = dynamic_cast<MapScene*>(this->getParent());
            this->releaseAnimation();
            this->removeFromParent();

            auto puttingLayer = static_cast<Layer*>(map->getChildByTag(103));
            auto employeelist = static_cast<employeeList<MapScene>*>(puttingLayer->getChildByTag(getEmployeeListType()));

            map->setRemainPuttingNumber(map->getRemainPuttingNumber() + 1);
            /*******************再部署时间******************/
            employeelist->reputtingLoading();

            releaseAllBlockedEnemy();//释放阻挡敌人

            employeelist->setOpacity(100);
            employeelist->setIsadded(false);
            employeelist->setReputNum(employeelist->getReputNum() + 1);

            MapInformation::getInstance()->allEmployeeInMap.eraseObject(this);
            });
        this->runAction(Sequence::create(animation, callbackDie, nullptr));
    }
}

void Taojinniang::skillOverUpdate(float dt)
{

    unschedule(CC_SCHEDULE_SELECTOR(Taojinniang::skillSPUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Taojinniang::skillCUpdate));
    unschedule(CC_SCHEDULE_SELECTOR(Taojinniang::skillHealthUpdate));

    remainBlockNumber = 1;

    lastState = employeeStateIdle;
    presentState = employeeStateIdle;
    auto animation = Animate::create((direction0 == left || direction0 == front) ? (idle1) : (idle2));
    animation->setTag(employeeStateIdle);
    this->runAction(animation);

    schedule(CC_SCHEDULE_SELECTOR(Employee::spIncreaseUpdate), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(Employee::stateUpdate));
    scheduleUpdate();

}

void Taojinniang::releaseSkillAnimation()
{
    beforeskill1->release();
    beforeskill2->release();
    duringskill1->release();
    duringskill2->release();
}