#include "menu.h"

int main() {
	srand(time(NULL));
	game game(1200, 1000, "Hotline BSTU");
	menu menu;
	menu.start(&game);
	return 0;
}