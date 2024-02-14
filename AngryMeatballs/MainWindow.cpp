/*
 * MainWindow.cpp
 *
 *  Created on: May 13, 2019
 *      Author: Microchip
 */

#include <MainWindow.h>
#include <iomanip>
#include <iostream>

using namespace egt;
using namespace std;

static unique_ptr<b2World> create_world(double width, double height)
{
	auto gravity = -9.81;
	auto world = std::make_unique<b2World>(b2Vec2(0, gravity));

	// create a 'box' to hold the objects
	b2Vec2 vs[4];
	vs[0].Set(0, height);
	vs[1].Set(0, 0);
	vs[2].Set(width, 0);
	vs[3].Set(width, height);
	b2ChainShape chain;
	chain.CreateChain(vs, 4);

	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(0.0f, 0.0f);
	groundBodyDef.linearDamping = 0.0f;
	groundBodyDef.angularDamping = 0.0f;

	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &chain;
	groundFixtureDef.friction = 0.05;
	groundFixtureDef.restitution = 0.1;

	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	groundBody->CreateFixture(&groundFixtureDef);

	cout << "Created world of size " << width << "," << height << endl;

	return world;
}

MainWindow::MainWindow()
{
	background(Image("file:background.png"));
	m_ground_ratio = (480. - 55.) / 480.;

	color(Palette::ColorId::bg, Palette::black);
	auto label = make_shared<Label>("Box2D Physics", AlignFlag::center_horizontal | AlignFlag::center_vertical);
        label->font(Font(40));
	label->color(Palette::ColorId::text, Palette::black);
        label->color(Palette::ColorId::bg, Palette::transparent);
	add(label);
	egt::align(label, egt::AlignFlag::top | egt::AlignFlag::center_horizontal);

	m_world = create_world(to_meter(size().width()), to_meter(m_ground_ratio * size().height()));

	cout << "MainWindow size " << size() << endl;
}


void MainWindow::handle(Event& event)
{
	TopWindow::handle(event);

	switch (event.id())
	{
		case EventId::pointer_hold:
		{
			auto mouse = display_to_local(event.pointer().point);
			auto shape = make_shared<Ball>(*this, mouse);

			cout << "Created" << shape->box() << endl;
			add(shape);
			m_objects.push_back(shape);

			shape->toss();
			break;
		}
		case EventId::pointer_click:
		{
			auto mouse = display_to_local(event.pointer().point);
			auto shape = make_shared<Ball>(*this, mouse);

			cout << "Created" << shape->box() << endl;
			add(shape);
			m_objects.push_back(shape);
			break;
		}
		case EventId::pointer_dblclick:
		{
			for(auto i = m_objects.begin(); i != m_objects.end(); ++i)
				(*i)->detach();
			m_objects.clear();
			damage();
			break;
		}
		default:
			break;
	}
}

void MainWindow::update()
{
	// perform the Box2D simulation
	m_world->Step(0.03f, 6, 5);

	for (auto i = m_objects.begin(); i != m_objects.end();)
	{
		(*i)->update();

		if ((*i)->is_alive() == false)
		{
			cout << "Destroyed" << (*i)->box() << endl;
			(*i)->detach();
			i = m_objects.erase(i);
		}
		else
		{
			++i;
		}
	}
}

egt::Point MainWindow::ground() const
{
	return egt::Point(0, m_ground_ratio * height());
}

egt::Point MainWindow::world2egt(const b2Vec2& position) const
{
	auto p = egt::Point(from_meter(position.x), from_meter(-position.y));
	return p + ground();
}

b2Vec2 MainWindow::egt2world(const egt::Point& point) const
{
	auto p = point - ground();
	return b2Vec2(to_meter(p.x()), to_meter(-p.y()));
}
