#include"GameOverLayer.h"
#include"SimpleAudioEngine.h"
#include"GameLayer.h"
#include"PlaneLayer.h"

using namespace CocosDenshion;
USING_NS_CC;

int GameOverLayer::highestScore = 0;
int GameOverLayer::m_score = 0;

CCScene* GameOverLayer::scene(int score)
{
	m_score = score;

	CCScene* scene = CCScene::create();
	GameOverLayer* layer = GameOverLayer::create();
	scene->addChild(layer);
	return scene;
}

void GameOverLayer::initData()
{

}

bool GameOverLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	this->initData();

	if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
	SimpleAudioEngine::sharedEngine()->playEffect("sound/game_over.mp3");

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* bg = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gameover.png"));
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);

	CCSprite* backNormalBtn = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
	CCSprite* backPressedBtn = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
	CCMenuItemSprite* itemBtn = CCMenuItemSprite::create(backNormalBtn, backPressedBtn, this, menu_selector(GameOverLayer::menuCallback));
	itemBtn->setPosition(ccp(winSize.width - backNormalBtn->getContentSize().width / 2 - 10, backNormalBtn->getContentSize().height / 2 + 10));

	CCMenu* menu = CCMenu::create(itemBtn, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	CCString* scoreStr = CCString::createWithFormat("%d", m_score);
	CCLabelBMFont* fontLabel = CCLabelBMFont::create(scoreStr->getCString(), "font/font.fnt");
	fontLabel->setColor(ccc3(143, 146,147));
	fontLabel->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(fontLabel);

	CCDelayTime* delayTime = CCDelayTime::create(1.0f);
	CCScaleTo* scaleBig = CCScaleTo::create(1.0f, 3.0f);
	CCScaleTo* scaleTitle = CCScaleTo::create(0.3f, 2.0f);
	CCCallFunc* scaleDone = CCCallFunc::create(this, callfunc_selector(GameOverLayer::showAD));
	CCSequence* seq = CCSequence::create(delayTime, scaleBig, scaleTitle, scaleDone, NULL);
	fontLabel->runAction(seq);

	CCString* highestScoreStr = CCString::createWithFormat("%d", highestScore);
	highestScoreLabel = CCLabelBMFont::create(highestScoreStr->getCString(), "font/font.fnt");
	highestScoreLabel->setColor(ccc3(143, 146,147));
	highestScoreLabel->setAnchorPoint(ccp(0, 0.5));
	highestScoreLabel->setPosition(ccp(140, winSize.height - 30));
	this->addChild(highestScoreLabel);

	if(m_score > highestScore)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("highestscore", m_score);
		highestScore = m_score;
		
		CCDelayTime* delayChange = CCDelayTime::create(1.3f);
		CCMoveBy* moveOut = CCMoveBy::create(1.0f, ccp(0, 100));
		CCCallFuncN* done = CCCallFuncN::create(this, callfuncN_selector(GameOverLayer::beginChangeHighestScore));
		CCMoveBy* moveIn = CCMoveBy::create(0.1f, ccp(0, -100));
		CCSequence* seq = CCSequence::create(delayChange, moveOut, done, moveIn, NULL);
		highestScoreLabel->runAction(seq);
	}

	return true;
}

void GameOverLayer::menuCallback(CCObject* obj)
{
	CCScene* scene = GameLayer::scene();
	CCTransitionSlideInL* transition = CCTransitionSlideInL::create(1.0f, scene);
	CCDirector::sharedDirector()->replaceScene(transition);
}

void GameOverLayer::beginChangeHighestScore(CCNode* node)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/achievement.mp3");
	CCString* changeScore = CCString::createWithFormat("%d", m_score);
	highestScoreLabel->setString(changeScore->getCString());
}

void GameOverLayer::showAD()
{}