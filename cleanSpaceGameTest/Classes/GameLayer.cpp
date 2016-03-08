#include"GameLayer.h"
#include"GameOverLayer.h"
#include"SelectLayer.h"
#include"SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

GameLayer::GameLayer() : m_time(60), m_mapLBX(0), m_mapLBY(0),
	m_spriteSheet(NULL), m_firstIcon(NULL), m_secondIcon(NULL),
	m_isTouchIcon(true), m_isFourthBoom(true), m_isAction(true),
	m_isFillIcon(false), m_score(0)
{}

CCScene* GameLayer::scene()
{
	CCScene* scene = CCScene::create();
	GameLayer* layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	this->setTouchEnabled(true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* bg = CCSprite::create("scene_bg.png");
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg, -1);

	CCMenuItemImage* backItem = CCMenuItemImage::create(
		"btn_back01.png", "btn_back02.png",
		this,
		menu_selector(GameLayer::menuBackCallback)
	);
	backItem->setPosition(ccp(winSize.width - backItem->getContentSize().width / 2, backItem->getContentSize().height / 2));
	CCMenu* menu = CCMenu::create(backItem, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	//最高分
	CCLabelTTF* highestScoreLabel = CCLabelTTF::create("HighestScore: 0", "Marker Felt.ttf", 30);
	highestScoreLabel->setPosition(ccp(winSize.width - highestScoreLabel->getContentSize().width,
		winSize.height - highestScoreLabel->getContentSize().height));
	CCString* strScore = CCString::createWithFormat("%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Score"));
	highestScoreLabel->setString(strScore->getCString());
	this->addChild(highestScoreLabel);

	//分数
	CCLabelTTF* scoreLabel = CCLabelTTF::create("Score: 0", "Marker Felt.ttf", 30);
	scoreLabel->setPosition(ccp(winSize.width / 2, winSize.height - scoreLabel->getContentSize().height * 2.6));
	scoreLabel->setTag(SCORE_GAME_TAG);
	this->addChild(scoreLabel);

	//时间
	CCLabelTTF* timeLabel = CCLabelTTF::create("Time: 60", "Marker Felt.ttf", 30);
	timeLabel->setPosition(ccp(timeLabel->getContentSize().width, winSize.height - timeLabel->getContentSize().height));
	timeLabel->setTag(TIME_TAG);
	this->addChild(timeLabel);

	//初始化坐标值 居中
	m_mapLBX = (winSize.width - ICON_WIDTH * COLS - (COLS - 1) * BOADER_WIDTH) / 2;
	m_mapLBY = (winSize.height - ICON_WIDTH * ROWS - (ROWS - 1) * BOADER_WIDTH) / 2;

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("icon.plist");
	m_spriteSheet = CCSpriteBatchNode::create("icon.png");
	this->addChild(m_spriteSheet);

	this->initMap();
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameLayer::updateClock), 1.0f);

	return true;
}

void GameLayer::initMap()
{
	int r, c;

	for(r = 0; r < ROWS; r++)
	{
		for(c = 0; c < COLS; c++)
		{
			this->createGameIcon(r, c);
		}
	}
}

void GameLayer::update(float dt)
{
	if(m_isAction)
	{
		m_isAction = false;
		for(int r = 0; r < ROWS; r++)
		{
			for(int c = 0; c < COLS; c++)
			{
				IconSprite* iconSp = m_iconMap[r][c];
				if(iconSp && iconSp->numberOfRunningActions() > 0)
				{
					m_isAction = true;
					break;
				}
			}
		}
	}

	m_isTouchIcon = !m_isAction;
	if(!m_isAction)
	{
		if(m_isFillIcon)
		{
			this->fillIcon();
			m_isFillIcon = false;
			if(!this->isHaveMoveIcon())
			{
				for(int row = 0; row < ROWS; row++)
				{
					for(int col = 0; col < COLS; col++)
					{
						m_iconMap[row][col]->setIsNeedRemove(true);
					}
					this->removeIcon();
				}
			}
		}
		else
		{
			this->checkAndRemoveIcon();
		}
	}
	CCLabelTTF* labelScore = (CCLabelTTF*)this->getChildByTag(SCORE_GAME_TAG);
	CCString* strScore = CCString::createWithFormat("Score: %d", this->getScore());
	labelScore->setString(strScore->getCString());
}

