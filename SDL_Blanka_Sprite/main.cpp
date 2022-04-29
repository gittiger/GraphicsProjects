#include <iostream>
#include "RenderingEngine.h"

int main(int, char**) {

	RenderingEngine *mainEngine = RenderingEngine::getInstance();
	mainEngine->startEngine();

	delete mainEngine;
	return 0;
}