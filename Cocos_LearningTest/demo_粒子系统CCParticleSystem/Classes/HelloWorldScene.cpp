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

	testGravity();  //����������ģʽ
	//testRadius();   //�뾶������ģʽ
	//testParticle(); //�ֳ�������Ч 
	//testPlist();    //�Զ���plist������Ч

	return true;
}

//------------------------------------------------------------------
// ����������ģʽ
//------------------------------------------------------------------
void HelloWorld::testGravity()
{
	CCPoint mysize = CCDirector::sharedDirector()->getVisibleSize();


	CCParticleSystemQuad* quad = CCParticleSystemQuad::create();
	this->addChild(quad,1,1);


//����ͼƬ
	quad->setTexture( CCTextureCache::sharedTextureCache()->addImage("HelloWorld.png") ); 


//���ģʽ
	ccBlendFunc cbl = { GL_SRC_ALPHA , GL_ONE};
	quad->setBlendFunc(cbl);


/********************/
/*     ��������     */
/********************/

//������������λ����
	quad->setLife(3);
	quad->setLifeVar(0.25);

//��С��-1��ʾ�ͳ�ʼ��Сһ��
	quad->setStartSize(100);
	quad->setStartSizeVar(0);
	quad->setEndSize(-1);
	quad->setEndSizeVar(0);

//��ɫ��ccc4f��ȡֵ0~1
	quad->setStartColor( ccc4f(192/255.0, 63/255.0, 63/255.0, 63/255.0) );
	quad->setStartColorVar( ccc4f(0, 0, 0, 0) );
	quad->setEndColor( ccc4f(0, 0, 0, 0) );
	quad->setEndColorVar( ccc4f(0, 0, 0, 0) );

//��ת�Ƕ�
	quad->setStartSpin(0);
	quad->setStartSpinVar(60);
	quad->setEndSpin(180);
	quad->setEndSpinVar(30);

//����Ƕ�
	quad->setAngle(90);
	quad->setAngleVar(10);


/********************/
/*  ������������    */
/********************/

//������Ӹ���
	quad->setTotalParticles(1000); 

//���ӷ���������ʱ�䣬-1Ϊ����
	quad->setDuration(-1);

//��������
	quad->setEmissionRate( quad->getTotalParticles()/quad->getLife() );

//������λ��
	quad->setPosition( mysize/2 );
	quad->setPosVar( ccp(10,10) );


//����ģʽ
	quad->setEmitterMode(kCCParticleModeGravity); 

//����λ��ģʽ
	quad->setPositionType(kCCPositionTypeFree);

//�����ٶ�
	quad->setSpeed(60);
	quad->setSpeedVar(20);

//�������ٶ�
	quad->setGravity( ccp(0, 0) ); 

//������ٶ�
	quad->setRadialAccel(0);
	quad->setRadialAccelVar(0);

//������ٶ�
	quad->setTangentialAccel(0);
	quad->setTangentialAccelVar(0);

}


//�뾶������ģʽ
void HelloWorld::testRadius()
{
	CCPoint mysize = CCDirector::sharedDirector()->getVisibleSize();


	CCParticleSystemQuad* quad = CCParticleSystemQuad::create();
	this->addChild(quad,1,1);


//����ͼƬ
	quad->setTexture( CCTextureCache::sharedTextureCache()->addImage("HelloWorld.png") ); 


//���ģʽ
	ccBlendFunc cbl = { GL_SRC_ALPHA , GL_ONE};
	quad->setBlendFunc(cbl);


/********************/
/*     ��������     */
/********************/

//������������λ����
	quad->setLife(3);
	quad->setLifeVar(0.25);

//��С��-1��ʾ�ͳ�ʼ��Сһ��
	quad->setStartSize(20);
	quad->setStartSizeVar(0);
	quad->setEndSize(-1);
	quad->setEndSizeVar(0);

//��ɫ��ccc4f��ȡֵ0~1
	quad->setStartColor( ccc4f(192/255.0, 63/255.0, 63/255.0, 63/255.0) );
	quad->setStartColorVar( ccc4f(0, 0, 0, 0) );
	quad->setEndColor( ccc4f(0, 0, 0, 0) );
	quad->setEndColorVar( ccc4f(0, 0, 0, 0) );

//��ת�Ƕ�
	quad->setStartSpin(0);
	quad->setStartSpinVar(60);
	quad->setEndSpin(180);
	quad->setEndSpinVar(30);

//����Ƕ�
	quad->setAngle(90);
	quad->setAngleVar(10);


/********************/
/*  ������������    */
/********************/

//������Ӹ���
	quad->setTotalParticles(1000); 

//���ӷ���������ʱ�䣬-1Ϊ����
	quad->setDuration(-1);

//��������
	quad->setEmissionRate( quad->getTotalParticles()/quad->getLife() );

//������λ��
	quad->setPosition( mysize/2 );
	quad->setPosVar( ccp(10,10) );


//����ģʽ
	quad->setEmitterMode(kCCParticleModeRadius);

//����λ��ģʽ
	quad->setPositionType(kCCPositionTypeFree);


//��ʼ�뾶
	quad->setStartRadius(20);
	quad->setStartRadiusVar(1);
	
//�����뾶��-1�ͳ�ʼ��Сһ��
	quad->setEndRadius(100);
	quad->setEndRadiusVar(1);

//����Χ�Ƴ�ʼ�㣬ÿ����ת�Ƕ�
	quad->setRotatePerSecond(360);
	quad->setRotatePerSecondVar(1);

}


//�ֳ�������Ч
void HelloWorld::testParticle()
{
	CCParticleFire* quad = CCParticleFire::create();
	this->addChild(quad,1,1);
}


//�Զ���plist������Ч
void HelloWorld::testPlist()
{
	CCPoint mysize = CCDirector::sharedDirector()->getVisibleSize();

	CCParticleSystemQuad* quad = CCParticleSystemQuad::create("1.plist");
	quad->setPosition( mysize/2 );
	this->addChild(quad,1,1);
}



bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pos =pTouch->getLocation();
	CCParticleSystemQuad* quad = (CCParticleSystemQuad*)this->getChildByTag(1);
	quad->setPosition(pos);

	return true;
}

void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pos =pTouch->getLocation();
	CCParticleSystemQuad* quad = (CCParticleSystemQuad*)this->getChildByTag(1);
	quad->setPosition(pos);
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void HelloWorld::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
	CCLayer::onEnter();
}

void HelloWorld::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}