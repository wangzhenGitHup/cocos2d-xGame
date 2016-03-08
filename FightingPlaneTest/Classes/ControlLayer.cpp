#include"ControlLayer.h"
#include"SimpleAudioEngine.h"
#include"global.h"

using namespace CocosDenshion;
USING_NS_CC;

ControlLayer::ControlLayer()
{
	scoreItem = NULL;
	pPauseItem = NULL;
}

ControlLayer::~ControlLayer()
{}

bool ControlLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* normalSp = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
	CCSprite* pressedSp = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));

	pPauseItem = CCMenuItemImage::create();
	pPauseItem->initWithNormalSprite(normalSp, pressedSp, NULL, this, menu_selector(ControlLayer::menuCallback));
	pPauseItem->setPosition(ccp(normalSp->getContentSize().width / 2 + 10, winSize.height - normalSp->getContentSize().height / 2 - 10));
	CCMenu* menu = CCMenu::create(pPauseItem, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu, 101);

	scoreItem = CCLabelBMFont::create("0", "font/font.fnt");
	scoreItem->setAnchorPoint(ccp(0, 0.5f));
	scoreItem->setColor(ccc3(143, 146, 147));
	scoreItem->setPosition(ccp(pPauseItem->getPositionX() + normalSp->getContentSize().width / 2 + 5, pPauseItem->getPositionY()));
	this->addChild(scoreItem);

	return true;
}

ControlLayer* ControlLayer::createControlLayer()
{
	ControlLayer* layer = new ControlLayer();
	if(layer)
	{
		layer->init();
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

void ControlLayer::menuCallback(CCObject* obj)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3");
	if(!CCDirector::sharedDirector()->isPaused())
	{
		pPauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png"));
		pPauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png"));
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		CCDirector::sharedDirector()->pause();
		noTouchLayer = NoTouchLayer::create();
		this->addChild(noTouchLayer);
	}
	else
	{
		pPauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
		pPauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		CCDirector::sharedDirector()->resume();
		this->removeChild(noTouchLayer, true);
	}
}

void ControlLayer::updateScore(int score)
{
	if(score >= 0 && score <= MAX_SCORE)
	{
		CCString* strScore = CCString::createWithFormat("%d", score);
		scoreItem->setString(strScore->getCString());
	}
}