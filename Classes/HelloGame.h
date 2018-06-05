#pragma once

#include "cocos2d.h"

USING_NS_CC;

class HelloGame : public cocos2d::Scene
{
public:
	HelloGame();
	~HelloGame();

	virtual bool init() override;

	static cocos2d::Scene* scene();


	void onMouseMove(cocos2d::Event* event);

	bool onBeginContact(PhysicsContact & contact);
	// implement the "static create()" method manually
	CREATE_FUNC(HelloGame);
};


