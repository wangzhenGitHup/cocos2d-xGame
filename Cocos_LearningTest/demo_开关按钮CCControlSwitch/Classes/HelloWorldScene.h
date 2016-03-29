#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "cocos-ext.h"
using namespace cocos2d::extension;


class HelloWorld : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(HelloWorld);

	CCLabelTTF* label; //������ʾ���ؿؼ���״̬ON/OFF
	void valueChanged(CCObject* sender, CCControlEvent controlEvent);
};

#endif // __HELLOWORLD_SCENE_H__
