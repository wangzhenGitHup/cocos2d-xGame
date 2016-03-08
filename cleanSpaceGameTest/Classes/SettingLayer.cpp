#include"SettingLayer.h"
#include"global.h"
#include"SelectLayer.h"
#include"SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

CCScene* SettingLayer::scene()
{
	CCScene* scene = CCScene::create();
	SettingLayer* layer = SettingLayer::create();
	scene->addChild(layer);
	return scene;
}

bool SettingLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCUserDefault* defaults = CCUserDefault::sharedUserDefault();
	CCSprite* bg = CCSprite::create("scene_abo.png");
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);

	CCMenuItemImage* backBtn = CCMenuItemImage::create(
		"btn_ret.png",
		"btn_ret.png",
		this,
		menu_selector(SettingLayer::menuBackCallback)
	);
	backBtn->setPosition(ccp(backBtn->getContentSize().width / 2, winSize.height - backBtn->getContentSize().height / 2));

	CCMenuItemImage* turnOnItem = CCMenuItemImage::create("btn_musOn.png", "btn_musOn.png");
	CCMenuItemImage* turnOffItem = CCMenuItemImage::create("btn_musOff.png", "btn_musOff.png");
	CCMenuItemImage* effectOnItem = CCMenuItemImage::create("btn_musOn.png", "btn_musOn.png");
	CCMenuItemImage* effectOffItem = CCMenuItemImage::create("btn_musOff.png", "btn_musOff.png");

	CCMenuItemToggle* musicToggle = CCMenuItemToggle::createWithTarget(this, menu_selector(SettingLayer::menuMusicCallback), 
		turnOnItem, turnOffItem, NULL);
	musicToggle->setPosition(ccp(winSize.width / 1.4, winSize.height / 1.8));

	CCMenuItemToggle* soundToggle = CCMenuItemToggle::createWithTarget(this, menu_selector(SettingLayer::menuSoundCallback),
		effectOnItem, effectOffItem, NULL);
	soundToggle->setPosition(ccp(winSize.width / 1.4, winSize.height / 1.4));

	CCMenu* menu = CCMenu::create(backBtn, musicToggle, soundToggle, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	CCLabelTTF* aboutLabel = CCLabelTTF::create("About US", "Marker Felt.ttf", 28);
	aboutLabel->setPosition(ccp(winSize.width / 2, winSize.height / 1.2));
	aboutLabel->setColor(ccc3(35, 35, 35));
	this->addChild(aboutLabel);

	if(defaults->getBoolForKey(MUSIC_KEY))
	{
		musicToggle->setSelectedIndex(0);
	}
	else
	{
		musicToggle->setSelectedIndex(1);
	}

	if(defaults->getBoolForKey(SOUND_KEY))
	{
		soundToggle->setSelectedIndex(0);
	}
	else
	{
		soundToggle->setSelectedIndex(1);
	}

	return true;
}

void SettingLayer::onEnter()
{
	CCLayer::onEnter();
}

void SettingLayer::onExit()
{
	CCLayer::onExit();
}

void SettingLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	if(CCUserDefault::sharedUserDefault()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music_mainScene.wav", true);
	}
}

void SettingLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
	SimpleAudioEngine::sharedEngine()->end();
}

void SettingLayer::cleanup()
{}

void SettingLayer::menuMusicCallback(CCObject* obj)
{
	CCMenuItemToggle* item = (CCMenuItemToggle*)obj;
	if(CCUserDefault::sharedUserDefault()->getBoolForKey(MUSIC_KEY))
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey(MUSIC_KEY, false);
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
	else
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/music_mainScene.wav");
	}
}

void SettingLayer::menuSoundCallback(CCObject* obj)
{
	CCMenuItemToggle* item = (CCMenuItemToggle*)obj;

	if(CCUserDefault::sharedUserDefault()->getBoolForKey(SOUND_KEY))
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey(SOUND_KEY, false);
	}
	else
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey(SOUND_KEY, true);
	}
}

void SettingLayer::menuBackCallback(CCObject* obj)
{
	CCScene* scene = SelectLayer::scene();
	CCTransitionPageTurn* transitionScene = CCTransitionPageTurn::create(1.0f, scene, false);
	CCDirector::sharedDirector()->replaceScene(transitionScene);
}