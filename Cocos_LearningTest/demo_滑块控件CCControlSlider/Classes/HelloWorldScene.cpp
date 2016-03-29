#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}


bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
//��ȡ��������ߴ��С
    CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();
//��ȡ���������ԭ��λ��
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//��Ļ������λ��
	CCPoint midPos = ccp(mysize.width/2, mysize.height/2);


//������ʾSliderֵ�ı�ǩ
	label = CCLabelTTF::create("50.0", "Arial", 32);
	label->setPosition( midPos + ccp(0, 100) );
	this->addChild(label);


//��������ؼ�CCControlSlider
	CCControlSlider* slider = CCControlSlider::create("sliderTrack.png", "sliderProgress.png", "sliderThumb.png");
	slider->setPosition( midPos );
	this->addChild(slider);

	//��������
	slider->setMinimumValue(0); //���û�����Сֵ
	slider->setMaximumValue(100); //���û������ֵ
	slider->setMinimumAllowedValue(20); //��������������Сֵ
	slider->setMaximumAllowedValue(80); //���������������ֵ
	slider->setValue(50); //���õ�ǰ�����ֵ

	//���¼����������ֵ�ı�ʱ�����ؼ��¼�
	slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::valueChanged), CCControlEventValueChanged);


	return true;
}

//�¼���Ӧ������ֵ�ı�ʱ���޸�label��ǩ������
void HelloWorld::valueChanged(CCObject* sender, CCControlEvent controlEvent)
{
//��ȡ�¼�ί���ߣ��������CCControlSlider
	CCControlSlider* slider = (CCControlSlider*)sender;

//�޸�label��ֵ����ʾ����ĵ�ǰֵ
	//sprintfΪC�����е��ַ�����ʽת�������ｫfloatת��Ϊ�ַ���
	char str[50];
	sprintf(str, "%f", slider->getValue() );  //�ַ�����ʽת��
	label->setString(str);
}


//�رճ���
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
