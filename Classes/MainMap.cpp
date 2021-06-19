#include "cocos2d.h"
#include "MainMap.h"
#include "MapScene.h"
USING_NS_CC;

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

MainMap::MainMap()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto mapBackground = Sprite::create("mapBackground.jpg");
	if (mapBackground == nullptr)
	{
		problemLoading("'mapBackground.jpg'");
	}
	else
	{
		mapBackground->setAnchorPoint(Vec2::ZERO);
		mapBackground->setPosition(Vec2(origin.x, origin.y));
		this->addChild(mapBackground);
	}

	auto startMap1 = MenuItemImage::create("map1.jpg", "map1.jpg", CC_CALLBACK_1(MainMap::menuCallbackForSrartMap1, this));
	startMap1->setPosition(Vec2(origin.x+200, origin.y+200));
	auto mainMap = Menu::create(startMap1, NULL);
	mainMap->setPosition(Vec2(origin.x, origin.y));
	this->addChild(mainMap);
}

MainMap::~MainMap()
{
	
}

bool MainMap::init()
{
	//auto listen = EventListenerTouchOneByOne::create();
	//listen->setSwallowTouches(true);
	
	return true;
}

void MainMap::menuCallbackForSrartMap1(Ref* pSender)
{
	auto mapScene1 = MapScene1::create();
	Director::getInstance()->pushScene(mapScene1);
}