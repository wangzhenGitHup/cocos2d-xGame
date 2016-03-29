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
/* Test																	*/
/************************************************************************/


/*
 *	����CCMenuItemLabel
 *		ʹ��CCLabelTTF����
 */
	CCLabelTTF* lb1 = CCLabelTTF::create("aaaaaa", "Arial", 32);
	CCMenuItemLabel* menuItemLabel = CCMenuItemLabel::create(lb1);
	//����λ��
	menuItemLabel->setPosition( ccp(120, mysize.height-50) ); 

/*
 *	����CCMenuItemAtlasFont
 *		������ʽ��CCLabelAtlas����
 */
	CCMenuItemAtlasFont* menuItemAtlas = CCMenuItemAtlasFont::create("20140818", "fonts/digit.png", 20, 20, '0');
	menuItemAtlas->setPosition( ccp(120, mysize.height-120) );


/*
 *	����CCMenuItemFont
 *		���������������޸����ص���Ӧ����
 */
	//����CCMenuItemFont����ʱ��Ĭ�������С
	CCMenuItemFont::setFontSize(50);

	//�����ص���Ӧ������tag���Ϊ1
	CCMenuItemFont* menuItemFont1 = CCMenuItemFont::create("11111");
	menuItemFont1->setTag(1);

	//������ִ�лص�����menuItemFont2Func������menuItemFont1������
	CCMenuItemFont* menuItemFont2 = CCMenuItemFont::create("Change1", this, menu_selector(HelloWorld::menuItemFont2Func) ); //�ص�
	
	menuItemFont2->setFontSizeObj(32); //���������С
	menuItemFont1->setPosition( ccp(120, mysize.height-190) ); //����λ��
	menuItemFont2->setPosition( ccp(120, mysize.height-260) ); //����λ��


/*
 *	����CCMenu��tag���Ϊ100
 *		�˵���menuItemLabel, menuItemAtlas, menuItemFont1, menuItemFont2
 */
	CCMenu* menu = CCMenu::create(menuItemLabel, menuItemAtlas, menuItemFont1, menuItemFont2, NULL);
	
	//����λ��Ϊ(0,0)����HelloWorld���غ�
	menu->setPosition(CCPointZero); 
	
	//��CCMenu�˵���ӵ�CCLayer�У� tag���Ϊ100
	this->addChild(menu, 0, 100); 


/*
 *	����CCMenuItemSprite
 *		����ΪCCSprite����
 */
	CCSprite* sp1 = CCSprite::create("sp1.png");
	CCSprite* sp2 = CCSprite::create("sp2.png");
	CCSprite* sp3 = CCSprite::create("sp3.png");
	CCMenuItemSprite* menuItemSprite = CCMenuItemSprite::create(sp1, sp2, sp3 );

	menuItemSprite->setPosition( ccp(mysize.width/2 + 50, mysize.height/2 + 50) );
	menu->addChild(menuItemSprite); //��ӵ��˵�����
	menuItemSprite->setTag(2); //tag���Ϊ2

/*
 *	����CCMenuItemImage
 *		�����������ͼƬpng
 */
	//ʹ��CCMenuItemImage����һ���رճ���Ĳ˵��ť
	CCMenuItemImage* menuItemImage = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(HelloWorld::menuCloseCallback) ); //�ص�
	menuItemImage->setPosition( ccp(mysize.width - 40, mysize.height - 40) );
	menu->addChild(menuItemImage); //��ӵ��˵�����


/*
 *	����CCMenuItemToggle
 *		����ΪCCMenuItem����
 */
	CCMenuItemFont::setFontSize(20);
	CCMenuItemFont* menuItemFont3 = CCMenuItemFont::create("Toggle_Normal");
	CCMenuItemFont* menuItemFont4 = CCMenuItemFont::create("Toggle_Selected");
	CCMenuItemImage* menuItemImage2 = CCMenuItemImage::create("sp3.png", "sp1.png");
	
	//����CCMenuItemToggle���ص�����������menuItemSprite��״̬��
	CCMenuItemToggle* menuItemToggle = CCMenuItemToggle::createWithTarget(this, menu_selector(HelloWorld::menuItemToggleFunc), 
																				menuItemFont3, menuItemFont4, NULL ); //�˵�������б�
	menuItemToggle->setPosition( ccp(mysize.width/2 + 50, mysize.height/2 - 50) ); //����λ��

	//��menuItemImage2��ӵ�menuItemToggle��
	menuItemToggle->addSubItem(menuItemImage2);

	menu->addChild(menuItemToggle); //��ӵ��˵�����


    return true;
}


/*
 *		�ص�����menuItemFont2Func
 */

//�仯menuItemFont1������
void HelloWorld::menuItemFont2Func(CCObject* sender)
{
	
//��ȡmenuItemFont2
	CCMenuItemFont* menuItemFont2 = (CCMenuItemFont*)sender;

//��CCLayer�л�ȡCCMenu�˵�
	CCMenu* menu = (CCMenu*)this->getChildByTag(100);

//��ȡmenuItemFont1����tagΪ1
	//������ע�⣡����
	//		tag����Ը��ڵ���Եģ�this���ӽڵ���û��tagΪ1����menuItemFont1��menu��tagΪ1���ӽڵ㡣
	CCMenuItemFont* menuItemFont1 = (CCMenuItemFont*)menu->getChildByTag(1);
	

//����menuItemFont1������
	//��ȡmenuItemFont2��ʾ�ı�ǩ����
	CCLabelTTF* lb = (CCLabelTTF*)menuItemFont2->getLabel();

	//strcmp�ж��Ƿ����Change1
	if( strcmp( lb->getString() , "Change1") == 0 ) { 
		lb->setString("Change2");
		menuItemFont1->setString("22222");
	}else {
		lb->setString("Change1");
		menuItemFont1->setString("11111");
	}
}


/*
 *		�ص�����menuItemToggleFunc
 */

//����״̬:����,ѡ��,����
void HelloWorld::menuItemToggleFunc(CCObject* sender)
{
	
//��ȡmenuItemToggle
	CCMenuItemToggle* menuItemToggle = (CCMenuItemToggle*)sender;

//��CCLayer�л�ȡCCMenu�˵�
	CCMenu* menu = (CCMenu*)this->getChildByTag(100);

//��ȡmenuItemSprite
	CCMenuItemSprite* menuItemSprite = (CCMenuItemSprite*)menu->getChildByTag(2);


//����menuItemToggle��ǰ��ѡ�е�����һ��,������menuItemSprite��״̬
	switch( menuItemToggle->getSelectedIndex() ) {
		case 0: //����
			menuItemSprite->setEnabled(true);
			break;
		case 1: //ѡ��
			menuItemSprite->selected();
			break;
		case 2: //����
			menuItemSprite->setEnabled(false);
			break;
	}
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
