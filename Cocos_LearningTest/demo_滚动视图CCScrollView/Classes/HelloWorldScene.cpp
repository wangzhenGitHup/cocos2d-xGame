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

	test1(); //����ͼƬ����
	//test2(); //����ֻ���������
	//test3(); //���Ա�����ҳ

	return true;
}


//����ͼƬ����
void HelloWorld::test1()
{
	CCSize visableSize = CCSizeMake(480, 320); //��Ļ��С
	CCSize mysize = CCSizeMake(960,600); //������С

	
//�������������ô�С
	CCLayerColor* scrollLayer = CCLayerColor::create( ccc4(255,255,255,255) );
	scrollLayer->setContentSize(mysize);
	
//�����еĶ���
	CCSprite* bg = CCSprite::create("war.png");
	bg->setPosition( ccp(960/2.0, 600/2.0) );
	scrollLayer->addChild(bg);


//����������ͼCCScrollView
	CCScrollView* scrollView = CCScrollView::create();
	this->addChild(scrollView, 0, 1);
	
	//��������
	scrollView->setContainer(scrollLayer); //��������
	scrollView->setViewSize( visableSize ); //���������С
	scrollView->setBounceable(true); //�Ƿ���е���
	
	//ί�д���
	scrollView->setDelegate(this);
}


//����ֻ���������
void HelloWorld::test2()
{
	CCSize visableSize = CCSizeMake(480, 320); //��Ļ��С
	CCSize mysize = CCSizeMake(150,220); //������С

//�������������ô�С
	CCLayerColor* scrollLayer = CCLayerColor::create( ccc4(255,255,255,255) );
	scrollLayer->setContentSize(mysize);

//����������ĸ���ť
	for(int i = 1; i <= 4; i++) 
	{
		char file[20];
		sprintf(file, "btn%d.png", i);
		CCSprite* btn = CCSprite::create(file);
		btn->setPosition( ccp(mysize.width/2, 220 - 50*i) );
		scrollLayer->addChild(btn);
	}

//����������ͼCCScrollView
	//���������С150*100 �� ����ΪscrollLayer
	CCScrollView* scrollView = CCScrollView::create(CCSizeMake(150, 100), scrollLayer);
	scrollView->setPosition( visableSize/2 - ccp(150/2.0, 100/2.0) );
	this->addChild(scrollView, 0, 2);
	
	//����Ϊֻ���������
	scrollView->setDirection(kCCScrollViewDirectionVertical);

	//ί�д���
	scrollView->setDelegate(this);

}

//���Ա�����ҳ
void HelloWorld::test3()
{
	CCSize visableSize = CCSizeMake(480, 320); //��Ļ��С
	CCSize mysize = CCSizeMake(300,80); //������С

//�������������ô�С
	CCLayerColor* scrollLayer = CCLayerColor::create( ccc4(255,255,255,255) );
	scrollLayer->setContentSize(mysize);

//�������������ͼƬ
	for(int i = 1; i <= 3; i++) 
	{
		char file[20];
		sprintf(file, "sp%d.png", i);
		CCSprite* sp = CCSprite::create(file);
		sp->setPosition( ccp(100*i - 50, 40) );
		scrollLayer->addChild(sp);
	}

//����������ͼCCScrollView
	//���������С100*80 �� ����ΪscrollLayer
	CCScrollView* scrollView = CCScrollView::create(CCSizeMake(100, 80), scrollLayer);
	scrollView->setPosition( visableSize/2 - ccp(100/2.0, 0) );
	this->addChild(scrollView, 0, 3);

	//��������
	scrollView->setTouchEnabled(false); //�رմ����¼����޷���������

	//ί�д���
	scrollView->setDelegate(this);


//����������ҳ��ť
	//ǰ��pBack����pFront
	pBack = CCMenuItemImage::create("b1.png", "b2.png", "b3.png", this, menu_selector(HelloWorld::scrollImage) );
	pFront = CCMenuItemImage::create("f1.png", "f2.png", "f3.png", this, menu_selector(HelloWorld::scrollImage) );
	pBack->setPosition( ccp(visableSize.width/2 - 100, 60) );
	pFront->setPosition( ccp(visableSize.width/2 + 100, 60) );
	CCMenu* pMenu = CCMenu::create(pBack, pFront, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 0, 100);

	pBack->setEnabled(false);
	pageNumber = 0; //��0ҳ

}

//ʵ�ַ�ҳЧ��
void HelloWorld::scrollImage(CCObject* sender)
{
	CCScrollView* scrollView = (CCScrollView*)this->getChildByTag(3);

	if(sender == pBack && pBack->isEnabled() )
	{
		pageNumber = max(0, pageNumber-1); //ǰ��
	}
	else if( pFront->isEnabled() )
	{
		pageNumber = min(2, pageNumber+1); //��
	}

	//����������Թ�����ͼ��ƫ����
	scrollView->setContentOffset(ccp(-100 * pageNumber, 0), true);

	pBack->setEnabled( pageNumber != 0);
	pFront->setEnabled( pageNumber != 2);
}


void HelloWorld::scrollViewDidScroll(CCScrollView* view) 
{
	CCLOG("ScrollView Moved!");
}
void HelloWorld::scrollViewDidZoom(CCScrollView* view) 
{
	CCLOG("ScrollView Scaled");
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
