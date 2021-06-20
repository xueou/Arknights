#pragma once
#include "cocos2d.h"
#include "AudioEngine.h"

class MainMap :public cocos2d::Layer
{
public:
	MainMap();
	~MainMap();

	void menuCallbackForSrartMap1(Ref* pSender);
	void menuCallbackForSrartMap2(Ref* pSender);
	void menuCallbackForSrartMap3(Ref* pSender);

	bool init();

	CREATE_FUNC(MainMap);
};