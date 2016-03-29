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



//�����������
	CCSprite* sp = CCSprite::create("Icon.png");
	sp->setPosition( ccp(30, mysize.height - 30) );
	this->addChild(sp, 0, 100); //tag���100

	CCSprite* sp1 = CCSprite::create("Icon.png");
	sp1->setPosition( ccp(30, mysize.height - 90) );
	this->addChild(sp1, 0, 101); //tag���101

	CCSprite* sp2 = CCSprite::create("Icon.png");
	sp2->setPosition( ccp(30, mysize.height - 150) );
	this->addChild(sp2, 0, 102); //tag���102

	CCSprite* sp3 = CCSprite::create("Icon.png");
	sp3->setPosition( ccp(30, mysize.height - 210) );
	this->addChild(sp3, 0, 103); //tag���103

	CCSprite* sp4 = CCSprite::create("Icon.png");
	sp4->setPosition( ccp(30, mysize.height - 270) );
	this->addChild(sp4, 0, 104); //tag���104
	 

//���������ʱ��,���¾���
	this->scheduleUpdate();
	this->schedule( schedule_selector(HelloWorld::myupdate) );
	this->schedule( schedule_selector(HelloWorld::myupdate2), 1.0f );
	this->schedule( schedule_selector(HelloWorld::myupdate3), 1.0f, 5, 3.0f);
	this->scheduleOnce( schedule_selector(HelloWorld::myupdate4), 5.0f );

	return true;
}

//scheduleUpdate
void HelloWorld::update(float dt)
{
	CCSprite* sp = (CCSprite*)this->getChildByTag(100); //��ȡ tag=100 �ľ���
	sp->setPosition( sp->getPosition() + ccp(1,0) ); //ÿ֡�ƶ�1
}

//schedule(schedule_selector)
void HelloWorld::myupdate(float dt)
{
	CCSprite* sp1 = (CCSprite*)this->getChildByTag(101); //��ȡ tag=101 �ľ���
	sp1->setPosition( sp1->getPosition() + ccp(1,0) ); //ÿ֡�ƶ�1
}

//schedule(schedule_selector, interval)
void HelloWorld::myupdate2(float dt)
{
	CCSprite* sp2 = (CCSprite*)this->getChildByTag(102); //��ȡ tag=102 �ľ���
	sp2->setPosition( sp2->getPosition() + ccp(60,0) ); //ÿ���ƶ�60
}

//schedule(schedule_selector, interval, repeat, delay)
void HelloWorld::myupdate3(float dt)
{
	CCSprite* sp3 = (CCSprite*)this->getChildByTag(103); //��ȡ tag=103 �ľ���
	sp3->setPosition( sp3->getPosition() + ccp(60,0) ); //ÿ���ƶ�60
}

//scheduleOnce
void HelloWorld::myupdate4(float dt)
{
	CCSprite* sp4 = (CCSprite*)this->getChildByTag(104); //��ȡ tag=104 �ľ���
	sp4->setPosition( sp4->getPosition() + ccp(100,0) ); //�ƶ�100
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
