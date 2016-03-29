#include "HelloWorldScene.h"

USING_NS_CC;

#include <string>
using namespace std;

#define UserDefault CCUserDefault::sharedUserDefault()


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

	CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();


	CCLabelTTF* label = CCLabelTTF::create("CCUserDefault test see log", "Arial", 28);
	label->setPosition( mysize/2 );
	this->addChild(label);
	

//����set
	UserDefault->setBoolForKey(   "bool",    true);
	UserDefault->setIntegerForKey("integer", 100);
	UserDefault->setFloatForKey(  "float",   33.33f);
	UserDefault->setDoubleForKey( "double",  44.44);
	UserDefault->setStringForKey( "string",  "1111111");


//��ȡget�������������̨
	//ͨ���ؼ��֣���ȡ����
	bool b = UserDefault->getBoolForKey("bool");
	int i = UserDefault->getIntegerForKey("integer");
	float f = UserDefault->getFloatForKey("float");
	double d = UserDefault->getDoubleForKey("double");
	string ret = UserDefault->getStringForKey("string");

	//���������̨
	CCLOG( (b == true)? "bool is true" : "bool is false" );
	CCLOG("integer is %d", i);
	CCLOG("float is %f", f);
	CCLOG("double is %f", d);
	CCLOG("string is %s", ret.c_str());


//���XML�ļ�·��
	if( UserDefault->isXMLFileExist() ) //�Ƿ����
	{
		string path = UserDefault->getXMLFilePath();
		CCLOG("XML file is exist!");
		CCLOG( "XML file path : %s", path.c_str() );
	}
	else
	{
		CCLOG("XML file is not exist!");
	}


//��������
	UserDefault->flush();


	return true;
}

