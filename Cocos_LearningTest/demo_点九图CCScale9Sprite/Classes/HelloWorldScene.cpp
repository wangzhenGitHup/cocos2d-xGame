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

	test("Icon.png", 1); //��Icon.png������
	test("CloseNormal.png", 2); //��CloseNormal.png������
	test("Rect.png", 3); //��Rect.png������

	return true;
}

/**
 *		file��ͼƬ��Դ���ƣ���"sp.png"
 *		index���ڼ����������
 */
void HelloWorld::test(const char* file, int index)
{

//��ȡ��������ߴ��С
	CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();
//��ȡ���������ԭ��λ��
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//��Ļ������λ��
	CCPoint midPos = ccp(mysize.width/2, mysize.height/2);


//CCSprite����������
	CCSprite* sprite1 = CCSprite::create(file);
	sprite1->setPosition( ccp(120 * index, mysize.height - 60) );
	this->addChild(sprite1);

	//��������
	sprite1->setScale(2.0f);


//scale9Sprite1��������capInsets
	CCScale9Sprite* scale9Sprite1 = CCScale9Sprite::create(file);
	scale9Sprite1->setPosition( ccp(120 * index, mysize.height/2) );
	this->addChild(scale9Sprite1);

	//������capInsets������
	scale9Sprite1->setContentSize( CCSizeMake(80, 80) );


//scale9Sprite2������capInsets
	CCScale9Sprite* scale9Sprite2 = CCScale9Sprite::create(file);
	scale9Sprite2->setPosition( ccp(120 * index, 60) );
	this->addChild(scale9Sprite2);

	//����capInsets��������
	scale9Sprite2->setCapInsets( CCRectMake(3, 3, 34, 34) );
	scale9Sprite2->setContentSize( CCSizeMake(80, 80) );
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
