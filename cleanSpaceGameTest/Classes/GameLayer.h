#ifndef  __com__wangzhen__cleanspacegame__gamelayer__h__
#define  __com__wangzhen__cleanspacegame__gamelayer__h__

#include"cocos2d.h"
#include"IconLayer.h"
#include"global.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	GameLayer();
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(GameLayer);
	virtual void update(float dt);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void cleanup();
	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

public:
	void menuBackCallback(cocos2d::CCObject* obj);
	void initMap();
	void updateClock(float dt);
	void createGameIcon(int row, int col);
	cocos2d::CCPoint getIconItemOfPosition(int row, int col);
	IconSprite* getIconOfPosition(cocos2d::CCPoint* pos);
	void swapIcons();
	void gameOver(float dt);
	void addTime();
	CC_SYNTHESIZE(int, m_score, Score);
	void fillIcon();
	bool isHaveMoveIcon();
	int findIconIndex(int r1, int c1, int r2, int c2, int r3, int c3);
	void removeIcon();
	void explodeSpecialH(cocos2d::CCPoint iconPos);
	void explodeSpecialV(cocos2d::CCPoint iconPos);
	void explodeIcon(IconSprite* icon);
	void checkAndRemoveIcon();
	void markRemove(IconSprite* icon);
	void removeNode(cocos2d::CCNode* node, void* data);
	void explodeFinish(cocos2d::CCNode* node);
	void getColChainIcon(IconSprite* iconSp, std::list<IconSprite*>& iconlist);
	void getRowChainIcon(IconSprite* iconSp, std::list<IconSprite*>& iconlist);

private:
	float m_mapLBX, m_mapLBY;
	cocos2d::CCSpriteBatchNode* m_spriteSheet;
	IconSprite* m_iconMap[ROWS][COLS];
	IconSprite* m_firstIcon;
	IconSprite* m_secondIcon;
	bool m_isTouchIcon;
	bool m_isFourthBoom;
	bool m_isAction;
	int m_time;
	bool m_isFillIcon;

};

#endif