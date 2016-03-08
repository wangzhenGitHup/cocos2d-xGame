#ifndef  __com__wangzhen__fightplane__gameover__h__
#define  __com__wangzhen__fightplane__gameover__h__

#include"cocos2d.h"

class GameOverLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene(int score);
	CREATE_FUNC(GameOverLayer);
	void menuCallback(cocos2d::CCObject* obj);
	void initData();
	void beginChangeHighestScore(cocos2d::CCNode* node);
	void showAD();

private:
	static int m_score;
	static int highestScore;
	cocos2d::CCLabelBMFont* highestScoreLabel;
};

#endif