void GameLayer::updateClock(float dt)
{
	--m_time;
	if(0 == m_time)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		if(CCUserDefault::sharedUserDefault()->getBoolForKey(SOUND_KEY))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("sound/music_gameOver.mp3", false);
		}
		CCLabelTTF* labelTime = (CCLabelTTF*)this->getChildByTag(TIME_TAG);
		labelTime->setScale(0);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* overSp = CCSprite::create("pic_gameover.png");
		overSp->setPosition(ccp(winSize.width / 2, winSize.height * 1.5));
		this->addChild(overSp);

		CCMoveTo* moveTo = CCMoveTo::create(3.0f, ccp(winSize.width / 2, winSize.height / 2));
		overSp->runAction(moveTo);
		this->scheduleOnce(schedule_selector(GameLayer::gameOver), 3.5f);
		return;
	}

	if(m_time > 0)
	{
		CCLabelTTF* labelTime = (CCLabelTTF*)this->getChildByTag(TIME_TAG);
		CCString* strTime = CCString::createWithFormat("Time: %d", m_time);
		labelTime->setString(strTime->getCString());
	}
}

void GameLayer::gameOver(float dt)
{
	CCScene* scene = GameOverLayer::scene(this->getScore());
	CCTransitionFadeUp* transitionScene = CCTransitionFadeUp::create(1.0f, scene);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void GameLayer::menuBackCallback(CCObject* obj)
{
	CCScene* scene = SelectLayer::scene();
	CCTransitionMoveInR* transitionScene = CCTransitionMoveInR::create(1.0f, scene);
	CCDirector::sharedDirector()->replaceScene(transitionScene);
}

void GameLayer::createGameIcon(int row, int col)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	IconSprite* iconSp = IconSprite::createIcon(row, col);
	CCPoint endPos = this->getIconItemOfPosition(row, col);
	CCPoint startPos = ccp(endPos.x, endPos.y + winSize.height / 2);
	iconSp->setPosition(startPos);

	float speed = startPos.y / (1.5 * winSize.height);
	CCMoveTo* moveAction = CCMoveTo::create(speed, endPos);
	iconSp->runAction(moveAction);

	m_spriteSheet->addChild(iconSp);
	m_iconMap[row][col] = iconSp;
}

CCPoint GameLayer::getIconItemOfPosition(int row, int col)
{
	float x = m_mapLBX + (ICON_WIDTH + BOADER_WIDTH) * col + ICON_WIDTH / 2;
	float y = m_mapLBY + (ICON_WIDTH + BOADER_WIDTH) * row + ICON_WIDTH / 2;
	return ccp(x, y);
}

//补充消除的icon
void GameLayer::fillIcon()
{
	int row, col, sum = 0;
	int nullIconCount = 0;	
	IconSprite* iconSp = NULL;
	int* emptyColInfo = (int*) malloc (sizeof(int) * COLS);
	memset((void*)emptyColInfo, 0, sizeof(int) * COLS);

	m_isFourthBoom = true;
	m_isAction = true;

	for(col = 0; col < COLS; col++)
	{	
		nullIconCount = 0;
		for(row = 0; row < ROWS; row++)
		{
			iconSp = m_iconMap[row][col];
			if(!iconSp)
			{
				nullIconCount++;
			}
			else
			{
				if(nullIconCount > 0)
				{
					int newRow = row - nullIconCount;
					m_iconMap[newRow][col] = iconSp;
					m_iconMap[row][col] = NULL;
					CCPoint startPos = iconSp->getPosition();
					CCPoint endPos = this->getIconItemOfPosition(newRow, col);
					float speed = (startPos.y - endPos.y) / (CCDirector::sharedDirector()->getWinSize().height * 3);
					CCMoveTo* moveTo = CCMoveTo::create(speed, endPos);
					iconSp->stopAllActions();
					iconSp->runAction(moveTo);
					iconSp->setRow(newRow);
				}
			}
		}
		emptyColInfo[col] = nullIconCount;
		sum += nullIconCount;
	}

	for(col = 0; col < COLS; col++)
	{
		if(0 == emptyColInfo[col])
		{
			continue;
		}

		for(row = ROWS - emptyColInfo[col]; row < ROWS; row++)
		{
			this->createGameIcon(row, col);
		}
	}
	this->setScore(this->getScore() + sum * 30);
	free(emptyColInfo);
	emptyColInfo = NULL;
}

