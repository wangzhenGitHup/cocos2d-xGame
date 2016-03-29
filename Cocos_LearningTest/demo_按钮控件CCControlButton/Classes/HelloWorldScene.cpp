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


//��ʾ��ť״̬�ı�ǩdisplayLabel
	displayLabel = CCLabelTTF::create("No Event", "Marker Felt", 32);
	displayLabel->setPosition( midPos + ccp(0, 100) );
	this->addChild(displayLabel);


//��ť�еı�������CCScale9Sprite
	CCScale9Sprite* bgNormal = CCScale9Sprite::create("btnNormal.png"); //��������
	CCScale9Sprite* bgHighlighted = CCScale9Sprite::create("btnHighlighted.png"); //��������

//��ť�еı�ǩCCLabelTTF
	CCLabelTTF* titleNormal = CCLabelTTF::create("Button is Normal !", "Marker Felt", 30);
	CCLabelTTF* titleHighlighted = CCLabelTTF::create("Button is Highlighted !", "Marker Felt", 30);


//������ťCCControlButton
	CCControlButton* btn = CCControlButton::create(titleNormal, bgNormal);
	btn->setPosition( midPos );
	this->addChild(btn);

//���ð�ť����ʱ��״̬
	btn->setTitleLabelForState(titleHighlighted, CCControlStateHighlighted); //������ǩ
	btn->setTitleColorForState(ccRED, CCControlStateHighlighted); //��ɫ
	btn->setBackgroundSpriteForState(bgHighlighted, CCControlStateHighlighted); //��������

	//д����仰��������С���̶��ˡ�û�а���label�Ĵ�С�����Զ���չ��
	//btn->setPreferredSize( CCSizeMake(120,40) );

//���¼���������ʾ��ť״̬
	btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::touchDownAction), CCControlEventTouchDown); //�ոտ�ʼ������ťʱ
	btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::touchDragInsideAction), CCControlEventTouchDragInside);  //���ڲ��϶�ʱ�����ִ���״̬�£�
	btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::touchDragOutsideAction), CCControlEventTouchDragOutside); //���ⲿ�϶�ʱ�����ִ���״̬�£�
	btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::touchDragEnterAction), CCControlEventTouchDragEnter);  //�϶��ս����ڲ�ʱ�����ִ���״̬�£�
	btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::touchDragExitAction), CCControlEventTouchDragExit); //�϶����뿪�ڲ�ʱ�����ִ���״̬�£�
	btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::touchUpInsideAction), CCControlEventTouchUpInside); //���ڲ�̧����ָ�����ִ���״̬�£�
	btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::touchUpOutsideAction), CCControlEventTouchUpOutside); //���ⲿ̧����ָ�����ִ���״̬�£�
	btn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::touchCancelAction), CCControlEventTouchCancel); //ȡ������

	return true;
}

//�ոտ�ʼ������ťʱ
void HelloWorld::touchDownAction(CCObject *senderz, CCControlEvent controlEvent)
{
	displayLabel->setString("Touch Down");
}

//���ڲ��϶�ʱ�����ִ���״̬�£�
void HelloWorld::touchDragInsideAction(CCObject *sender, CCControlEvent controlEvent)
{
	displayLabel->setString("Drag Inside");
}

//���ⲿ�϶�ʱ�����ִ���״̬�£�
void HelloWorld::touchDragOutsideAction(CCObject *sender, CCControlEvent controlEvent)
{
	displayLabel->setString("Drag Outside");
}

//�϶��ս����ڲ�ʱ�����ִ���״̬�£�
void HelloWorld::touchDragEnterAction(CCObject *sender, CCControlEvent controlEvent)
{
	displayLabel->setString("Drag Enter");
}

//�϶����뿪�ڲ�ʱ�����ִ���״̬�£�
void HelloWorld::touchDragExitAction(CCObject *sender, CCControlEvent controlEvent)
{
	displayLabel->setString("Drag Exit");
}

//���ڲ�̧����ָ�����ִ���״̬�£�
void HelloWorld::touchUpInsideAction(CCObject *sender, CCControlEvent controlEvent)
{
	displayLabel->setString("Touch Up Inside.");
}

//���ⲿ̧����ָ�����ִ���״̬�£�
void HelloWorld::touchUpOutsideAction(CCObject *sender, CCControlEvent controlEvent)
{
	displayLabel->setString("Touch Up Outside.");
}

//ȡ�����д���
void HelloWorld::touchCancelAction(CCObject *sender, CCControlEvent controlEvent)
{
	displayLabel->setString("Touch Cancel");
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
