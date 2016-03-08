#ifndef  __com__wangzhen__cleanspacegame__welcomelayer__h__
#define  __com__wangzhen__cleanspacegame__welcomelayer__h__

#include"cocos2d.h"

class WelcomeLayer : public cocos2d::CCLayerColor
{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);

public:
	void transitionToSelectLayer(float dt);

};

#endif