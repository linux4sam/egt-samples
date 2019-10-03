/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "shape.h"
#include <Box2D/Box2D.h>
#include <cairo.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <egt/detail/meta.h>
#include <egt/ui>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <vector>

using namespace egt;
using namespace std;

static unique_ptr<b2World> create_world(double width, double height)
{
    auto gravity = -9.81;
    auto world = detail::make_unique<b2World>(b2Vec2(0, gravity));

    b2Vec2 vs[3];
    vs[0].Set(0, height) ;
    vs[1].Set(0, 0);
    vs[2].Set(width, 0);
    b2ChainShape chain;
    chain.CreateChain(vs, 3);

    b2BodyDef groundBodyDef ;
    groundBodyDef.type = b2_staticBody ;
    groundBodyDef.position.Set(0.0f, 0.0f) ;
    groundBodyDef.linearDamping = 0;
    groundBodyDef.angularDamping = 0;

    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &chain ;
    groundFixtureDef.friction = 0.01;
    groundFixtureDef.restitution = 0.1;

    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    groundBody->CreateFixture(&groundFixtureDef) ;

    cout << "created world of size " << width << "," << height << endl;

    return world;
}

struct Box2DWindow : public TopWindow
{
    Box2DWindow()
    {
        auto label = make_shared<Label>("EGT Box2D Physics",
                                        alignmask::center);
        auto font = label->font();
        font.set_size(40);
        label->set_font(font);
        add(egt::center(label));

        m_world = create_world(to_meter(size().width()), to_meter(size().height())) ;
    }

    void handle(Event& event) override
    {
        TopWindow::handle(event);

        switch (event.id())
        {
        case eventid::pointer_hold:
        {
            auto mouse = display_to_local(event.pointer().point);
            auto shape = make_shared<Shape>(*m_world, mouse);

            cout << "created " << shape->box() << endl;
            add(shape);
            m_boxes.push_back(shape);

            shape->toss();
            break;
        }
        case eventid::pointer_click:
        {
            auto mouse = display_to_local(event.pointer().point);
            auto shape = make_shared<Shape>(*m_world, mouse);

            cout << "created " << shape->box() << endl;
            add(shape);
            m_boxes.push_back(shape);
            break;
        }
        case eventid::pointer_dblclick:
            for (auto i = m_boxes.begin(); i != m_boxes.end(); ++i)
                (*i)->detach();
            m_boxes.clear();
            damage();
            break;
        default:
            break;
        }
    }

    void update()
    {
        detail::code_timer(false, "step: ", [&]()
        {
            m_world->Step((1.0 / 30), 10, 10);
        });

        for (auto i = m_boxes.begin(); i != m_boxes.end();)
        {
            (*i)->update();

            bool visible = box().intersect((*i)->box());
            if (!visible)
            {
                (*i)->detach();
                i = m_boxes.erase(i);
            }
            else
                ++i;
        }
    }

    virtual ~Box2DWindow()
    {
        // The shapes are added as children, but to destruct a Shape,
        // we need m_world around.  So, explicitly cleanup the shapes
        // here (instead of in egt::Frame by default) where we still
        // have m_world around.
        for(auto& i : m_boxes)
            i->detach();
        m_boxes.clear();
    }

protected:

    unique_ptr<b2World> m_world ;
    vector<shared_ptr<Shape>> m_boxes;
};

int main(int argc, const char** argv)
{
    Application app(argc, argv, "drop");

    Box2DWindow win;

    PeriodicTimer timer(std::chrono::milliseconds(30));
    timer.on_timeout([&win]()
    {
        win.update();
    });
    timer.start();

    win.show();

    return app.run();
}
