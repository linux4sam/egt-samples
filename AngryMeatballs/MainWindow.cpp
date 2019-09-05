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
	auto world = make_unique<b2World>(b2Vec2(0, gravity));

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
    auto background = make_shared<ImageLabel>(Image("background.png"));
    add(background);

	set_color(Palette::ColorId::bg, Palette::black);
	auto label = make_shared<Label>("Box2D Physics", alignmask::center);
        label->set_font(Font(40));
	label->set_color(Palette::ColorId::text, Palette::black);
        label->set_color(Palette::ColorId::bg, Palette::transparent);
	add(label);
	egt::align(label, egt::alignmask::top | egt::alignmask::center);

	m_world = create_world(to_meter(size().width()), to_meter(size().height() - 55));

	cout << "MainWindow size " << size() << endl;
}


void MainWindow::handle(Event& event)
{
	TopWindow::handle(event);

	switch (event.id())
	{
		case eventid::pointer_hold:
		{
			auto mouse = display_to_local(event.pointer().point);
			auto shape = make_shared<Ball>(*m_world, mouse);

			cout << "Created" << shape->box() << endl;
			add(shape);
			m_objects.push_back(shape);

			shape->toss();
			break;
		}
		case eventid::pointer_click:
		{
			auto mouse = display_to_local(event.pointer().point);
			auto shape = make_shared<Ball>(*m_world, mouse);

			cout << "Created" << shape->box() << endl;
			add(shape);
			m_objects.push_back(shape);
			break;
		}
		case eventid::pointer_dblclick:
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
