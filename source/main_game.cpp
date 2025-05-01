#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "main_game.h"
#include "menu.h"

static char zNum[][4] = { "０", "１", "２", "３", "４", "５", "６", "７", "８", "９" };

MAIN_GAME_RESULT main_game(MAIN_GAME_MODE mode) {
	srand((unsigned int)time(NULL));

	// 画面全消し
	printf("\033[2J");

	int map_width = 0;
	int map_height = 0;
	int total_mine_num = 0;

	// 初期化
	if (mode == MAIN_GAME_MODE_BEGINNER) {
		map_width = MAP_WIDTH_BEGINNER;
		map_height = MAP_HEIGHT_BEGINNER;
		total_mine_num = MAP_MINE_NUM_BEGINNER;
	}
	else if (mode == MAIN_GAME_MODE_INTERMEDIATE) {
		map_width = MAP_WIDTH_INTERMEDIAT;
		map_height = MAP_HEIGHT_INTERMEDIAT;
		total_mine_num = MAP_MINE_NUM_INTERMEDIAT;
	}
	else if (mode == MAIN_GAME_MODE_ADVANCED) {
		map_width = MAP_WIDTH_ADVANCED;
		map_height = MAP_HEIGHT_ADVANCED;
		total_mine_num = MAP_MINE_NUM_ADVANCED;
	}

	Masu* map = initMap(map_width, map_height, total_mine_num);

	int cursor_x = 0;
	int cursor_y = 0;
	int opened_masu_num = 0;
	int remain_mine_num = total_mine_num;
	int start_time = 0;
	int end_time = 0;
	GAME_STATE state = GAME_STATE_CONTINUE;

	displayStatus(remain_mine_num);
	displayMap(map, map_width, map_height, cursor_x, cursor_y);


	while (state == GAME_STATE_CONTINUE) {

		// 入力待ち
		int input = _getch();

		if (input == 'w') {
			cursor_y--;
		}
		else if (input == 's') {
			cursor_y++;
		}
		else if (input == 'a') {
			cursor_x--;
		}
		else if (input == 'd') {
			cursor_x++;
		}
		else if (input == 'j') {
			// マスを開く
			Masu* targetMasu = &map[cursor_x + cursor_y * map_width];
			if (targetMasu->state != MASU_STATE_FLAG && targetMasu->isMine) {
				state = GAME_STATE_GAMEOVER;
			}
			if (opened_masu_num == 0) {

				// 最初に開いたマスがマインの場合ランダムの空のマスと入れ替える
				if (state == GAME_STATE_GAMEOVER) {
					int index = rand() % (map_width * map_height);
					while (!map[index].isMine) {
						index = (index + 1) % (map_width * map_height);
					}
					map[index].isMine = 1;
					targetMasu->isMine = 0;
					state = GAME_STATE_CONTINUE;
				}

				start_time = time(NULL);
			}
			opened_masu_num += openMasu(map, map_width, map_height, cursor_x, cursor_y);
		}
		else if (input == 'k') {
			// フラッグを建てる
			Masu* targetMasu = &map[cursor_x + cursor_y * map_width];
			if (targetMasu->state == MASU_STATE_FLAG) {
				targetMasu->state = MASU_STATE_CLOSE;
				remain_mine_num++;
			}
			else if (targetMasu->state == MASU_STATE_CLOSE) {
				targetMasu->state = MASU_STATE_FLAG;
				remain_mine_num--;
			}
		}

		// マップの端を超えたら逆の端に戻す
		cursor_x %= map_width;
		cursor_y %= map_height;
		if (cursor_x < 0) {
			cursor_x += map_width;
		}
		if (cursor_y < 0) {
			cursor_y += map_height;
		}

		// 全空のマス開いたら勝ち
		if (opened_masu_num == map_width * map_height - total_mine_num) {
			end_time = time(NULL);
			remain_mine_num = 0;
			for (int i = 0; i < map_width * map_height; i++) {
				if (map[i].isMine) {
					map[i].state = MASU_STATE_FLAG;
				}
				else {
					map[i].state = MASU_STATE_OPEN;
				}
			}
			state = GAME_STATE_WIN;
		}

		// ゲームオーバーの時、全マインオープン
		if (state == GAME_STATE_GAMEOVER) {
			for (int i = 0; i < map_width * map_height; i++) {
				if (map[i].isMine && map[i].state != MASU_STATE_FLAG) {
					map[i].state = MASU_STATE_OPEN;
				}
				else if (!map[i].isMine && map[i].state == MASU_STATE_FLAG) {
					map[i].state = MASU_STATE_WRONG_FLAG;
				}
			}
		}

		// 表示
		displayStatus(remain_mine_num);
		displayMap(map, map_width, map_height, cursor_x, cursor_y);
	}

	if (map != NULL) {
		free(map);
		map = NULL;
	}

	// メニュー表示する前にボタン説明消す
	printf(
		"\033[2;0H\033[2K\n"
		"\033[2K\n"
	);

	if (state == GAME_STATE_WIN) {
		printf("\033[2;0Hクリア時間%d秒", end_time - start_time);
	}

	// メニュー選択肢
	MENU_OPTION options[] = {
		{MAIN_GAME_RESULT_NEWGAME, "新しいゲーム"},
		{MAIN_GAME_RESULT_TITLE, "タイトルに戻る"},
		{MAIN_GAME_RESULT_END, "終了"}
	};

	// マップの下1行開けてメニュー表示
	return menu(options, sizeof(options) / sizeof(MENU_OPTION), MAP_DISPLAY_AT_Y + map_height + 1);


}

