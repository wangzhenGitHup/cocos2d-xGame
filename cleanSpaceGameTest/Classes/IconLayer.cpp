#include"IconLayer.h"

USING_NS_CC;

IconSprite::IconSprite() : m_col(0), m_row(0), m_imageIndex(0),
	m_isNeedRemove(false), m_ignoreCheck(false), m_displayMode(DISPLAY_MODE_NORMAL)
{

}

IconSprite* IconSprite::createIcon(int row, int col)
{
	IconSprite* icon = new IconSprite();
	icon->m_row = row;
	icon->m_col = col;
	icon->m_imageIndex = rand() % TOTAL_ICON;
	icon->initWithSpriteFrameName(iconNormal[icon->m_imageIndex]);
	icon->autorelease();
	return icon;
}

DisplayMode IconSprite::getDisplayMode()
{
	return m_displayMode;
}

void IconSprite::setDisplayMode(DisplayMode mode)
{
	m_displayMode = mode;
	CCSpriteFrame* frame = NULL;
	switch(mode)
	{
	case DISPLAY_MODE_VERTICAL:
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconVertical[m_imageIndex]);
		break;

	case DISPLAY_MODE_HORIZONTAL:
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconHorizontal[m_imageIndex]);
		break;
	}
	//为当前的精灵设置新的显示帧
	this->setDisplayFrame(frame);
}