/*
 * MainWindow.h
 *
 *  Created on: May 13, 2019
 *      Author: Microchip
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <Box2D/Box2D.h>
#include "Ball.h"
#include <chrono>
#include <egt/ui>
#include <random>
#include <vector>

class MainWindow: public egt::TopWindow
{
public:
	MainWindow();

	void handle(egt::Event& event) override;
	void update();

	virtual ~MainWindow()
	{
		// The balls are added as children, but to destruct a Ball,
		// we need m_world around.  So, explicitly cleanup the balls
		// here (instead of in egt::Frame by default) where we still
		// have m_world around.
		for(auto& i : m_objects)
			i->detach();
		m_objects.clear();
	}

protected:
	std::unique_ptr<b2World> m_world;
	std::vector<std::shared_ptr<Ball>> m_objects;

};

#endif /* MAINWINDOW_H_ */
