#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;


class HelloWorld : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();
	CREATE_FUNC(HelloWorld);

	void test1(); //ʹ��ͼƬ��Դ
	void test2(); //ʹ�þ���֡
	void test3(); //ʹ�ö���֡
};

#endif // __HELLOWORLD_SCENE_H__
