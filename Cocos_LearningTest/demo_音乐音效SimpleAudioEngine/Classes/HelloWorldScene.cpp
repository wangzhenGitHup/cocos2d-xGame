#include "HelloWorldScene.h"

USING_NS_CC;


//��Ч�ļ�
//Androidƽֻ̨֧��OGG����Ч��ʽ
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#define EFFECT_FILE        "music/effect2.ogg"
#elif( CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
	#define EFFECT_FILE        "music/effect1.raw"
#else
	#define EFFECT_FILE        "music/effect1.wav"
#endif

//�����ļ�
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define MUSIC_FILE        "music/music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )
#define MUSIC_FILE        "music/background.ogg"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#define MUSIC_FILE        "music/background.wav"
#else
#define MUSIC_FILE        "music/background.mp3"
#endif



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

//Ԥ����������Ч
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_FILE);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(EFFECT_FILE);


//��������������Ч�Ĳ˵���ť
	std::string testItems[] = {
		"play background music",
		"stop background music",
		"pause background music",
		"resume background music",
		"rewind background music",
		"is background music playing",

		"play effect",
		"play effect repeatly",
		"stop effect",
		"pause effect",
		"resume effect",
		"pause all effects",
		"resume all effects",
		"stop all effects",
		"unload effect",

		"add background music volume",
		"sub background music volume",
		"add effects volume",
		"sub effects volume"
	};

//�����˵�
	CCMenu* pMenu = CCMenu::create();
	pMenu->setContentSize(CCSizeMake(480,1000));

	for (int i = 0; i < 19; ++i)
	{
		CCLabelTTF* label = CCLabelTTF::create(testItems[i].c_str(), "Arial", 24);
		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(HelloWorld::menuCallback));
		pMenuItem->setPosition( ccp(mysize.width/2, 1000 - (i+1)*50 ) );
		pMenu->addChild(pMenuItem, 0, i);
	}


//���˵���Ϊ���������������ͼ��
	CCScrollView* scrollView = CCScrollView::create(CCSizeMake(480, 320), pMenu);
	scrollView->setDirection(kCCScrollViewDirectionVertical);
	scrollView->setPosition(CCPointZero);
	pMenu->setPosition( ccp(0, 320-1000) );
	this->addChild(scrollView);


	return true;
}


void HelloWorld::menuCallback(CCObject* sender)
{

//��ȡ�˵���ť���
	int idx = ((CCMenuItem*)sender)->getTag();


	switch(idx)
	{
//���ֿ���
	case 0: SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE, true); break; //�������֣�ѭ��
	case 1: SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();                 break; //ֹͣ����
	case 2: SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();                break; //��ͣ����
	case 3: SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();               break; //�ָ�����
	case 4: SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();               break; //�ز�����
	case 5:
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())                   //�Ƿ����ڲ��ű�������
		{
			CCLOG("background music is playing");
		}
		else
		{
			CCLOG("background music is not playing");
		}
		break;

//��Ч����
	case 6: m_soundID = SimpleAudioEngine::sharedEngine()->playEffect(EFFECT_FILE);        break; //������Ч����ѭ��
	case 7: m_soundID = SimpleAudioEngine::sharedEngine()->playEffect(EFFECT_FILE, true);  break; //������Ч��ѭ��
	case 8: SimpleAudioEngine::sharedEngine()->stopEffect(m_soundID);                      break; //ָֹͣ��ID����Ч
	case 9: SimpleAudioEngine::sharedEngine()->pauseEffect(m_soundID);                     break; //��ָͣ��ID����Ч
	case 10: SimpleAudioEngine::sharedEngine()->resumeEffect(m_soundID);                   break; //�ָ�ָ��ID����Ч
	case 11: SimpleAudioEngine::sharedEngine()->pauseAllEffects();                         break; //��ͣ������Ч
	case 12: SimpleAudioEngine::sharedEngine()->resumeAllEffects();                        break; //�ָ�������Ч
	case 13: SimpleAudioEngine::sharedEngine()->stopAllEffects();                          break; //ֹͣ������Ч
	case 14: SimpleAudioEngine::sharedEngine()->unloadEffect(EFFECT_FILE);                 break; //ж����Ч

//��������
	case 15:
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() + 0.1f);
		break;
	case 16:
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() - 0.1f);
		break;
	case 17:
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(SimpleAudioEngine::sharedEngine()->getEffectsVolume() + 0.1f);
		break;
	case 18:
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(SimpleAudioEngine::sharedEngine()->getEffectsVolume() - 0.1f);
		break;
	}

}