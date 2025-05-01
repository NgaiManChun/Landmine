#include <stdio.h>
#include <conio.h>
#include "menu.h"


MENU_OPTION_VALUE menu(MENU_OPTION menu_options[], int options_num, int display_at_y) {

	int cursor = 0;
	int selected = 0;

	do {
		printf("\033[%d;0H", display_at_y);
		for (int i = 0; i < options_num; i++) {
			if (cursor == i) {
				printf("→");
			}
			else {
				printf("　");
			}
			printf("%s\n", menu_options[i].label);
		}
		printf("\nW：上へ　S：下へ　J：決定");

		char input = _getch();
		if (input == 'w') {
			if (--cursor < 0) {
				cursor = options_num - 1;
			}
		}
		else if (input == 's') {
			cursor = ++cursor % options_num;
		}
		else if (input == 'j') {
			selected = 1;
		}

	} while (!selected);

	return menu_options[cursor].value;
}