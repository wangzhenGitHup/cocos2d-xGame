#ifndef __com__wangzhen__cleanspacegame__global__h__
#define __com__wangzhen__cleanspacegame__global__h__

#define ICON_WIDTH 48
#define BOADER_WIDTH 2
#define ROWS 8
#define COLS 8
#define TOTAL_ICON 6

#define SOUND_KEY "sound_key"
#define MUSIC_KEY "music_key"

typedef enum
{
	DISPLAY_MODE_NORMAL = 0,
	DISPLAY_MODE_HORIZONTAL,
	DISPLAY_MODE_VERTICAL
}DisplayMode;

typedef enum
{
	SCORE_TAG = 100,
	SCORE_GAME_TAG = 10,
	TIME_TAG = 11,
}TagType;

typedef enum
{
	UP = 0,
	LEFT,
	RIGHT,
	DOWN
}GameDirection;

static const char* iconNormal[TOTAL_ICON] = 
{
	"icon1.png",
	"icon2.png",
	"icon3.png",
	"icon4.png",
	"icon5.png",
	"icon6.png"
};

static const char* iconVertical[TOTAL_ICON] = 
{
	"icon1_z.png",
	"icon2_z.png",
	"icon3_z.png",
	"icon4_z.png",
	"icon5_z.png",
	"icon6_z.png"
};

static const char* iconHorizontal[TOTAL_ICON] = 
{
	"icon1_h.png",
	"icon2_h.png",
	"icon3_h.png",
	"icon4_h.png",
	"icon5_h.png",
	"icon6_h.png"
};

#endif