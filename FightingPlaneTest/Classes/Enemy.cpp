#include"Enemy.h"

USING_NS_CC;

Enemy::Enemy() : m_life(0), m_sprite(NULL)
{
}

Enemy* Enemy::createEnemy()
{
	Enemy* enemy = new Enemy();
	if(enemy)
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

void Enemy::bindSprite(CCSprite* sprite, int life)
{
	m_sprite = sprite;
	m_life = life;
	this->addChild(m_sprite);
}

void Enemy::loseLife()
{
	m_life--;
}

int Enemy::getLife()
{
	return m_life;
}

CCSprite* Enemy::getSprite()
{
	return m_sprite;
}

CCRect Enemy::getBoundingBox()
{
	CCRect rect = m_sprite->boundingBox();
	CCPoint pos = this->convertToWorldSpace(rect.origin);
	CCRect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return enemyRect;
}