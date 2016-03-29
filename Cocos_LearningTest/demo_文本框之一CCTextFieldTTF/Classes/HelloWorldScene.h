#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;


class HelloWorld : public cocos2d::CCLayer,cocos2d::CCTextFieldDelegate
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(HelloWorld);

	virtual bool onTextFieldAttachWithIME(CCTextFieldTTF* sender); //���û�����������̵�ʱ��Ļص�����
	virtual bool onTextFieldDetachWithIME(CCTextFieldTTF* sender); //���û��ر�������̵�ʱ��Ļص�����
	virtual bool onTextFieldInsertText(CCTextFieldTTF* sender, const char* text, int nLen); //���û������ʱ��Ļص�����
	virtual bool onTextFieldDeleteBackward(CCTextFieldTTF* sender, const char* delText, int nLen); //���û�ɾ�����ֵ�ʱ��Ļص�����

	//��������
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void onEnter();
	virtual void onExit();
};

#endif // __HELLOWORLD_SCENE_H__
