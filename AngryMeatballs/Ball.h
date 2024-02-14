/*
 * Ball.h
 *
 *  Created on: May 13, 2019
 *      Author: Microchip
 */

#ifndef BALL_H_
#define BALL_H_

#include <Box2D/Box2D.h>
#include <RotateImageWidget.h>
#include <chrono>
#include <egt/ui>

class MainWindow;

class Ball: public RotateImageWidget
{
public:
	Ball(MainWindow& window, const egt::Point& point);

	std::unique_ptr<Widget> clone()
	{
		return std::unique_ptr<Widget>();
	}

	void update();

	bool is_alive()
	{
		return m_alive;
	}

	void toss()
	{
		m_body->SetLinearVelocity(b2Vec2(5, 2));
		m_body->SetAngularVelocity(-4.0);
	}

	virtual ~Ball();

protected:
	b2World& m_world;
	MainWindow& m_window;
	b2Body* createElement(const float radius, const b2Vec2& position);

private:
	b2Body* m_body;
	std::chrono::steady_clock::time_point m_createTime;
	bool m_alive;
};


#endif /* BALL_H_ */