bool GameLayer::isHaveMoveIcon()
{
	for(int row = 0; row < ROWS; row++)
	{
		for(int col = 0; col < COLS; col++)
		{
			if(m_iconMap[row][col]->getImageIndex() == this->findIconIndex(row, col - 1, row - 1, col + 1, row + 1, col + 1))
			{
				return true;
			}

			if(m_iconMap[row][col]->getImageIndex() == this->findIconIndex(row, col + 1, row - 1, col - 1, row + 1, col - 1))
			{
				return true;
			}

			if(m_iconMap[row][col]->getImageIndex() == this->findIconIndex(row - 1, col, row + 1, col - 1, row + 1, col + 1))
			{
				return true;
			}

			if(m_iconMap[row][col]->getImageIndex() == this->findIconIndex(row + 1, col, row - 1, col - 1, row - 1, col + 1))
			{
				return true;
			}
		}
	}
	return false;
}

int GameLayer::findIconIndex(int r1, int c1, int r2, int c2, int r3, int c3)
{
	bool isIconOne = false;
	bool isIconTwo = false;
	bool isIconThree = false;

	if(r1 >= 0 && r1 < ROWS && c1 >= 0 && c1 < COLS)
	{
		isIconOne = true;
	}

	if(r2 >= 0 && r2 < ROWS && c2 >= 0 && c2 < COLS)
	{
		isIconTwo = true;
	}

	if(r3 >= 0 && r3 < ROWS  && c3 >= 0 && c3 < COLS)
	{
		isIconThree = true;
	}

	if(isIconOne)
	{
		if(isIconTwo)
		{
			if(m_iconMap[r1][c1]->getImageIndex() == m_iconMap[r2][c2]->getImageIndex())
			{
				return m_iconMap[r1][c1]->getImageIndex();
			}
		}

		if(isIconThree)
		{
			if(m_iconMap[r1][c1]->getImageIndex() == m_iconMap[r3][c3]->getImageIndex())
			{
				return m_iconMap[r1][c1]->getImageIndex();
			}
		}
	}

	if(isIconTwo && isIconThree)
	{
		if(m_iconMap[r2][c2]->getImageIndex() == m_iconMap[r3][c3]->getImageIndex())
		{
			return m_iconMap[r2][c2]->getImageIndex();
		}
	}
	return - 1;
}

void GameLayer::removeIcon()
{
	m_isAction = true;

	for(int row = 0; row < ROWS; row++)
	{
		for(int col = 0; col < COLS; col++)
		{
			IconSprite* iconSp = m_iconMap[row][col];
			if(!iconSp)
			{
				continue;
			}

			if(iconSp->getIsNeedRemove())
			{
				m_isFillIcon = true;
				if(iconSp->getDisplayMode() == DISPLAY_MODE_HORIZONTAL)
				{
					m_time += 3;
					this->addTime();
					this->explodeSpecialH(iconSp->getPosition());
				}
				else if(iconSp->getDisplayMode() == DISPLAY_MODE_VERTICAL)
				{
					m_time += 3;
					this->addTime();
					this->explodeSpecialV(iconSp->getPosition());
				}
				this->explodeIcon(iconSp);
			}
		}
	}
}

//水平爆炸效果
void GameLayer::explodeSpecialH(CCPoint iconPos)
{
	if(CCUserDefault::sharedUserDefault()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sound/music_explodeOne.wav", false);
	}

	float scaleX = 4.0f;
	float scaleY = 0.7f;
	float time = 0.3f;
	CCPoint startPos = iconPos;
	float speed = 0.6f;

	CCSprite* colorSpriteRight = CCSprite::create("colorHRight.png");
	colorSpriteRight->setPosition(startPos);
	this->addChild(colorSpriteRight, 10);

	CCPoint endPosRight = ccp(iconPos.x - CCDirector::sharedDirector()->getWinSize().width, iconPos.y);
	CCCallFuncND* funcDoneRight = CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeNode), (void*)colorSpriteRight);
	CCScaleTo* scaleTo = CCScaleTo::create(time, scaleX, scaleY);
	CCMoveTo* moveToRight = CCMoveTo::create(speed, endPosRight);
	CCSequence* seqRight = CCSequence::create(scaleTo, moveToRight, funcDoneRight, NULL);
	colorSpriteRight->runAction(seqRight);

	CCSprite* colorSpriteLeft = CCSprite::create("colorHLeft.png");
	colorSpriteLeft->setPosition(startPos);
	this->addChild(colorSpriteLeft, 10);

	CCPoint endPosLeft = ccp(iconPos.x + CCDirector::sharedDirector()->getWinSize().width, iconPos.y);
	CCCallFuncND* funcDoneLeft = CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeNode), (void*)colorSpriteLeft);
	CCMoveTo* moveToLeft = CCMoveTo::create(speed, endPosLeft);
	CCSequence* seqLeft = CCSequence::create(scaleTo, moveToLeft, funcDoneLeft, NULL);
	colorSpriteLeft->runAction(seqLeft);
}

