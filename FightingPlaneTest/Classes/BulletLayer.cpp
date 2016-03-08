#include"BulletLayer.h"
#include"SimpleAudioEngine.h"
#include"PlaneLayer.h"
#include"global.h"

using namespace CocosDenshion;
USING_NS_CC;

bool BulletLayer::init()
{
	m_bulletBatchNode = CCSpriteBatchNode::create("shoot.png");
	this->addChild(m_bulletBatchNode);
	this->schedule(schedule_selector(BulletLayer::addBullet), 0.5f);

	return true;
}

BulletLayer::BulletLayer()
{
	m_bulletBatchNode = NULL;
	m_allBullets = CCArray::create();
	m_allBullets->retain();
}

BulletLayer::~BulletLayer()
{
	CC_SAFE_RELEASE_NULL(m_allBullets);
}

BulletLayer* BulletLayer::createBullet()
{
	BulletLayer* bullet = new BulletLayer();
	if(bullet)
	{
		bullet->init();
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}

void BulletLayer::addBullet(float dt)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
	CCSprite* bullet = CCSprite::createWithSpriteFrameName("bullet1.png");
	m_bulletBatchNode->addChild(bullet);
	m_allBullets->addObject(bullet);

	PlaneLayer* plane = (PlaneLayer*)PlaneLayer::sharedPlaneLayer()->getChildByTag(AIR_TAG);
	CCPoint planePos = plane->getPosition();
	CCPoint bulletPos = ccp(planePos.x, planePos.y  + plane->getContentSize().width / 2);
	bullet->setPosition(bulletPos);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float flyDistance = winSize.height + bullet->getContentSize().height / 2 - bulletPos.y;
	float flySpeed = 320;
	float flyTime = flyDistance / flySpeed;
	CCMoveTo* moveTo = CCMoveTo::create(flyTime, ccp(bulletPos.x, winSize.height + bullet->getContentSize().height / 2));
	CCCallFuncN* flyDone = CCCallFuncN::create(this, callfuncN_selector(BulletLayer::bulletFlyFinish));
	CCSequence* seq = CCSequence::create(moveTo, flyDone, NULL);
	bullet->runAction(seq);
}

void BulletLayer::bulletFlyFinish(CCNode* node)
{
	CCSprite* bullet = (CCSprite*)node;
	this->removeBullet(bullet);
}

void BulletLayer::removeBullet(CCSprite* bullet)
{
	if(bullet)
	{
		m_allBullets->removeObject(bullet);
		m_bulletBatchNode->removeChild(bullet, true);
	}
}

void BulletLayer::startShoot(float dt)
{
	this->schedule(schedule_selector(BulletLayer::addBullet), 0.2f, kCCRepeatForever, dt);
}

void BulletLayer::stopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::addBullet));
}