#ifndef  __com__wangzhen__fightplane__global__h__
#define __com__wangzhen__fightplane__global__h__

typedef enum
{
	AIR_TAG = 0,
};

typedef enum
{
	ENEMYONE_MAXLIFE = 1,
	ENEMYSECOND_MAXLIFE = 3,
	ENEMYTHIRD_MAXLIFE = 7
};

typedef enum
{
	EASY = 0,
	MIDDLE,
	HARD
};

typedef enum
{
	ENEMYONE = 0,
	ENEMYSECOND,
	ENEMYTHIRD
}EnemyType;

typedef enum
{
	MIDDLE_SCORE = 100000,
	HARD_SCORE = 200000,
	MAX_SCORE = 10000000,
	ENEMYONE_SCORE = 1000,
	ENEMYSECOND_SCORE = 6000,
	ENEMYTHIRD_SCORE = 10000
}Score;

typedef enum
{
	NORMAL_BULLET = 0,
	MULTI_BULLET
}BulletType;

typedef enum
{
	BOMB_MENU = 1,
	BOMB_LABEL
}BombType;

const int MAX_BIGBOOM_COUNT = 1000000;
#endif