//垂直爆炸效果
void GameLayer::explodeSpecialV(CCPoint iconPos)
{
	if(CCUserDefault::sharedUserDefault()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sound/music_explodeOne.wav", false);
	}

	float scaleX = 0.7f;
	float scaleY = 4.0f;
	float time = 0.3f;
	CCPoint startPos = iconPos;
	float speed = 0.6f;

	CCSprite* colorSpriteDown = CCSprite::create("colorVDown.png");
	colorSpriteDown->setPosition(startPos);
	this->addChild(colorSpriteDown, 10);

	CCPoint endPosDown = ccp(iconPos.x , iconPos.y - CCDirector::sharedDirector()->getWinSize().height);
	CCCallFuncND* funcDoneDown = CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeNode), (void*)colorSpriteDown);
	CCScaleTo* scaleTo = CCScaleTo::create(time, scaleX, scaleY);
	CCMoveTo* moveToDown = CCMoveTo::create(speed, endPosDown);
	CCSequence* seqDown = CCSequence::create(scaleTo, moveToDown, funcDoneDown, NULL);
	colorSpriteDown->runAction(seqDown);

	CCSprite* colorSpriteUp = CCSprite::create("colorVUp.png");
	colorSpriteUp->setPosition(startPos);
	this->addChild(colorSpriteUp, 10);

	CCPoint endPosUp = ccp(iconPos.x, iconPos.y + CCDirector::sharedDirector()->getWinSize().height);
	CCCallFuncND* funcDoneUp = CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeNode), (void*)colorSpriteUp);
	CCMoveTo* moveToUp = CCMoveTo::create(speed, endPosUp);
	CCSequence* seqUp = CCSequence::create(scaleTo, moveToUp, funcDoneUp, NULL);
	colorSpriteUp->runAction(seqUp);
}

void GameLayer::explodeIcon(IconSprite* icon)
{
	if(CCUserDefault::sharedUserDefault()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sound/music_explode.wav", false);
	}
	float time = 0.2f;
	CCScaleTo* scaleTo = CCScaleTo::create(time, 0);
	CCCallFuncN* funcDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::explodeFinish));
	CCSequence* seq = CCSequence::create(scaleTo, funcDone, NULL);
	icon->runAction(seq);

	CCSprite* circleSp = CCSprite::create("circle.png");
	circleSp->setPosition(icon->getPosition());
	circleSp->setScale(0);
	this->addChild(circleSp);

	CCScaleTo* scaleTo2 = CCScaleTo::create(time, 1.0f);
	CCCallFuncND* funcNDDone = CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeNode), (void*)circleSp);
	CCSequence* seq2 = CCSequence::create(scaleTo2, funcNDDone, NULL);
	circleSp->runAction(seq2);
}

void GameLayer::explodeFinish(CCNode* node)
{
	IconSprite* iconSp = (IconSprite*)node;
	m_iconMap[iconSp->getRow()][iconSp->getCol()] = NULL;
	iconSp->removeFromParent();
}

