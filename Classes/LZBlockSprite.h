#pragma once

#include "cocos2d.h"
class LZBlockSprite : public cocos2d::Sprite
{
public:
	LZBlockSprite();
	~LZBlockSprite();

private:
	int _nLife;
};

