#include "main_game.h"

#ifndef _TITLE_H
#define _TITLE_H

typedef int TITLE_MENU_OPTION;

#define TITLE_MENU_OPTION_BEGINNER 1
#define TITLE_MENU_OPTION_INTERMEDIATE 2
#define TITLE_MENU_OPTION_ADVANCED 3
#define TITLE_MENU_OPTION_END 4

TITLE_MENU_OPTION title();
MAIN_GAME_MODE getMainGameModeByOption(TITLE_MENU_OPTION menu_option);

#endif