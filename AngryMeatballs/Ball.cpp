/*
 * Ball.cpp
 *
 *  Created on: May 13, 2019
 *      Author: Microchip
 */

#include <Ball.h>
#include <random>

using namespace std;
using namespace egt;

static vector<string> image_names =
{
	"ball1.png",
	"ball2.png",
	"ball3.png"
};

Ball::Ball(b2World& world, const Point& point) :
	RotateImageWidget(),
	m_world(world),
	m_createTime(std::chrono::steady_clock::now()),
	m_alive(true)
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(0, image_names.size() - 1);

	int ball_size = uniform_dist(e1);
	auto image = Image(image_names[ball_size].c_str());

	this->image(image);

	resize(m_shapeSize);
	move_to_center(point);

	auto radius = m_shapeSize.width() / 2;
	auto x = to_meter(point.x());
	auto y = to_meter(480 - 55) - to_meter(point.y());

	m_body = createElement(to_meter(radius), b2Vec2(x, y));
}

Ball::~Ball()
{
	m_world.DestroyBody(m_body);
}

void Ball::update()
{
	b2Vec2 position = m_body->GetPosition();
	float32 angle = m_body->GetAngle();

	double x = from_meter(position(0));
	double y = from_meter(position(1));
	Point p(x, 480 - 55 - y);

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
