#include <stdio.h>
#include "title.h"
#include "main_game.h"
#include "menu.h"


TITLE_MENU_OPTION title() {
	// 画面全消し
	printf("\033[2J");

	printf("\033[0;0H地雷にフラッグ立てる系ゲーム\n");

	printf(
		"\033[31m\033[40m　　　　　　　　　　　　　　　　　　　　　　　　\033[30m\033[47m　　　　　　　　■  ■　　　　　　　　　　　　　　　　　　　　\n"
		"\033[31m\033[40m　■　　　　　■　　　　　■■■■■■■■■　　\033[30m\033[47m　　　■　　　　　■　■　　　　　　　　　　　　　　　　　　　\n"
		"\033[31m\033[40m　■　　　■　■　　　　■■■■■■■■■■■　\033[30m\033[47m　　　■　　　　　　　　　　　　　　　　　　　　■■　　　　　\n"
		"\033[31m\033[40m　■　　　■　■　■　　■　　　　■　　　　■　\033[30m\033[47m　　■■■■■■■■■　　　　　　　　　　　　　■　　　　　　\n"
		"\033[31m\033[40m■■■■　■■■■■■　■　■■　■　■■　■　\033[30m\033[47m　　■　　　■■　　　　　　　　　　　　　　　　■　　　　　　\n"
		"\033[31m\033[40m　■　　■■　■　　■　　　■■　■　■■　　　\033[30m\033[47m　■　　　　■　　　　　　　　　　　　　　　　■■　　■　　　\n"
		"\033[31m\033[40m　■　　　■　■　　■　　　　　　　　　　　　　\033[30m\033[47m■■　　　　■　　　　　■■■■■■■　　　　■　　　■　　　\n"
		"\033[31m\033[40m　■　　　■　　　　　　　■■■■■■■■■　　\033[30m\033[47m　　　　　　■　　　　　　　　　　　　　　　　■　　　　■　　\n"
		"\033[31m\033[40m　■　　　■　　　■■　　■　　　■　　　■　　\033[30m\033[47m　　　　　■　　　　　　　　　　　　　　　　■　　　　■■■　\n"
		"\033[31m\033[40m　■■■　■　　　　■　　■■■■■■■■■　　\033[30m\033[47m　　　　■■　　　　　　　　　　　　　　■■■■■■■■　■■\n"
		"\033[31m\033[40m■■　　　■　　　　■　　■　　　■　　　■　　\033[30m\033[47m　　　■■　　　　　　　　　　　　　　　　　　　　　　　　　　\n"
		"\033[31m\033[40m　　　　　■■■■■■　　■■■■■■■■■　　\033[30m\033[47m　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\033[0m\n"
	);


	MENU_OPTION menu_options[] = {
		{TITLE_MENU_OPTION_BEGINNER, "初級（9×9マス、地雷10個）"},
		{TITLE_MENU_OPTION_INTERMEDIATE, "中級（16×16マス、地雷40個）"},
		{TITLE_MENU_OPTION_ADVANCED, "上級（30×16マス、地雷99個）"},
		{TITLE_MENU_OPTION_END,  "終了"}
	};

	return menu(menu_options, sizeof(menu_options) / sizeof(MENU_OPTION), 14);
}

MAIN_GAME_MODE getMainGameModeByOption(TITLE_MENU_OPTION menu_option) {
	switch (menu_option)
	{
	case TITLE_MENU_OPTION_BEGINNER:
		return MAIN_GAME_MODE_BEGINNER;
	case TITLE_MENU_OPTION_INTERMEDIATE:
		return MAIN_GAME_MODE_INTERMEDIATE;
	case TITLE_MENU_OPTION_ADVANCED:
		return MAIN_GAME_MODE_ADVANCED;
	}
	return MAIN_GAME_MODE_ADVANCED;
}