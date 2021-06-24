#include "cocos2d.h"
#include "MainMap.h"
#include "MapScene.h"
#include "AudioEngine.h"
USING_NS_CC;

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

MainMap::MainMap()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto mapBackground = Sprite::create("mapBackground.png");
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

	auto startMap1 = MenuItemImage::create("map1.png", "map1.png", CC_CALLBACK_1(MainMap::menuCallbackForSrartMap1, this));
	startMap1->setPosition(Vec2(origin.x+250, origin.y+250));
	auto startMap2 = MenuItemImage::create("map2.png", "map2.png", CC_CALLBACK_1(MainMap::menuCallbackForSrartMap2, this));
	startMap2->setPosition(Vec2(origin.x + 650, origin.y + 550));
	auto startMap3 = MenuItemImage::create("map3.png", "map3.png", CC_CALLBACK_1(MainMap::menuCallbackForSrartMap3, this));
	startMap3->setPosition(Vec2(origin.x + 1050, origin.y + 400));
	
	auto mainMap = Menu::create(startMap1, startMap2, startMap3, NULL);
	mainMap->setPosition(Vec2(origin.x, origin.y));
	this->addChild(mainMap);

	AudioEngine::play2d("mainmap.mp3", true, 0.5f);
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
	AudioEngine::stopAll();
	auto mapScene1 = MapScene1::create();
	Director::getInstance()->pushScene(mapScene1);
	AudioEngine::play2d("0-1.mp3", false, 0.5f);
}

void MainMap::menuCallbackForSrartMap2(Ref* pSender)
{
	AudioEngine::stopAll();
	auto mapScene2 = MapScene2::create();
	Director::getInstance()->pushScene(mapScene2);
	AudioEngine::play2d("H0-1.mp3", false, 0.5f);
}

void MainMap::menuCallbackForSrartMap3(Ref* pSender)
{
	AudioEngine::stopAll();
	auto mapScene3 = MapScene3::create();
	Director::getInstance()->pushScene(mapScene3);
	AudioEngine::play2d("WD-EX-8.mp3",false,0.5f);
}