#include "game.h"

int main(void) {
	GameTetris* app = new GameTetris();
	DWORD err = app->CreateMainForm();
	if (err != NO_ERROR) {
		printf("code error: %lu\n", err);
		return 1;
	}
	app->run(40);
	delete app;
	return 0;
}