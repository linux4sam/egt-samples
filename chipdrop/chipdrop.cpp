/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "shape.h"
#include "chipmunk/chipmunk.h"
#include <cairo.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <egt/ui>
#include <iostream>
#include <map>
#include <unistd.h>
#include <vector>

using namespace egt;
using namespace std;

static cpSpace* create_world(double width, double height)
{
    auto gravity = cpv(0, -100);
    cpSpace* space = cpSpaceNew();
    cpSpaceSetGravity(space, gravity);
    cpSpaceSetSleepTimeThreshold(space, .5);

    cpBody* b = cpSpaceGetStaticBody(space);

    cpShape* ground = cpSegmentShapeNew(b,
                                        cpv(-width, 0),
                                        cpv(width, 0),
                                        0);

    cpShapeSetFriction(ground, 1);
    cpSpaceAddShape(space, ground);
    cpBodySetPosition(b, cpv(1, height));

    cout << "created world of size " << width << "," << height << endl;

    return space;
}

struct Box2DWindow : public TopWindow
{
    Box2DWindow()
        : TopWindow()
    {
        auto label = make_shared<Label>("EGT Chipmunk 2D Physics",
                                        alignmask::center);
        auto font = label->font();
        font.set_size(40);
        label->set_font(font);
        add(egt::center(label));

        m_space = create_world(to_meter(size().width()), to_meter(size().height())) ;
    }

    void handle(Event& event) override
    {
        TopWindow::handle(event);

        switch (event.id())
        {
        case eventid::pointer_hold:
        {
            auto mouse = display_to_local(event.pointer().point);
            auto shape = make_shared<Shape>(m_space, mouse);

            cout << "created " << shape->box() << endl;
            add(shape);
            m_boxes.push_back(shape);

            shape->toss();
            break;
        }
        case eventid::pointer_click:
        {
            auto mouse = display_to_local(event.pointer().point);
            auto shape = make_shared<Shape>(m_space, mouse);

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
        experimental::code_timer(true, "step: ", [&]()
        {
            cpFloat timeStep = 1.0 / 30.0;
            cpSpaceStep(m_space, timeStep);
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

    virtual ~Box2DWindow() = default;

protected:

    cpSpace* m_space;
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
