#include "HelloGame.h"
#include "LZBlockSprite.h"



HelloGame::HelloGame()
{
}


HelloGame::~HelloGame()
{
}

cocos2d::Scene* HelloGame::scene()
{
	return HelloGame::create();
}

bool HelloGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	// 鼠标监听注册
	cocos2d::EventListenerMouse* _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(HelloGame::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	initWithPhysics();
	_physicsWorld->setGravity(Point::ZERO); // 关闭重力
//	_physicsWorld->setDebugDrawMask(true ? PhysicsWorld::DEBUGDRAW_ALL : PhysicsWorld::DEBUGDRAW_NONE);
//	_physicsWorld->setFixedUpdateRate(180);
	// 设置背景层颜色
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();// 这个点才是默认的坐标原点

	auto lyc = LayerColor::create(Color4B::WHITE, visibleSize.width + origin.x, visibleSize.height + origin.y);
	addChild(lyc, -1);

	// 初始化外壁
	auto wall = Node::create();
	wall->addComponent(PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.1f, 1, 0.0f)));
	wall->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
	addChild(wall);

	// 初始化小球
	auto ball = Sprite::create("ball.png");
	if (ball != nullptr)
	{
		ball->setScale(0.7f);
		ball->setPosition(500, 300);
		auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0.1f, 1, 0.0f));
		ballBody->setContactTestBitmask(0xFFFFFFFF); // 设置碰撞监听开关
		ball->addComponent(ballBody);
		ballBody->setVelocity(Vec2(500, 100));
		addChild(ball, 1, 88);
	}

	// 初始化拍子
	auto plant = Sprite::create("YellowSquare.png");
	if (plant != nullptr)
	{
		plant->setScaleX(1.5f);
		plant->setScaleY(0.3f);
		plant->setPosition(200, 150);
		addChild(plant, 0, 77);
		auto plantBody = PhysicsBody::createBox(plant->getContentSize(), PhysicsMaterial(0.1f, 1, 0.0f));
		plantBody->setContactTestBitmask(0xFFFFFFFF); // 设置碰撞监听开关
		plantBody->setDynamic(false);
		plant->addComponent(plantBody);
	}


	// 初始化砖块
	for (int row = 0; row < 10; ++row)
	{
		for (int col = 0; col < 15; ++col)
		{
			auto block = Sprite::create("CyanSquare.png");
			if (block != nullptr)
			{
				block->setScaleX(0.5f);
				block->setScaleY(0.25f);
				Size sz(block->getContentSize().width*0.5f, block->getContentSize().height*0.25f);
			
				Vec2 vecStart(50,400);
				//Vec2 vecStart((visibleSize.width - (sz.width + 2) * 10) / 2, (visibleSize.height - (sz.height + 1) * 20) / 2);
				block->setPosition(vecStart.x + (sz.width + 2) * col, vecStart.y + (sz.height + 1) * row);
				addChild(block, 0, 99);

				auto blockBody = PhysicsBody::createBox(block->getContentSize(), PhysicsMaterial(0.1f, 1, 0.0f));
				blockBody->setContactTestBitmask(0xFFFFFFFF); // 设置碰撞监听开关
				blockBody->setDynamic(false);
				block->addComponent(blockBody);
			}
		}
	}


	// 碰撞监听注册
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloGame::onBeginContact,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}


void HelloGame::onMouseMove(cocos2d::Event* event)
{
	EventMouse* e = (EventMouse*)event;
	auto plant = getChildByTag(77);
	if (plant)
	{
		plant->setPositionX(e->getLocationInView().x);
	}
}

bool HelloGame::onBeginContact(PhysicsContact & contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA->getTag() == 99)
	{
		nodeA->removeFromParentAndCleanup(true);
	}
	else if (nodeB->getTag() == 99)
	{
		nodeB->removeFromParentAndCleanup(true);
	}
	return true;
}
