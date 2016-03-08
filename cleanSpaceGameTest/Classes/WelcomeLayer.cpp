#include"WelcomeLayer.h"
#include"SelectLayer.h"

USING_NS_CC;

CCScene* WelcomeLayer::scene()
{
	CCScene* scene = CCScene::create();
	WelcomeLayer* layer = WelcomeLayer::create();
	scene->addChild(layer);
	return scene;
}

bool WelcomeLayer::init()
{
	if(!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("inkmoo_flash.plist");
	CCSprite* sp = CCSprite::createWithSpriteFrameName("inkmoo_001.png");
	sp->setScale(1.5f);
	sp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(sp);

	CCArray* frames = CCArray::create();
	
	for(int i = 1; i < 79; i++)
	{
		CCString* strName = CCString::createWithFormat("inkmoo_%03d.png", i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName->getCString());
		frames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, 0.05f);
	CCAnimate* animate = CCAnimate::create(animation);
	sp->runAction(animate);

	this->scheduleOnce(schedule_selector(WelcomeLayer::transitionToSelectLayer), 4);

	return true;
}

void WelcomeLayer::transitionToSelectLayer(float dt)
{
	CCScene* scene = SelectLayer::scene();
	CCTransitionProgressInOut* transitionScene = CCTransitionProgressInOut::create(1.2f, scene);
	CCDirector::sharedDirector()->replaceScene(transitionScene);
}