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


	test1(); //ʹ��ͼƬ��Դ
	test2(); //ʹ�þ���֡
	test3(); //ʹ�ö���֡

	return true;
}


//------------------------------------------------------------------
// ʹ��ͼƬ��Դ
//------------------------------------------------------------------
void HelloWorld::test1()
{

//�����Ļ�ߴ�
	CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();


//��������sprite
	CCSprite* sprite = CCSprite::create("Animation/dance_00.png");
	sprite->setPosition( mysize/2 - ccp(100, 0) );
	this->addChild(sprite);


//����CCAnimation
	CCAnimation* animation = CCAnimation::create();

	//ֱ�����ͼƬ��Դ
	for(int i =1; i <= 14; i++) {
		char str[50];
		sprintf(str, "Animation/dance_%02d.png", i);

		animation->addSpriteFrameWithFileName(str); //��Ӷ���֡
	}

	//��������
	animation->setRestoreOriginalFrame(true); //��ԭ��һ֡
	animation->setDelayPerUnit(2.0/14.0);     //��λ֡���
	animation->setLoops(-1);                  //-1����ѭ��


//����CCAnimate
	CCAnimate* animate = CCAnimate::create(animation);
	CCDelayTime* delay = CCDelayTime::create(2.0f);
	CCSequence* seq = CCSequence::create(delay, animate, NULL);


//ִ�ж�������
	sprite->runAction(seq);

}


//------------------------------------------------------------------
// ʹ�þ���֡
//------------------------------------------------------------------
void HelloWorld::test2()
{

//�����Ļ�ߴ�
	CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();


//��������sprite
	CCSprite* sprite = CCSprite::create("Animation/dance_00.png");
	sprite->setPosition( mysize/2 );
	this->addChild(sprite);


//����CCAnimation
	//��plist������Ķ���ͼƬ����ӵ�����֡�������
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Animation/grossini.plist");

	//��������֡CCSpriteFrame����
	CCArray* array = new CCArray();
	for(int i =1; i <= 14; i++) {
		char str[50];
		sprintf(str, "grossini_dance_%02d.png", i);

		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		array->addObject(frame);
	}

	//ʹ�þ���֡���鴴������λ֡���Ϊ2.0/14.0��
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(array, 2.0/14.0);

	//��������
	animation->setRestoreOriginalFrame(true); //��ԭ��һ֡
	animation->setLoops(-1);                  //����ѭ��


//����CCAnimate
	CCAnimate* animate = CCAnimate::create(animation);
	CCDelayTime* delay = CCDelayTime::create(2.0f);
	CCSequence* seq = CCSequence::create(delay, animate, NULL);


//ִ�ж�������
	sprite->runAction(seq);

}


//------------------------------------------------------------------
// ʹ�ö���֡
//------------------------------------------------------------------
void HelloWorld::test3()
{

//�����Ļ�ߴ�
	CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();


//��������sprite
	CCSprite* sprite = CCSprite::create("Animation/dance_00.png");
	sprite->setPosition( mysize/2 + ccp(100, 0) );
	this->addChild(sprite);


//����CCAnimation
	//��plist������Ķ���ͼƬ����ӵ�����֡����
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Animation/grossini.plist");

	//��������֡CCAnimationFrame����
	CCArray* array = new CCArray();
	for(int i =1; i <= 14; i++) {
		char str[50];
		sprintf(str, "grossini_dance_%02d.png", i);

		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		CCAnimationFrame* animationFrame = new CCAnimationFrame();

		animationFrame->setSpriteFrame(frame); //���þ���֡
		animationFrame->setDelayUnits( i );    //���ü��֡��

		array->addObject(animationFrame);
	}

	//ʹ�ö���֡���鴴������λ֡���0.2��
	CCAnimation* animation = CCAnimation::create(array, 0.2f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);


//����CCAnimate
	CCAnimate* animate = CCAnimate::create(animation);
	CCDelayTime* delay = CCDelayTime::create(2.0f);
	CCSequence* seq = CCSequence::create(delay, animate, NULL);

//ִ�ж�������
	sprite->runAction(seq);

}

