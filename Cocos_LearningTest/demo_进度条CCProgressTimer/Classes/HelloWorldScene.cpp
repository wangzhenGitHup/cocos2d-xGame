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

//�����Ļ�ߴ�
	CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();

	
//ԭʼͼƬ
	CCSprite* bg = CCSprite::create("Icon.png");
	bg->setPosition( mysize/2 + ccp(0, 100) );
	this->addChild(bg);


//���ν�����pro1
	CCSprite* bg1 = CCSprite::create("Icon.png");
	CCProgressTimer* pro1 = CCProgressTimer::create(bg1);
	pro1->setPosition( ccp(130, 100) );
	this->addChild(pro1);

	//���Σ������������ʽ�����ҵ�����ʾ
	pro1->setType(kCCProgressTimerTypeBar);
	pro1->setBarChangeRate( ccp(1, 0) );
	pro1->setMidpoint( ccp(1, 0) );
	//pro1->setReverseProgress(true); //��������ʾ


//���ν�����pro2
	CCSprite* bg2 = CCSprite::create("Icon.png");
	CCProgressTimer* pro2 = CCProgressTimer::create(bg2);
	pro2->setPosition( ccp(350, 100) );
	this->addChild(pro2);

	//���Σ�Բ��ccp(0.3 , 0.7)
	pro2->setType(kCCProgressTimerTypeRadial);
	pro2->setMidpoint( ccp(0.3, 0.7) );
	//pro2->setReverseProgress(true); //��ʱ��


//���ȶ���
	CCProgressTo* ac1 = CCProgressTo::create(2.0f, 100);
	CCProgressFromTo* ac2 = CCProgressFromTo::create(2.0f, 30, 100);

	pro1->runAction( CCRepeatForever::create(ac1) ); //��0��100
	pro2->runAction( CCRepeatForever::create(ac2) ); //��30��100

	return true;
}

