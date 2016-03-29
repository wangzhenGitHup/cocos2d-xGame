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


/************************************************************************/
/* CCLabelTTF															*/
/************************************************************************/

/*

//����CCLabelTTF�����ַ���
	CCLabelTTF* lb1 = CCLabelTTF::create("aaaaaaaa", "arial", 20);
	CCLabelTTF* lb2 = CCLabelTTF::create("bbbbbbbb", "����", 40, CCSizeMake(50,100), CCTextAlignment::kCCTextAlignmentCenter);
	CCLabelTTF* lb3 = CCLabelTTF::create("cccccc", "����", 40, CCSizeMake(480,320), CCTextAlignment::kCCTextAlignmentRight, CCVerticalTextAlignment::kCCVerticalTextAlignmentBottom);

//����λ��,��Ļ����
	lb1->setPosition( midPos );
	lb2->setPosition( midPos );
	lb3->setPosition( midPos );

//��ӵ�HelloWorld����
	this->addChild(lb1);
	this->addChild(lb2);
	this->addChild(lb3);

//��������
	lb1->setColor( ccc3(255, 0, 0) ); //������ɫccc3
	lb1->setRotation(60.0f); //��ת
	lb2->setColor( cocos2d::ccBLUE ); //������ɫccBLUE
	lb3->setString("hello world!"); //������������

*/

/************************************************************************/
/* CCLabelAtlas															*/
/************************************************************************/

/*

//����CCLabelTTF�ķ���
	CCLabelAtlas* lb4 = CCLabelAtlas::create("20140815", "fonts/digit.png", 20, 20, '0');
//����λ��
	lb4->setPosition(midPos);
//��ӵ�HelloWorld����
	this->addChild(lb4);

*/

/************************************************************************/
/* CCLabelBMFont														*/
/************************************************************************/

/*
//��������CCLabelBMFont����
	CCLabelBMFont* lb5 = CCLabelBMFont::create("hello", "fonts/bitmapFontTest.fnt");
	CCLabelBMFont* lb6 = CCLabelBMFont::create("world", "fonts/bitmapFontTest.fnt");

//����λ��
	lb5->setPosition( midPos );
	lb6->setPosition( midPos - ccp(0,100) );

//��ӵ�Layer����
	this->addChild(lb5);
	this->addChild(lb6);

//��������
	lb5->setColor(ccRED); //����������ɫΪ��ɫ
	lb6->setString("abc"); //��������

//��ȡĳ��λ�õ���ĸ,����һ��ʹ��
	CCSprite* lb5_c1 = (CCSprite*)lb5->getChildByTag(0); //��ȡ��0����ĸh
	CCSprite* lb5_c2 = (CCSprite*)lb5->getChildByTag(3); //��ȡ��3����ĸl
	lb5_c1->setColor(ccc3(0,255,0)); //����Ϊ��ɫ
	lb5_c2->setScale(2.0f); //�Ŵ�
*/

    return true;
}


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
