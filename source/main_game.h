#ifndef _MAIN_GAME_H
#define _MAIN_GAME_H

#define MAP_DISPLAY_AT_Y 5

typedef int MAIN_GAME_MODE;

#define MAIN_GAME_MODE_BEGINNER 1
#define MAIN_GAME_MODE_INTERMEDIATE 2
#define MAIN_GAME_MODE_ADVANCED 3

typedef int MAIN_GAME_RESULT;

#define MAIN_GAME_RESULT_NEWGAME 1
#define MAIN_GAME_RESULT_TITLE 2
#define MAIN_GAME_RESULT_END 3

// èâãâ
#define MAP_WIDTH_BEGINNER 9
#define MAP_HEIGHT_BEGINNER 9
#define MAP_MINE_NUM_BEGINNER 10

// íÜãâ
#define MAP_WIDTH_INTERMEDIAT 16
#define MAP_HEIGHT_INTERMEDIAT 16
#define MAP_MINE_NUM_INTERMEDIAT 40

// è„ãâ
#define MAP_WIDTH_ADVANCED 30
#define MAP_HEIGHT_ADVANCED 16
#define MAP_MINE_NUM_ADVANCED 99

typedef int GAME_STATE;

#define GAME_STATE_CONTINUE 1
#define GAME_STATE_GAMEOVER 2
#define GAME_STATE_WIN 3

typedef int MASU_STATE;

#define MASU_STATE_CLOSE 0
#define MASU_STATE_OPEN 1
#define MASU_STATE_FLAG 2
#define MASU_STATE_WRONG_FLAG 3

typedef struct _Masu {
	int isMine;
	MASU_STATE state;
	int position;
} Masu;

MAIN_GAME_RESULT main_game(MAIN_GAME_MODE mode);
Masu* initMap(int map_width, int map_height, int total_mine_num);
int countNearMine(Masu* map, int map_width, int map_height, int x, int y);
void displayMap(Masu* map, int map_width, int map_height, int cursor_x, int cursor_y);
void displayStatus(int remain_mine_num);
int openMasu(Masu* map, int map_width, int map_height, int x, int y);
void sortMasu(Masu* map, int size);

#endif