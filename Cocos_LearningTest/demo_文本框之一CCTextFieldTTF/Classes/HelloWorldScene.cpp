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


	CCTextFieldTTF* textFieldTTF = CCTextFieldTTF::textFieldWithPlaceHolder("please input", "Marker Felt", 24);
	//CCTextFieldTTF* textFieldTTF = CCTextFieldTTF::textFieldWithPlaceHolder("please input", CCSize(100,100), CCTextAlignment::kCCTextAlignmentCenter, "Arial", 20);
	textFieldTTF->setPosition( midPos );
	this->addChild(textFieldTTF, 0, 1); //tag���1

	//�����������ί�ж���
	textFieldTTF->setDelegate(this); 

	return true;
}


//���û�����������̵�ʱ��Ļص�����
bool HelloWorld::onTextFieldAttachWithIME(CCTextFieldTTF* sender)
{
	//�¼�����
	sender->setFontSize(30); //����Ŵ�Ϊ30
	sender->setColor(ccYELLOW); //������ɫ: ��ɫ
	sender->setColorSpaceHolder(ccWHITE); //Ĭ��������ɫ: ��ɫ

	return false; //���ü��̡��������ü���return true;
}

//���û��ر�������̵�ʱ��Ļص�����
bool HelloWorld::onTextFieldDetachWithIME(CCTextFieldTTF* sender)
{
	//�¼�����
	sender->setFontSize(24); //�����С��ԭΪ24
	sender->setColor(ccORANGE); //������ɫ: �ٻ�
	sender->setColorSpaceHolder(ccGRAY); //Ĭ��������ɫ: ��ɫ

	return false; //�رռ��̡������رռ���return true;
}

//���û������ʱ��Ļص�����
bool HelloWorld::onTextFieldInsertText(CCTextFieldTTF* sender, const char* text, int nLen)
{
	//�¼�����
	CCLOG("CharCount: %d", sender->getCharCount());

	return false; //�����ַ����������������ַ�return true;
}

//���û�ɾ�����ֵ�ʱ��Ļص�����
bool HelloWorld::onTextFieldDeleteBackward(CCTextFieldTTF* sender, const char* delText, int nLen)
{
	return false; //ɾ���ַ�����������ɾ���ַ�return true;
}


bool HelloWorld::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLOG("ccTouchBegan");
	return true;
}

void HelloWorld::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCLOG("ccTouchMoved");
}

void HelloWorld::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCLOG("ccTouchEnded");

//��ȡ����
	CCPoint pos = touch->getLocation();

//��ȡtextFieldTTF���ڵľ�������rect
	CCTextFieldTTF* textFieldTTF = (CCTextFieldTTF*)this->getChildByTag(1);
	float x = textFieldTTF->getPositionX() - textFieldTTF->getContentSize().width/2;
	float y = textFieldTTF->getPositionY() - textFieldTTF->getContentSize().height/2;
	float width = textFieldTTF->getContentSize().width;
	float height = textFieldTTF->getContentSize().height;
	CCRect rect = CCRectMake(x, y, width, height);

//�жϴ����Ƿ������ı����ڲ�
	if( rect.containsPoint(pos) ) {
		CCLOG("attachWithIME");
		textFieldTTF->attachWithIME(); //�����������
	}else {
		CCLOG("detachWithIME");
		textFieldTTF->detachWithIME(); //�ر��������
	}
}


//��������
void HelloWorld::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	CCLayer::onEnter();
}

//ɾ������
void HelloWorld::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
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
