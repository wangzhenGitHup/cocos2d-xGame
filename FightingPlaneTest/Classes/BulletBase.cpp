#include"BulletBase.h"
USING_NS_CC;

BulletBase::BulletBase()
{}

BulletBase::~BulletBase()
{}

bool BulletBase::init()
{
	return true;
}

void BulletBase::addBullet(float dt)
{}

void BulletBase::startShoot(float d)
{}

void BulletBase::stopShoot()
{}

void BulletBase::bulletFlyFinish(CCNode* node)
{}

void BulletBase::removeBullet(CCSprite* bullet)
{}
