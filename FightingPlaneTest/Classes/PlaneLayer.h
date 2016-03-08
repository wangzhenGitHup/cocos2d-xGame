#ifndef  __com__wangzhen__fightplane__planelayer__h__
#define __com__wangzhen__fightplane__planelayer__h__

#include"cocos2d.h"

class PlaneLayer : public cocos2d::CCLayer
{
public:
	~PlaneLayer();
	virtual bool init();
	//PlaneLayer* createPlane();
	static PlaneLayer* createPlane();
	void movePlane(cocos2d::CCPoint pos);
	void removePlane();
	void blowEffect(int score);
	CC_SYNTHESIZE(bool, isAlive, IsAlive);

public:
	static PlaneLayer* sharedPlaneLayer();
	static PlaneLayer* m_plane;
	static void destoryPlane();

private:
	PlaneLayer();

private:
	int m_planeScore;
};

#endif