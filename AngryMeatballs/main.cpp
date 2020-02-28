/*
 * RotateImageWidget.cpp
 *
 *  Created on: May 15, 2019
 *      Author: Microchip
 */

#include "MainWindow.h"
#include <egt/ui>

using namespace egt;

int main(int argc, char **argv) {
	Application app(argc, argv, "AngryMeatballs");
	egt::add_search_path(ASSETDIR);

	MainWindow win;
	win.show();

	PeriodicTimer animatetimer(std::chrono::milliseconds(30));
	animatetimer.on_timeout([&win]()
	{
		win.update();
	});
	animatetimer.start();

	return app.run();
}
