#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "cocos-ext.h"
using namespace cocos2d::extension;


class HelloWorld : public cocos2d::CCLayer,public CCScrollViewDelegate
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();
	void menuCloseCallback(CCObject* pSender);
	CREATE_FUNC(HelloWorld);

	void test1(); //����ͼƬ����
	void test2(); //����ֻ���������
	void test3(); //���Ա�����ҳ

	int pageNumber; //�����ڼ�ҳ
	CCMenuItemImage* pBack; //��ǰ��ҳ
	CCMenuItemImage* pFront; //����ҳ
	void scrollImage(CCObject* sender); //test3�ı�����ҳ

	void scrollViewDidScroll(CCScrollView* view); //����ʱ��Ӧ�Ļص�����
	void scrollViewDidZoom(CCScrollView* view); //����ʱ��Ӧ�Ļص�����
};

#endif // __HELLOWORLD_SCENE_H__
