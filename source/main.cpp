/*
	Author: AT51A093-05-魏文俊（ガイ　マンチュン）
	2023/11/26	「＠」マークの代わりに、色改変でカーソルとして表示に変更
				それに伴ってカーソル常時表示に変更、
				main_game.cpp内のdisplay_cursor変数を削除
	2023/11/25	ver1完成

*/

#include <stdio.h>
#include <stdlib.h>
#include "title.h"


#define MAIN_STATE_TITLE 1
#define MAIN_STATE_MAIN_GAME 2
#define MAIN_STATE_END 3

int main() {
	// 画面制御開始
	system("cls");
	// 画面全消し
	printf("\033[2J");
	// カーソル非表示
	printf("\033[?25l");


	int state = MAIN_STATE_TITLE;
	TITLE_MENU_OPTION menu_option;

	while (state != MAIN_STATE_END) {
		if (state == MAIN_STATE_TITLE) {
			menu_option = title();
			if (menu_option == TITLE_MENU_OPTION_END) {
				state = MAIN_STATE_END;
			}
			else {
				state = MAIN_STATE_MAIN_GAME;
			}
		}
		else if (state == MAIN_STATE_MAIN_GAME) {
			MAIN_GAME_MODE mode = getMainGameModeByOption(menu_option);
			MAIN_GAME_RESULT result = main_game(mode);
			if (result == MAIN_GAME_RESULT_TITLE) {
				state = MAIN_STATE_TITLE;
			}
			else if (result == MAIN_GAME_RESULT_END) {
				state = MAIN_STATE_END;
			}
		}
	}
	return 0;

}