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

//�������CCSprite����,���ڶ�㴥��
	CCSprite* sp1 = CCSprite::create("Icon.png");
	sp1->setPosition( ccp( 100, 160 ) );
	this->addChild(sp1, 0, 1);

	CCSprite* sp2 = CCSprite::create("Icon_gray.png");
	sp2->setPosition( ccp( 200, 160) );
	this->addChild(sp2, 0, 2);

//������㴥��
//ע����仰����Ҫд,�����޷���㴥��
	this->setTouchEnabled(true);

	return true;
}


//ע���㴥��
void HelloWorld::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

//ע����㴥��
void HelloWorld::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit(); //��Ҫ����д��
}

//������ʼ,����ֵ��void
void HelloWorld::ccTouchesBegan(CCSet* touches,CCEvent* event)
{
	CCLOG("ccTouchesBegan");
}

//�����ƶ�
void HelloWorld::ccTouchesMoved(CCSet* touches,CCEvent* event)
{
	CCLOG("ccTouchesMoved");

//����CCSet�ĵ�����CCSetIterator
	CCSetIterator iter = touches->begin();

//������㴥�㼯��touches
	for( ;iter != touches->end(); iter++) 
	{
		//��ȡ����󣬾ͺ͵���һ���Ĵ�����
		CCTouch* touch = (CCTouch*)(*iter);

		if( touch->getID() == 0) //���ƾ���sp1
		{
			CCSprite* sp1 = (CCSprite*)this->getChildByTag(1);
			sp1->setPosition( touch->getLocation() );
		}
		else if( touch->getID() == 1) //���ƾ���sp2
		{
			CCSprite* sp2 = (CCSprite*)this->getChildByTag(2);
			sp2->setPosition( touch->getLocation() );
		}
	}
}

//��������
void HelloWorld::ccTouchesEnded(CCSet* touches,CCEvent* event)
{
	CCLOG("ccTouchesEnded");
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
