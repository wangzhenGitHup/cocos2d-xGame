#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "cocos-ext.h"
using namespace cocos2d::extension;

class HelloWorld : public cocos2d::CCLayer,CCEditBoxDelegate
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(HelloWorld);
	
	virtual void editBoxEditingDidBegin(CCEditBox* editBox); //��ʼ�༭
	virtual void editBoxEditingDidEnd(CCEditBox* editBox); //�����༭
	virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text); //�༭�����ָı�
	virtual void editBoxReturn(CCEditBox* editBox); //����return��Ļص�����
};

#endif // __HELLOWORLD_SCENE_H__
