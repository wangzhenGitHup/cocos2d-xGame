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

//���һ��CCSprite����
	CCSprite* sp = CCSprite::create("Icon.png");
	sp->setPosition( midPos );
	this->addChild(sp, 0, 1);

	return true;
}


//������ʼ
bool HelloWorld::ccTouchBegan(CCTouch* touch,CCEvent * event) 
{
	CCLOG("ccTouchBegan");

//��ȡCCSprite����
	CCSprite* sp = (CCSprite*)this->getChildByTag(1);

//���þ��������Ϊ: ��ǰ����λ��
	CCPoint pTouch = touch->getLocation();
	sp->setPosition( pTouch );

	return true;
}

//�����ƶ�
void HelloWorld::ccTouchMoved(CCTouch* touch,CCEvent* event) 
{
	CCLOG("ccTouchMoved");

//��ȡ��������ߴ��С
	CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();

//��ȡCCSprite����
	CCSprite* sp = (CCSprite*)this->getChildByTag(1);

//ʵ�ִ����ƶ�
	CCPoint pos = touch->getDelta(); //��ô���������ƫ����
	CCPoint currentPos = sp->getPosition(); //��þ���ĵ�ǰ����

	currentPos = ccpAdd(currentPos, pos); //����+ƫ���� �������

	sp->setPosition(currentPos); //���ô����ƶ��������
}


//��������
void HelloWorld::ccTouchEnded(CCTouch* touch,CCEvent* event) 
{
	CCLOG("ccTouchEnded");

//��ȡCCSprite����
	CCSprite* sp = (CCSprite*)this->getChildByTag(1);

//���þ��������Ϊ: ������ʼʱ�Ĵ���λ��
	CCPoint touchStartPos = touch->getStartLocation();
	sp->setPosition( touchStartPos );
}


//������������
void HelloWorld::onEnter() 
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
	CCLayer::onEnter();//һ����Ҫ����
}

//�رմ�������
void HelloWorld::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();//һ����Ҫ����
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
