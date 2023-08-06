#include "GameManager.h"
int main(int argc, char** args) {
	GameManager manager(640, 480, 60);
	manager.run();
	return 0;
}