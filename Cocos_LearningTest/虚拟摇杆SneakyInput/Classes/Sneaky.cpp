#include "Sneaky.h"

Sneaky::Sneaky()
{
//����ҡ�˰�ť
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI.plist", "UI.png");

//ҡ��
	joystick = NULL;
	joystick = new SneakyJoystick();
	joystick->initWithRect(CCRectZero); // ��ԭ���ʼ��
	joystick->setAutoCenter(true); //�Ƿ��Զ��ص�����
	joystick->setHasDeadzone(true);  //����֧����Ч�������İ뾶ΪR�������ڲ��ᴥ��
	joystick->setDeadRadius(10); // �������İ뾶10��Ϊ��Ч����

	SneakyJoystickSkinnedBase* jstickSkin = new SneakyJoystickSkinnedBase();
	jstickSkin->autorelease();
	jstickSkin->init();
	
	//-- need modify start --
	jstickSkin->setBackgroundSprite(CCSprite::createWithSpriteFrameName("JoyStick-base.png")); //����
	jstickSkin->setThumbSprite(CCSprite::createWithSpriteFrameName("JoyStick-thumb.png")); //ң�ظ�
	jstickSkin->setPosition(ccp(jstickSkin->getContentSize().width/2, jstickSkin->getContentSize().height/2));
	//-- need modify end --

	jstickSkin->setJoystick(joystick);
	this->addChild(jstickSkin);


//��ťA
	buttonA = NULL;
	buttonA = new SneakyButton();
	buttonA->initWithRect(CCRectZero);
	buttonA->setIsToggleable(false);
	buttonA->setIsHoldable(true); //�����ڰ���ʱ���Ƿ񱣳ְ���״̬

	SneakyButtonSkinnedBase* buttonASkin = new SneakyButtonSkinnedBase();
	buttonASkin->autorelease();
	buttonASkin->init();

	//-- need modify start --
	buttonASkin->setDefaultSprite(CCSprite::createWithSpriteFrameName("button-default.png")); //Ĭ��ͼƬ
	buttonASkin->setPressSprite(CCSprite::createWithSpriteFrameName("button-pressed.png")); //����ͼƬ
	buttonASkin->setActivatedSprite(CCSprite::createWithSpriteFrameName("button-activated.png")); //����ͼƬ
	//buttonASkin->setDisabledSprite(CCSprite::createWithSpriteFrameName("button-disabled.png")); //ʧЧͼƬ
	buttonASkin->setPosition(ccp(480 - buttonASkin->getContentSize().width/2, buttonASkin->getContentSize().height/2) );
	//-- need modify end --

	buttonASkin->setButton(buttonA);
	this->addChild(buttonASkin);


	init();
}

bool Sneaky::init()
{
	CCLayer::init();
	return true;
}


//void HudLayer::inputUpdate(float dt)
//{
//
//}