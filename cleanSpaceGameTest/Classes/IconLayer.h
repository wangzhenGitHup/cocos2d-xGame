#ifndef  __com__wangzhen__cleanspacegame__iconlayer__h__
#define  __com__wangzhen__cleanspacegame__iconlayer__h__

#include"cocos2d.h"
#include"global.h"

class IconSprite : public cocos2d::CCSprite
{
public:
	IconSprite();
	static IconSprite* createIcon(int row, int col);
	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(int, m_col, Col);
	CC_SYNTHESIZE(int, m_imageIndex, ImageIndex);
	CC_SYNTHESIZE(bool, m_isNeedRemove, IsNeedRemove);
	CC_SYNTHESIZE(bool, m_ignoreCheck, IgnoreCheck);
	void setDisplayMode(DisplayMode mode);
	DisplayMode getDisplayMode();

private:
	DisplayMode m_displayMode;

};

#endif