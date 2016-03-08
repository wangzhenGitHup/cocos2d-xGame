#include"WelcomeLayer.h"
#include"GameLayer.h"
#include"SimpleAudioEngine.h"


using namespace CocosDenshion;
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
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot_background.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");

	CCSprite* bgSp = CCSprite::createWithSpriteFrameName("background.png");
	bgSp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bgSp);

	CCSprite* gameNameSp = CCSprite::createWithSpriteFrameName("shoot_copyright.png");
	gameNameSp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(gameNameSp);

	CCSprite* loadingSp = CCSprite::createWithSpriteFrameName("game_loading1.png");
	loadingSp->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 120));
	this->addChild(loadingSp);

	CCAnimation* loadingAnimation = CCAnimation::create();
	loadingAnimation->setDelayPerUnit(0.2f);

	loadingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
	loadingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
	loadingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
	loadingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));


	CCAnimate* animate = CCAnimate::create(loadingAnimation);
	CCRepeat* repeat = CCRepeat::create(animate, 5);
	CCCallFunc* funcDone = CCCallFunc::create(this, callfunc_selector(WelcomeLayer::loadingDone));
	CCSequence* seq = CCSequence::create(repeat, funcDone, NULL);
	loadingSp->runAction(seq);

	preLoadMusic();
	return true;
}

void WelcomeLayer::loadingDone()
{
	CCScene* scene = GameLayer::scene();
	CCTransitionMoveInB* transitionScene = CCTransitionMoveInB::create(0.5f, scene);
	CCDirector::sharedDirector()->replaceScene(transitionScene);
}

bool WelcomeLayer::isHaveSaveXml()
{
	if(CCUserDefault::sharedUserDefault()->getBoolForKey("planescore.xml"))
	{
		return true;
	}
	CCUserDefault::sharedUserDefault()->setBoolForKey("planescore.xml", true);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("highestscore", 0);
	CCUserDefault::sharedUserDefault()->flush();
	return false;
}

void WelcomeLayer::getHighestHistoryScore()
{
	if(isHaveSaveXml())
	{
		CCUserDefault::sharedUserDefault()->getIntegerForKey("highestscore");
	}
}

void WelcomeLayer::preLoadMusic()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/game_music.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/achievement.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/big_spaceship_flying.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/bullet.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/button.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy1_down.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy2_down.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy3_down.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/game_over.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/get_bomb.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/get_double_laser.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/out_porp.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/use_bomb.mp3");
}