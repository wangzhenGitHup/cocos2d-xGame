#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;


class HelloWorld : public cocos2d::CCLayer,cocos2d::CCTouchDelegate
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();
	CREATE_FUNC(HelloWorld);


	void testGravity();  //����������ģʽ
	void testRadius();   //�뾶������ģʽ
	void testParticle(); //�ֳ�������Ч 
	void testPlist();    //�Զ���plist������Ч


	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();
};

#endif // __HELLOWORLD_SCENE_H__
