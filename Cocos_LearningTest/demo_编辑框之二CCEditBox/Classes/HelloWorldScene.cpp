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

	

//�༭��ߴ��С
	CCSize editBoxSize = CCSizeMake(mysize.width - 100, 60);


//�û���editBoxName
	CCEditBox* editBoxName = CCEditBox::create(editBoxSize, CCScale9Sprite::create("green_edit.png"));
	editBoxName->setPosition( ccp(mysize.width/2, mysize.height*3/4) );
	this->addChild(editBoxName);

	//��������
	editBoxName->setFontName("fonts/Paint Boy.ttf");
	editBoxName->setFontSize(20);
	editBoxName->setFontColor(ccRED);
	editBoxName->setPlaceHolder("Name:");
	editBoxName->setPlaceholderFontColor(ccWHITE);
	editBoxName->setMaxLength(8);

	//ģʽ��������
	editBoxName->setInputMode(kEditBoxInputModeSingleLine);
	editBoxName->setInputFlag(kEditBoxInputFlagInitialCapsAllCharacters);
	editBoxName->setReturnType(kKeyboardReturnTypeDefault);

	//ί�д������this
	editBoxName->setDelegate(this);


//����editBoxPassword
	CCEditBox* editBoxPassword = CCEditBox::create(editBoxSize, CCScale9Sprite::create("orange_edit.png"));
	editBoxPassword->setPosition( midPos );
	this->addChild(editBoxPassword);

	//��������
	editBoxPassword->setFont("fonts/Marker Felt.ttf", 30);
	editBoxPassword->setFontColor(ccGREEN);
	editBoxPassword->setPlaceHolder("Password:");
	editBoxPassword->setMaxLength(6);

	//ģʽ����
	editBoxPassword->setInputFlag(kEditBoxInputFlagPassword);
	editBoxPassword->setReturnType(kKeyboardReturnTypeDone);

	//ί�д������this
	editBoxPassword->setDelegate(this);
	

//����editBoxEmail
	CCEditBox* editBoxEmail = CCEditBox::create(editBoxSize, CCScale9Sprite::create("yellow_edit.png"));
	editBoxEmail->setPosition( ccp(mysize.width/2, mysize.height/4) );
	this->addChild(editBoxEmail);

	//��������
	editBoxEmail->setFont("fonts/Marker Felt.ttf", 30);
	editBoxEmail->setPlaceHolder("Email:");

	//ģʽ��������
	editBoxEmail->setInputMode(kEditBoxInputModeEmailAddr);
	editBoxEmail->setReturnType(kKeyboardReturnTypeSend);

	//ί�д������this
	editBoxEmail->setDelegate(this);

	return true;
}


//��ʼ�༭
void HelloWorld::editBoxEditingDidBegin(CCEditBox* editBox)
{
	CCLog("editBox %p DidBegin !", editBox);
}

//�����༭
void HelloWorld::editBoxEditingDidEnd(CCEditBox* editBox)
{
	CCLog("editBox %p DidEnd !", editBox);
}

//�༭�����ݸı�
void HelloWorld::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{
	CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

//����return����
void HelloWorld::editBoxReturn(CCEditBox* editBox)
{
	CCLog("editBox %p was returned !",editBox);
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