Masu* initMap(int map_width, int map_height, int total_mine_num) {
	Masu* map = (Masu*)malloc(sizeof(Masu) * map_width * map_height);

	// マイン分のマスを作る、positionにランダム数を入れる
	for (int i = 0; i < total_mine_num; i++) {
		map[i] = {
			1,
			MASU_STATE_CLOSE,
			rand()
		};
	}
	// 空のマスを作る、positionにランダム数を入れる
	for (int i = total_mine_num; i < map_width * map_height; i++) {
		map[i] = {
			0,
			MASU_STATE_CLOSE,
			rand()
		};
	}

	// positionによってマスを並びなおす
	sortMasu(map, map_width * map_height);

	return map;
}

int countNearMine(Masu* map, int map_width, int map_height, int x, int y) {
	int count = 0;
	for (int offset_y = -1; offset_y < 2; offset_y++) {
		if (y + offset_y < 0 || y + offset_y >= map_height) {
			continue;
		}
		for (int offset_x = -1; offset_x < 2; offset_x++) {
			if (x + offset_x < 0 || x + offset_x >= map_width) {
				continue;
			}
			if (offset_x == 0 && offset_y == 0) {
				continue;
			}
			if (map[(x + offset_x) + (y + offset_y) * map_width].isMine) {
				count++;
			}
		}
	}
	return count;
}

// マップの表示
void displayMap(Masu* map, int map_width, int map_height, int cursor_x, int cursor_y) {
	printf("\033[%d;0H", MAP_DISPLAY_AT_Y);
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			int index = x + y * map_width;
			int isCursor = (cursor_y * map_width + cursor_x == index);

			if (map[index].state == MASU_STATE_CLOSE) {
				if (isCursor) {
					printf("\033[36m");
				}
				printf("■");
			}
			else if (map[index].state == MASU_STATE_FLAG) {
				if (isCursor) {
					printf("\033[45m");
				}
				else {
					printf("\033[41m");
				}
				printf("Ｆ");
			}
			else if (map[index].state == MASU_STATE_WRONG_FLAG) {
				printf("\033[31m×");
			}
			else if (map[index].state == MASU_STATE_OPEN) {
				if (isCursor) {
					printf("\033[30m\033[46m");
				}
				if (map[index].isMine) {
					printf("＊");
				}
				else {
					printf(zNum[
						countNearMine(map, map_width, map_height, x, y)
					]);
				}
			}
			printf("\033[0m");
		}
		printf("\n");
	}
}

void displayStatus(int remain_mine_num) {
	printf("\033[0;0H\033[2K残り地雷：%d\n", remain_mine_num);
	printf(
		"W：上へ　S：下へ　A：左へ　D：右へ　\n"
		"J：マス捲る　K：フラッグ立てる／外す\n"
		"＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝"
	);
}

// マスをオープンする関数
// 隣接マインゼロの場合、隣接マス（８方向）も同じ関数にかける
// 戻り値は捲った空のマスの数
int openMasu(Masu* map, int map_width, int map_height, int x, int y) {
	int index = x + y * map_width;

	if (map[index].state == MASU_STATE_OPEN) {
		return 0;
	}
	if (map[index].state == MASU_STATE_FLAG) {
		return 0;
	}

	map[index].state = MASU_STATE_OPEN;

	if (map[index].isMine) {
		return 0;
	};

	int count = 1;
	if (countNearMine(map, map_width, map_height, x, y) == 0) {
		for (int offset_y = -1; offset_y < 2; offset_y++) {
			if (y + offset_y < 0 || y + offset_y >= map_height) {
				continue;
			}
			for (int offset_x = -1; offset_x < 2; offset_x++) {
				if (x + offset_x < 0 || x + offset_x >= map_width) {
					continue;
				}
				if (offset_x == 0 && offset_y == 0) {
					continue;
				}
				count += openMasu(map, map_width, map_height, x + offset_x, y + offset_y);
			}
		}
	}
	return count;
}

void sortMasu(Masu* map, int size) {
	int complete = 1;
	do {
		complete = 1;
		for (int i = 0; i < size - 1; i++) {
			Masu a = map[i];
			Masu b = map[i + 1];
			if (a.position < b.position) {
				map[i] = b;
				map[i + 1] = a;
				complete = 0;
			}
		}
	} while (complete == 0);

}