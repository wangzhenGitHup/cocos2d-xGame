#include"SelectLayer.h"
#include"global.h"
#include"GameLayer.h"
#include"SettingLayer.h"
#include"SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

CCScene* SelectLayer::scene()
{
	CCScene* scene = CCScene::create();
	SelectLayer* layer = SelectLayer::create();
	scene->addChild(layer);
	return scene;
}

bool SelectLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::create("scene_sta.png");
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);

	CCMenuItemImage* startBtn = CCMenuItemImage::create(
		"btn_start01.png",
		"btn_start02.png",
		this,
		menu_selector(SelectLayer::menuStartCallback)
	);
	startBtn->setPosition(ccp(winSize.width / 2, winSize.height / 6));

	CCMenuItemImage* setBtn = CCMenuItemImage::create(
		"btn_setting01.png",
		"btn_setting02.png",
		this,
		menu_selector(SelectLayer::menuSetCallback)
	);
	setBtn->setPosition(ccp(setBtn->getContentSize().width, winSize.height / 6));

	CCMenuItemImage* exitBtn = CCMenuItemImage::create(
		"btn_exit01.png",
		"btn_exit02.png",
		this,
		menu_selector(SelectLayer::menuExitCallback)
	);
	exitBtn->setPosition(ccp(winSize.width - exitBtn->getContentSize().width, winSize.height / 6));

	CCMenu* menu = CCMenu::create(startBtn, setBtn, exitBtn, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	return true;
}

void SelectLayer::onEnter()
{
	CCLayer::onEnter();
}

void SelectLayer::onExit()
{
	CCLayer::onExit();
}

void SelectLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	if(!CCUserDefault::sharedUserDefault()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/music_mainScene.mp3", true);
	}
}

void SelectLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
	SimpleAudioEngine::sharedEngine()->end();
}

void SelectLayer::cleanup()
{

}

void SelectLayer::menuStartCallback(CCObject* obj)
{
	CCScene* scene = GameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}

void SelectLayer::menuSetCallback(CCObject* obj)
{
	CCScene* scene = SettingLayer::scene();
	CCTransitionPageTurn* transitionScene = CCTransitionPageTurn::create(1.0f, scene, false);
	CCDirector::sharedDirector()->replaceScene(transitionScene);
}

void SelectLayer::menuExitCallback(CCObject* obj)
{
	CCDirector::sharedDirector()->end();
	SimpleAudioEngine::sharedEngine()->end();
}