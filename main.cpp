#include "Application.h"

int main(int argc, char* argv[])
{

	Application::getInstance().init();
	Application::getInstance().loadResources();

	if (Application::getInstance().isRunning())
		Application::getInstance().handleApplication();
	else
		Application::getInstance().free();

	return EXIT_SUCCESS;
}