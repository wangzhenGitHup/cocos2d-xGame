#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "cocos-ext.h"
using namespace cocos2d::extension;


class HelloWorld : public cocos2d::CCLayer,public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();
	CREATE_FUNC(HelloWorld);


	//�̳���CCTableViewDataSource
	virtual CCSize tableCellSizeForIndex(CCTableView* table, unsigned int idx);      //����idx������ÿ��cell�ĳߴ��С
	virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx); //��ȡ���Ϊidx��cell
	virtual unsigned int numberOfCellsInTableView(CCTableView* table);               //һ��������cell

	//�̳���CCTableViewDelegate
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);        //ĳ��cell�����ʱ�ص�����
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);        //����ʱ�ص�����
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);          //����ʱ�ص�����
};

#endif // __HELLOWORLD_SCENE_H__
