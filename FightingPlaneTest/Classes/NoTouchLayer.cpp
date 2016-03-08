#include"NoTouchLayer.h"

USING_NS_CC;

bool NoTouchLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	this->setTouchEnabled(true);

	return true;
}

void NoTouchLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -100, true);
	CCLayer::registerWithTouchDispatcher();
}

bool NoTouchLayer::ccTouchBegn(CCTouch* pTouch, CCEvent* pEvent)
{
	return true;
}

void NoTouchLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{}

void NoTouchLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{}