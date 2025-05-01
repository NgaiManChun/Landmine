#ifndef _MENU_H
#define _MENU_H

typedef int MENU_OPTION_VALUE;

typedef struct MENU_OPTION {
	MENU_OPTION_VALUE value;
	char label[50];
} MENU_OPTION;

MENU_OPTION_VALUE menu(MENU_OPTION menu_options[], int options_num, int display_at_y);

#endif