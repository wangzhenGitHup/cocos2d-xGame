#ifndef  __com__wangzhen__cleanspacegame__gameoverlayer__h__
#define  __com__wangzhen__cleanspacegame__gameoverlayer__h__

#include"cocos2d.h"

class GameOverLayer : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene(int score);
	virtual bool init();
	CREATE_FUNC(GameOverLayer);

public:
	void setScore(int score);
	void menuRestartCallback(cocos2d::CCObject* obj);
	void menuBackCallback(cocos2d::CCObject* obj);

private:
	static int m_score;
};

#endif