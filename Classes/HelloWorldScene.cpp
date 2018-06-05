/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "AppMacros.h"

USING_NS_CC;

template <typename T> std::string tostr(const T& t) { std::ostringstream os; os << t; return os.str(); }

Scene* HelloWorld::scene()
{
     return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    


	this->initWithPhysics();
	//_physicsWorld->setDebugDrawMask(true ? PhysicsWorld::DEBUGDRAW_ALL : PhysicsWorld::DEBUGDRAW_NONE);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();// 这个点才是默认的坐标原点

	auto lyc = LayerColor::create(Color4B::WHITE, visibleSize.width + origin.x, visibleSize.height + origin.y);
	addChild(lyc, -1);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));

    closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label


	_pLabel = Label::createWithTTF("Hello Bird", "fonts/arial.ttf", TITLE_FONT_SIZE);
	// add the label as a child to this layer
	this->addChild(_pLabel, 1);

    // position the label on the center of the screen
	_pLabel->setPosition(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - _pLabel->getContentSize().height);
	_pLabel->setColor(Color3B(255, 122, 0));
	_pLabel->enableShadow(Color4B::GREEN);



	auto spriteBox = Sprite::create("block.png");
	addChild(spriteBox,0 ,88);
	
	spriteBox->setPosition(origin.x + visibleSize.width / 2, origin.x + visibleSize.height / 2);

	//spriteBox->runAction(RepeatForever::create(RotateBy::create(3, 90)));

	//auto sca = ScaleBy::create(1, 2);
	//spriteBox->runAction(RepeatForever::create(Sequence::create(sca, sca->reverse(), DelayTime::create(0.3f), nullptr)));

	auto physicsBody = PhysicsBody::createBox(spriteBox->getContentSize(), PhysicsMaterial(0.3f, 1.0f, 0.5f));
	physicsBody->setGravityEnable(true);
	//physicsBody->setVelocity(Vec2(cocos2d::random(-100, 100), cocos2d::random(-100, 100)));
	spriteBox->addComponent(physicsBody);
	

	auto spriteBoxG = Sprite::create("Birds_1.png");
	spriteBoxG->setPosition(Vec2(500,500));	
	spriteBoxG->runAction(RepeatForever::create(Sequence::create(MoveBy::create(3,Vec2(500,0)), MoveBy::create(3, Vec2(-500, 0)), nullptr)));
	auto physicsBody2 = PhysicsBody::createBox(spriteBoxG->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody2->setGravityEnable(false);
	physicsBody2->setVelocity(Vec2(cocos2d::random(-400, 400), cocos2d::random(-400, 400)));
	spriteBoxG->addComponent(physicsBody2);
	addChild(spriteBoxG);


	auto node = Node::create();
	node->addComponent(PhysicsBody::createEdgeBox(Director::getInstance()->getSafeAreaRect().size, PhysicsMaterial(0.5f, 0.5f, 0.5f)));
	node->setPosition(origin.x + visibleSize.width / 2,origin.y + visibleSize.height/2);
	this->addChild(node);
	/*
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize / 2) + origin);

    // add the sprite as a child to this layer
    this->addChild(sprite);
	*/

    auto drawNode = DrawNode::create();
    drawNode->setPosition(Vec2(0, 0));
    Rect safeArea = Director::getInstance()->getSafeAreaRect();
    drawNode->drawRect(safeArea.origin, safeArea.origin + safeArea.size, Color4F::BLUE);
	addChild(drawNode);

	auto drawMouseC = DrawNode::create(DEFAULT_LINE_WIDTH-1);
	drawMouseC->setPosition(Vec2(0, 0));
	drawMouseC->drawCircle(Vec2(0, 0), 10, 360, 36, false, Color4F::RED);
	drawMouseC->drawPoint(Vec2(0, 0), 2, Color4F::BLUE);
	drawMouseC->setVisible(false);
	addChild(drawMouseC,10,77);




	cocos2d::EventListenerMouse* _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	_mouseListener->onMouseMove = [&](cocos2d::Event* event) {
		EventMouse* e = (EventMouse*)event;
		if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			auto dcc = getChildByTag(77);
			if (dcc)
			{
				dcc->setPosition(e->getLocationInView());
			}

			auto dccBd = getChildByTag(44);
			if (dccBd)
			{
				dccBd->setPosition(e->getLocationInView());
			}
		}
	};
	_mouseListener->onMouseUp = [&](cocos2d::Event* event) {
		EventMouse* e = (EventMouse*)event;
		if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			auto dcc = getChildByTag(77);
			if (dcc)
			{
				dcc->setVisible(false);
			}

			auto dccBd = getChildByTag(44);
			if (dccBd)
			{
				removeChild(dccBd);
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    return true;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onMouseDown(cocos2d::Event* event)
{
	EventMouse* e = (EventMouse*)event;
	if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{
		auto box = getChildByTag(88);
		if (box)
		{
			Sprite *spi = dynamic_cast<Sprite *>(box);
			if (NULL != spi)
			{
				auto jmp = spi->getActionByTag(99);
				if (jmp == nullptr)
				{
					
					jmp = Spawn::createWithTwoActions(JumpBy::create(0.5, Vec2(150, 0), 100, 1), RotateBy::create(0.5, 90));
					jmp->setTag(99);
					spi->runAction(jmp);
				}

			}	
		}

		auto dcc = getChildByTag(77);
		if (dcc)
		{
			
			DrawNode *dnode = dynamic_cast<DrawNode *>(dcc);
			if (dnode)
			{
				dnode->setVisible(true);
				dnode->setPosition(e->getLocationInView());
			}
		}

		auto ps = _physicsWorld->getShape(e->getLocationInView());
		if (ps != nullptr)
		{
			auto pb = ps->getBody();
			if (pb != nullptr)
			{
				auto tnode = Node::create();
				auto tBody = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
				tBody->setDynamic(false);
				tnode->addComponent(tBody);
				tnode->setTag(44);
				tnode->setPosition(e->getLocationInView());
				addChild(tnode);
				PhysicsJointPin* joint = PhysicsJointPin::construct(tBody, pb, e->getLocationInView());
				_physicsWorld->addJoint(joint);
			}
		}

	}
	else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		auto box = getChildByTag(88);
		if (box)
		{
			Sprite *spi = dynamic_cast<Sprite *>(box);
			if (NULL != spi)
			{
				auto jmp = spi->getActionByTag(99);
				if (jmp == nullptr)
				{
					jmp = Spawn::createWithTwoActions(JumpBy::create(0.5, Vec2(-150, 0), 100, 1), RotateBy::create(0.5, -90));
					jmp->setTag(99);
					spi->runAction(jmp);
				}

			}
		}
	}
}