void GameLayer::checkAndRemoveIcon()
{
	IconSprite* iconSp = NULL;
	int row, col;

	for(row = 0; row < ROWS; row++)
	{
		for(col = 0; col < COLS; col++)
		{
			iconSp = m_iconMap[row][col];
			if(!iconSp)
			{
				continue;
			}
			iconSp->setIgnoreCheck(false);
		}
	}

	for(row = 0; row < ROWS; row++)
	{
		for(col = 0; col < COLS; col++)
		{
			iconSp = m_iconMap[row][col];
			if(!iconSp)
			{
				continue;
			}

			if(iconSp->getIsNeedRemove())
			{
				continue;
			}
			if(iconSp->getIgnoreCheck())
			{
				continue;
			}
			std::list<IconSprite*> colChainList;
			this->getColChainIcon(iconSp, colChainList);

			std::list<IconSprite*> rowChainList;
			this->getRowChainIcon(iconSp, rowChainList);

			std::list<IconSprite*> &theLongerList = (colChainList.size() > rowChainList.size()) ? colChainList : rowChainList;
			if(theLongerList.size() < 3)
			{
				continue;
			}

			std::list<IconSprite*>::iterator it;
			bool isSetedIgnoreCheck = false;

			for(it = theLongerList.begin(); it != theLongerList.end(); ++it)
			{
				iconSp = (IconSprite*) *it;
				if(!iconSp)
				{
					continue;
				}

				if(theLongerList.size() > 3)
				{
					if(iconSp == m_firstIcon)
					{
						isSetedIgnoreCheck = true;
						iconSp->setIgnoreCheck(true);
						iconSp->setIsNeedRemove(false);
						iconSp->setDisplayMode(m_isFourthBoom ? DISPLAY_MODE_VERTICAL : DISPLAY_MODE_HORIZONTAL);
						continue;
					}
				}
				this->markRemove(iconSp);
			}
			if(!isSetedIgnoreCheck && theLongerList.size() > 3)
			{
				iconSp->setIgnoreCheck(true);
				iconSp->setIsNeedRemove(false);
				iconSp->setDisplayMode(m_isFourthBoom ? DISPLAY_MODE_VERTICAL : DISPLAY_MODE_HORIZONTAL);
			}
		}
	}
	this->removeIcon();
}

void GameLayer::markRemove(IconSprite* iconSp)
{
	if(iconSp->getIsNeedRemove())
	{
		return;
	}

	if(iconSp->getIgnoreCheck())
	{
		return;
	}
	iconSp->setIsNeedRemove(true);
	
	//垂直方向
	if(iconSp->getDisplayMode() == DISPLAY_MODE_VERTICAL)
	{
		for(int row = 0; row < ROWS; row++)
		{
			IconSprite* tmpIcon = m_iconMap[row][iconSp->getCol()];
			if(!tmpIcon || tmpIcon == iconSp)
			{
				continue;
			}
			
			if(tmpIcon->getDisplayMode() == DISPLAY_MODE_NORMAL)
			{
				tmpIcon->setIsNeedRemove(true);
			}
			else
			{
				this->markRemove(tmpIcon);
			}
		}
	}
	else if(iconSp->getDisplayMode() == DISPLAY_MODE_HORIZONTAL)
	{
		for(int col = 0; col < COLS; col++)
		{
			IconSprite* tmpIcon = m_iconMap[iconSp->getRow()][col];
			if(!tmpIcon || tmpIcon == iconSp)
			{
				continue;
			}

			if(tmpIcon->getDisplayMode() == DISPLAY_MODE_NORMAL)
			{
				tmpIcon->setIsNeedRemove(true);
			}
			else
			{
				this->markRemove(tmpIcon);
			}
		}
	}
}

