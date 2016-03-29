#include "HelloWorldScene.h"
#include "AppMacros.h"

USING_NS_CC;
using namespace std;



Scene* HelloWorld::scene()
{
	Scene* scene = Scene::create();

	HelloWorld* layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}


bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
	winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();


//[1].����ͼƬ(Layer����)
	Sprite* bg = Sprite::create("HelloWorld.png");
	bg->setPosition(visibleSize / 2);
	this->addChild(bg);


//[2].�����ü��ڵ� : holesClipper
	holesClipper = ClippingNode::create();
	holesClipper->setPosition(visibleSize / 2);
	this->addChild(holesClipper);

	//��������
	holesClipper->setInverted(true);        //������ʾ��δ���ü�������ʣ�ಿ��
	holesClipper->setAlphaThreshold(0.5f);  //����alpha͸����բֵ
	holesClipper->runAction(RepeatForever::create(RotateBy::create(1, 45))); //��ת����


//[3].����ģ�� : holesStencil
	holesStencil = Node::create();
	holesClipper->setStencil(holesStencil); //����ģ��ڵ�

	//���һ��ģ������ ball
	holesStencil->addChild(Sprite::create("ball.png"), -1);


//[4].�����װ� : holes
	holes = Node::create();
	holesClipper->addChild(holes); //���õװ�

	//�����һ���װ����� blocks
	Sprite* content = Sprite::create("blocks.png");
	holesClipper->addChild(content, -1, "content");


//[5].�����¼�
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
//[1].��ȡ����, ת��Ϊ���holesClipper�ڵ�� �������
	Vec2 point = touches[0]->getLocation();
	point = holesClipper->convertToNodeSpace(point);


//[2].��ȡ�װ��������Rect
	Sprite* content = (Sprite*)this->getChildByName("content");
	Size contentSize = content->getContentSize();
	Rect rect = Rect(-contentSize.width / 2, -contentSize.height / 2, contentSize.width, contentSize.height);


//[3].�������ڵװ��ڲ�, ����"��"
	if (rect.containsPoint(point))
	{
		pokeHoleAtPoint(point);
	}
}

void HelloWorld::pokeHoleAtPoint(Vec2 point)
{
	CCLOG("Add a Hole!!!");


//[1].��ӵװ����� : һ�����ĺۼ�
	auto hole = Sprite::create("hole_effect.png");
	hole->setPosition(point);
	holes->addChild(hole);


//[2].���ģ������ : һ��С��
	auto holeStencil = Sprite::create("hole_stencil.png");
	holeStencil->setPosition(point);
	holesStencil->addChild(holeStencil);


//[3].����Ч�� : �Ŵ���С
	holesClipper->runAction(Sequence::create(ScaleTo::create(0.05f, 1.05f), ScaleTo::create(0.05f, 1.0f), NULL));
}