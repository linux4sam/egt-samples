/*
 * Ball.cpp
 *
 *  Created on: May 13, 2019
 *      Author: Microchip
 */

#include <Ball.h>
#include <MainWindow.h>
#include <cstdlib>

using namespace std;
using namespace egt;

static vector<string> image_names =
{
	"file:ball1.png",
	"file:ball2.png",
	"file:ball3.png"
};

Ball::Ball(MainWindow& window, const Point& point) :
	RotateImageWidget(),
	m_world(window.world()),
	m_window(window),
	m_createTime(std::chrono::steady_clock::now()),
	m_alive(true)
{
	int ball_size = std::rand() % image_names.size();
	auto image = Image(image_names[ball_size].c_str());

	this->image(image);

	resize(m_shapeSize);
	move_to_center(point);

	auto radius = m_shapeSize.width() / 2;
	auto position = m_window.egt2world(point);

	m_body = createElement(to_meter(radius), position);
}

Ball::~Ball()
{
	m_world.DestroyBody(m_body);
}

void Ball::update()
{
	b2Vec2 position = m_body->GetPosition();
	float32 angle = m_body->GetAngle();

	Point p = m_window.world2egt(position);

	move_to_center(p);
	this->angle(-angle);

	auto end_time = std::chrono::steady_clock::now();

	// check if the lifetime has expired
	auto lifetime = std::chrono::duration_cast<std::chrono::seconds>(end_time - m_createTime).count();
	if (lifetime > 30)
	{
		m_alive = false;
	}
}

b2Body* Ball::createElement(const float32 radius, const b2Vec2& position)
{
	b2BodyDef prototypeBodyDef;
	prototypeBodyDef.type = b2_dynamicBody;
	prototypeBodyDef.linearDamping = 0;
	prototypeBodyDef.angularDamping = 0;

	prototypeBodyDef.allowSleep = true;
	prototypeBodyDef.awake = true;
	prototypeBodyDef.active = true;
	prototypeBodyDef.position = position;

	auto result = m_world.CreateBody(&prototypeBodyDef);

	b2CircleShape circle;
	circle.m_p.Set(0.0, 0.0);;
	circle.m_radius = radius;

	b2FixtureDef prototypeFixtureDef;
	prototypeFixtureDef.restitution = 0.45;
	prototypeFixtureDef.friction = 0.25;
	prototypeFixtureDef.density = 50;
	prototypeFixtureDef.shape = &circle;
	result->CreateFixture(&prototypeFixtureDef);
	return result;
}
