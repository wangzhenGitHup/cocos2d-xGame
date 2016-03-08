#include"GameOverLayer.h"
#include"GameLayer.h"
#include"SelectLayer.h"
#include"global.h"
#include"SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

int GameOverLayer::m_score = 0;
CCScene* GameOverLayer::scene(int score)
{
	m_score = score;
	CCScene* scene = CCScene::create();
	GameOverLayer* layer = GameOverLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* bg = CCSprite::create("scene_end.png");
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);

	CCLabelTTF* scoreLabel = CCLabelTTF::create("Score: ", "Marker Felt.ttf", 48);
	scoreLabel->setPosition(ccp(winSize.width / 2, winSize.height / 1.4));
	scoreLabel->setTag(SCORE_TAG);
	this->addChild(scoreLabel);

	CCMenuItemImage* restartBtn = CCMenuItemImage::create(
		"btn_restart01.png",
		"btn_restart02.png",
		this,
		menu_selector(GameOverLayer::menuRestartCallback)
	);
	restartBtn->setPosition(ccp(winSize.width / 4, winSize.height / 8));

	CCMenuItemImage* backBtn = CCMenuItemImage::create(
		"btn_back01.png",
		"btn_back02.png",
		this,
		menu_selector(GameOverLayer::menuBackCallback)
	);
	backBtn->setPosition(ccp(winSize.width / 1.4, winSize.height / 8));

	CCMenu* menu = CCMenu::create(restartBtn, backBtn, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);
	this->setScore(m_score);
	return true;
}

void GameOverLayer::setScore(int score)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* scoreLabel = (CCLabelTTF*)this->getChildByTag(SCORE_TAG);
	CCString* strScore = CCString::createWithFormat("%d", score);
	scoreLabel->setString(strScore->getCString());

	if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Score") < score)
	{
		CCSprite* newRecord = CCSprite::create("sprite_newRecord.png");
		newRecord->setPosition(ccp(winSize.width / 3.05f, winSize.height / 1.22));
		newRecord->setScale(10.0f);
		newRecord->runAction(CCScaleTo::create(1.2f, 1.0f));
		this->addChild(newRecord);

		if(CCUserDefault::sharedUserDefault()->getBoolForKey(SOUND_KEY))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("music_win.wav", false);
		}
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Score", score);
	}
	else
	{
		if(CCUserDefault::sharedUserDefault()->getBoolForKey(SOUND_KEY))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("music_fail.mp3", false);
		}
	}
}

void GameOverLayer::menuRestartCallback(CCObject* obj)
{
	CCScene* scene = GameLayer::scene();
	CCTransitionMoveInL* transitionScene = CCTransitionMoveInL::create(1.2f, scene);
	CCDirector::sharedDirector()->replaceScene(transitionScene);
}


void GameOverLayer::menuBackCallback(CCObject* obj)
{
	CCScene* scene = SelectLayer::scene();
	CCTransitionSplitRows* transitionScene = CCTransitionSplitRows::create(1.0f, scene);
	CCDirector::sharedDirector()->replaceScene(transitionScene);
}