void GameLayer::swapIcons()
{
	m_isAction = true;
	m_isTouchIcon = false;

	if(!m_firstIcon || !m_secondIcon)
	{
		m_isFourthBoom = true;
		return;
	}
	float time = 0.2f;
	CCPoint firstPos = m_firstIcon->getPosition();
	CCPoint secondPos = m_secondIcon->getPosition();
	m_iconMap[m_firstIcon->getRow()][m_firstIcon->getCol()] = m_secondIcon;
	m_iconMap[m_secondIcon->getRow()][m_secondIcon->getCol()] = m_firstIcon;

	int tmpRow = m_firstIcon->getRow();
	int tmpCol = m_firstIcon->getCol();
	m_firstIcon->setRow(m_secondIcon->getRow());
	m_firstIcon->setCol(m_secondIcon->getCol());
	m_secondIcon->setRow(tmpRow);
	m_secondIcon->setCol(tmpCol);
	
	std::list<IconSprite*> colChainIconListFirst;
	this->getColChainIcon(m_firstIcon, colChainIconListFirst);

	std::list<IconSprite*> rowChainIconListFirst;
	this->getRowChainIcon(m_firstIcon, rowChainIconListFirst);

	std::list<IconSprite*> colChainIconListSecond;
	this->getColChainIcon(m_secondIcon, colChainIconListSecond);

	std::list<IconSprite*> rowChainIconListSecond;
	this->getRowChainIcon(m_secondIcon, rowChainIconListSecond);

	if(colChainIconListFirst.size() >= 3 
		|| rowChainIconListFirst.size() >= 3
		|| colChainIconListSecond.size() >= 3
		|| rowChainIconListSecond.size() >= 3)
	{
		m_firstIcon->runAction(CCMoveTo::create(time, secondPos));
		m_secondIcon->runAction(CCMoveTo::create(time, firstPos));
		return;
	}

	//以下重复上面的行为主要是 如果交换位置不成功 就给它们还原
	m_iconMap[m_firstIcon->getRow()][m_firstIcon->getCol()] = m_secondIcon;
	m_iconMap[m_secondIcon->getRow()][m_secondIcon->getCol()] = m_firstIcon;

	tmpRow = m_firstIcon->getRow();
	tmpCol = m_firstIcon->getCol();
	m_firstIcon->setRow(m_secondIcon->getRow());
	m_firstIcon->setCol(m_secondIcon->getCol());
	m_secondIcon->setRow(tmpRow);
	m_secondIcon->setCol(tmpCol);

	m_firstIcon->runAction(CCSequence::create(CCMoveTo::create(time, secondPos), 
		CCMoveTo::create(time, firstPos), NULL));
	m_secondIcon->runAction(CCSequence::create(CCMoveTo::create(time, firstPos),
		CCMoveTo::create(time, secondPos), NULL));
}

void GameLayer::getColChainIcon(IconSprite* iconSp, std::list<IconSprite*>& iconlist)
{
	iconlist.push_back(iconSp);
	int neighborCol = iconSp->getCol() - 1;
	while(neighborCol >= 0)
	{
		IconSprite* neighborSp = m_iconMap[iconSp->getRow()][neighborCol];
		if(neighborSp && (neighborSp->getImageIndex() == iconSp->getImageIndex()) && 
			!neighborSp->getIsNeedRemove() && !neighborSp->getIgnoreCheck())
		{
			iconlist.push_back(neighborSp);
			neighborCol--;
		}
		else
		{
			break;
		}
	}
	neighborCol = iconSp->getCol() + 1;
	while(neighborCol < COLS)
	{
		IconSprite* neighborSp = m_iconMap[iconSp->getRow()][neighborCol];
		if(neighborSp && (neighborSp->getImageIndex() == iconSp->getImageIndex())
			&& !neighborSp->getIsNeedRemove() && !neighborSp->getIgnoreCheck())
		{
			iconlist.push_back(neighborSp);
			neighborCol++;
		}
		else
		{
			break;
		}
	}
}

void GameLayer::getRowChainIcon(IconSprite* iconSp, std::list<IconSprite*>& iconlist)
{
	iconlist.push_back(iconSp);
	int neighborRow = iconSp->getRow() - 1;

	while(neighborRow >= 0)
	{
		IconSprite* neighborSp = m_iconMap[neighborRow][iconSp->getCol()];
		if(neighborSp && (neighborSp->getImageIndex() == iconSp->getImageIndex()) 
			&& !neighborSp->getIsNeedRemove() && !neighborSp->getIgnoreCheck())
		{
			iconlist.push_back(neighborSp);
			neighborRow--;
		}
		else
		{
			break;
		}
	}

	neighborRow = iconSp->getRow() + 1;
	while(neighborRow < ROWS)
	{
		IconSprite* neighborSp = m_iconMap[neighborRow][iconSp->getCol()];
		if(neighborSp && (neighborSp->getImageIndex() == iconSp->getImageIndex()) 
			&& !neighborSp->getIsNeedRemove() && !neighborSp->getIgnoreCheck())
		{
			iconlist.push_back(neighborSp);
			neighborRow++;
		}
		else
		{
			break;
		}
	}
}

void GameLayer::removeNode(CCNode* node, void* data)
{
	CCSprite* icon = (CCSprite*)data;
	this->removeChild(icon, true);
}

void GameLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	m_firstIcon = NULL;
	m_secondIcon = NULL;

	if(m_isTouchIcon)
	{
		CCPoint pos = pTouch->getLocation();
		m_firstIcon = getIconOfPosition(&pos);
	}

	return m_isTouchIcon;
}

void GameLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{}

void GameLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	if(!m_firstIcon || !m_isTouchIcon)
	{
		return;
	}
	int row = m_firstIcon->getRow();
	int col = m_firstIcon->getCol();
	CCPoint locationPos = pTouch->getLocation();
	int halfIconW = ICON_WIDTH / 2;
	int halfIconH = ICON_WIDTH / 2;

	CCRect upRect = CCRect(m_firstIcon->getPositionX() - halfIconW, m_firstIcon->getPositionY() + halfIconH, 
		ICON_WIDTH, ICON_WIDTH);
	if(upRect.containsPoint(locationPos))
	{
		++row;
		if(row < ROWS)
		{
			m_secondIcon = m_iconMap[row][col];
		}
		m_isFourthBoom = true;
		this->swapIcons();
		return;
	}

	CCRect downRect = CCRect(m_firstIcon->getPositionX() - halfIconW, m_firstIcon->getPositionY() - halfIconH * 3,
		ICON_WIDTH, ICON_WIDTH);
	if(downRect.containsPoint(locationPos))
	{
		--row;
		if(row >= 0)
		{
			m_secondIcon = m_iconMap[row][col];
		}
		m_isFourthBoom = true;
		this->swapIcons();
		return;
	}

	CCRect rightRect = CCRect(m_firstIcon->getPositionX() + halfIconW, m_firstIcon->getPositionY() - halfIconH,
		ICON_WIDTH, ICON_WIDTH);
	if(rightRect.containsPoint(locationPos))
	{
		++col;
		if(col < COLS)
		{
			m_secondIcon = m_iconMap[row][col];
		}
		m_isFourthBoom = true;
		this->swapIcons();
		return;
	}

	CCRect leftRect = CCRect(m_firstIcon->getPositionX() - halfIconW * 3, m_firstIcon->getPositionY() - halfIconH,
		ICON_WIDTH, ICON_WIDTH);
	if(leftRect.containsPoint(locationPos))
	{
		--col;
		if(col >= 0)
		{
			m_secondIcon = m_iconMap[row][col];
		}
		m_isFourthBoom = true;
		this->swapIcons();
		return;
	}
}

void GameLayer::addTime()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* labelTime = (CCLabelTTF*)this->getChildByTag(TIME_TAG);
	CCSprite* sp = CCSprite::create("sprite_plus3.png");
	sp->setPosition(ccp(labelTime->getContentSize().width + sp->getContentSize().width * 1.3,
		winSize.height - labelTime->getContentSize().height * 0.4));
	sp->setScale(1.6f);
	this->addChild(sp);

	CCScaleTo* scaleTo = CCScaleTo::create(0.4f, 0);
	sp->runAction(scaleTo);
}

void GameLayer::onEnter()
{
	CCLayer::onEnter();
}

void GameLayer::onExit()
{
	CCLayer::onExit();
	SimpleAudioEngine::sharedEngine()->end();
}

void GameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	if(CCUserDefault::sharedUserDefault()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/music_bg.mp3", true);
	}
}

void GameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

void GameLayer::cleanup()
{
	CCLayer::cleanup();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("music_bg.mp3");
}

IconSprite* GameLayer::getIconOfPosition(CCPoint* pos)
{
	IconSprite* iconSp = NULL;
	int r, c;
	CCSize size = CCSize(ICON_WIDTH, ICON_WIDTH);
	CCRect rect = CCRect(0, 0, 0, 0);
	
	for(r = 0; r < ROWS; r++)
	{
		for(c = 0; c < COLS; c++)
		{
			iconSp = m_iconMap[r][c];
			if(iconSp)
			{
				rect.origin.x = iconSp->getPositionX() - (ICON_WIDTH / 2);
				rect.origin.y = iconSp->getPositionY() - (ICON_WIDTH / 2);
				rect.size = size;
				if(rect.containsPoint(*pos))
				{
					return iconSp;
				}
			}
		}
	}
	return NULL;
}