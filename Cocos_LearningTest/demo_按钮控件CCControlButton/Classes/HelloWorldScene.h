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


	CCLabelTTF* displayLabel; //��ʾ��ť״̬��label
	void touchDownAction(CCObject* sender, CCControlEvent controlEvent); //�ոտ�ʼ������ťʱ
	void touchDragInsideAction(CCObject* sender, CCControlEvent controlEvent); //���ڲ��϶�ʱ�����ִ���״̬�£�
	void touchDragOutsideAction(CCObject* sender, CCControlEvent controlEvent); //���ⲿ�϶�ʱ�����ִ���״̬�£�
	void touchDragEnterAction(CCObject* sender, CCControlEvent controlEvent); //�϶��ս����ڲ�ʱ�����ִ���״̬�£�
	void touchDragExitAction(CCObject* sender, CCControlEvent controlEvent); //�϶����뿪�ڲ�ʱ�����ִ���״̬�£�
	void touchUpInsideAction(CCObject* sender, CCControlEvent controlEvent); //���ڲ�̧����ָ�����ִ���״̬�£�
	void touchUpOutsideAction(CCObject* sender, CCControlEvent controlEvent); //���ⲿ̧����ָ�����ִ���״̬�£�
	void touchCancelAction(CCObject* sender, CCControlEvent controlEvent); //ȡ������

};

#endif // __HELLOWORLD_SCENE_H__
