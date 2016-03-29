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

	CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();


//����CCTableView
	CCTableView* tableView1 = CCTableView::create(this, CCSizeMake(250, 60));
	tableView1->setPosition(ccp(20, mysize.height/2 - 30));
	this->addChild(tableView1);

	//��������
	tableView1->setBounceable(false);							//�رյ���Ч��
	tableView1->setDirection(kCCScrollViewDirectionHorizontal); //����
	tableView1->setDelegate(this);								//ί�д���
	tableView1->reloadData();									//��������


//����CCTableView
	CCTableView* tableView2 = CCTableView::create(this, CCSizeMake(60, 250));
	tableView2->setPosition(ccp(mysize.width - 150, mysize.height/2 - 120));
	this->addChild(tableView2);

	//��������
	tableView2->setDirection(kCCScrollViewDirectionVertical);	//����
	tableView2->setVerticalFillOrder(kCCTableViewFillTopDown);	//��С��������
	tableView2->setDelegate(this);								//ί�д���
	tableView2->reloadData();									//��������


	return true;
}


//��ȡ���Ϊidx��cell
CCTableViewCell* HelloWorld::tableCellAtIndex(CCTableView* table, unsigned int idx)
{
	char Icon[20];   //����idxѡ����ʾ��ͼƬ
	char number[10]; //��ʾlabel��ǩ������
	sprintf(Icon, "sp%d.png", idx%3 + 1);
	sprintf(number, "%02d", idx);

	//Ҳ������cell = table->cellAtIndex(idx);
	CCTableViewCell* cell = table->dequeueCell();
	
	if(!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease(); //�Զ��ͷ���Դ

		//���һ������ͼƬ
		CCSprite* sprite = CCSprite::create(Icon);
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(ccp(0, 0));
		cell->addChild(sprite, 0, 1);

		//���һ��label��ǩ
		CCLabelTTF* label = CCLabelTTF::create(number, "Arial", 20);
		label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
		cell->addChild(label, 0, 2);
	}
	else
	{
		//��������ͼƬ��ʹ������
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(Icon);
		CCSprite* sprite = (CCSprite*)cell->getChildByTag(1);
		sprite->setTexture(texture);

		//����ͼƬ���
		CCLabelTTF* label = (CCLabelTTF*)cell->getChildByTag(2);
		label->setString(number);
	}

	return cell;
}


//����idx������ÿ��cell�ĳߴ��С
CCSize HelloWorld::tableCellSizeForIndex(CCTableView* table, unsigned int idx)
{
	if(idx == 2) return CCSizeMake(100,100);
	return CCSizeMake(60,60);
}


//һ��������cell
unsigned int HelloWorld::numberOfCellsInTableView(CCTableView* table)
{
	return 10;
}


//ĳ��cell�����ʱ�ص�����
void HelloWorld::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx()); //����̨���
}


void HelloWorld::scrollViewDidScroll(cocos2d::extension::CCScrollView* view) { } //����ʱ�ص�����
void HelloWorld::scrollViewDidZoom(cocos2d::extension::CCScrollView* view) { }   //����ʱ�ص�����

