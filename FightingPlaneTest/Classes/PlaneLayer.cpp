#include"PlaneLayer.h"
#include"global.h"
#include"GameOverLayer.h"

USING_NS_CC;

PlaneLayer* PlaneLayer::m_plane = NULL;

PlaneLayer::PlaneLayer() : m_planeScore(0), isAlive(true)
{
	
}

PlaneLayer::~PlaneLayer()
{

}

void PlaneLayer::destoryPlane()
{
	if(m_plane)
	{
		CC_SAFE_RELEASE_NULL(m_plane);
	}
}

PlaneLayer* PlaneLayer::createPlane()
{
	PlaneLayer* pRet = new PlaneLayer();
	if(pRet && pRet->init())
	{
		pRet->autorelease();
		m_plane = pRet;
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

PlaneLayer* PlaneLayer::sharedPlaneLayer()
{
	/*if(!m_plane)
	{
		m_plane = new PlaneLayer();
		if(m_plane)
		{
			m_plane->init();
			m_plane->autorelease();
			return m_plane;
		}
		CC_SAFE_DELETE(m_plane);
		return NULL;
	}

	return m_plane;*/
	return m_plane;
}

bool PlaneLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* plane = CCSprite::createWithSpriteFrameName("hero1.png");
	plane->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 120));
	this->addChild(plane, 0, AIR_TAG);

	CCBlink* blink = CCBlink::create(1.0f, 3);
	CCAnimation* animation = CCAnimation::create();
	animation->setDelayPerUnit(0.3f);
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));

	CCAnimate* animate = CCAnimate::create(animation);
	plane->runAction(blink);
	plane->runAction(CCRepeatForever::create(animate));

	return true;
}

void PlaneLayer::movePlane(CCPoint pos)
{
	if(isAlive && !CCDirector::sharedDirector()->isPaused())
	{
		CCSize planeSize = this->getChildByTag(AIR_TAG)->getContentSize();
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		if(pos.x < planeSize.width / 2)
		{
			pos.x = planeSize.width / 2;
		}

		if(pos.x > winSize.width - planeSize.width / 2)
		{
			pos.x = winSize.width - planeSize.width / 2;
		}

		if(pos.y < planeSize.height / 2)
		{
			pos.y = planeSize.height / 2;
		}

		if(pos.y > winSize.height - planeSize.height / 2)
		{
			pos.y = winSize.height - planeSize.height / 2;
		}

		this->getChildByTag(AIR_TAG)->setPosition(pos);
	}
}

void PlaneLayer::blowEffect(int score)
{
	if(isAlive)
	{
		m_planeScore = score;
		isAlive = false;
		
		CCAnimation* animation = CCAnimation::create();
		animation->setDelayPerUnit(0.3f);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png"));

		CCAnimate* animate = CCAnimate::create(animation);
		CCCallFunc* funcDone = CCCallFunc::create(this, callfunc_selector(PlaneLayer::removePlane));
		CCSequence* seq = CCSequence::create(animate, funcDone, NULL);
		this->getChildByTag(AIR_TAG)->stopAllActions();
		this->getChildByTag(AIR_TAG)->runAction(seq);
	}
}

void PlaneLayer::removePlane()
{
	this->removeChildByTag(AIR_TAG, true);
	CCScene* scene = GameOverLayer::scene(m_planeScore);
	CCTransitionMoveInT* transitionScene = CCTransitionMoveInT::create(0.8f, scene);
	CCDirector::sharedDirector()->replaceScene(transitionScene);
}
