/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "hooman.h"
#include <Box2D/Box2D.h>
#include <egt/ui>
#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

using namespace egt;
using namespace std;

static b2World* createWorld(double width, double height)
{
    b2World* myWorld ;

    b2Vec2 vs[3] ;
    b2ChainShape chain;
    b2BodyDef groundBodyDef ;
    b2FixtureDef groundFixtureDef;
    b2Body* groundBody ;

    myWorld = new b2World(b2Vec2(0, -9.81)) ;

    vs[0].Set(0, height) ;
    vs[1].Set(0, 0);
    vs[2].Set(1000 * width, 0);
    chain.CreateChain(vs, 3);

    groundBodyDef.position.Set(0.0f, 0.0f) ;
    groundBodyDef.linearDamping = 0;
    groundBodyDef.angularDamping = 0;
    groundFixtureDef.shape = &chain ;
    groundFixtureDef.friction = 0.01;
    groundFixtureDef.restitution = 0.1;
    groundBody = myWorld->CreateBody(&groundBodyDef);
    groundBody->CreateFixture(&groundFixtureDef) ;

    return myWorld ;
}

struct Box2DWindow : public Window
{
    Box2DWindow()
    {
        fill_flags().clear();

        double height = 2.5 ;
        double width = 1.5 * height ;

        setupEGT(width, height) ;
        world = createWorld(width, height) ;
    }

    virtual void draw(Painter& painter, const Rect&)
    {
        while (hoomans.size() < 1)
        {
            hoomans.push_back(new Hooman(*world)) ;
        }

        for (auto i = hoomans.begin() ;
             i != hoomans.end() ;
             ++i)
        {
            (*i)->render(painter, true) ;
        }

        world->Step((1.0 / 25), 8, 8) ;

        for (auto i = hoomans.begin();
             i != hoomans.end();)
        {
            if ((*i)->isAlive())
            {
                (*i)->render(painter) ;

                if (drand48() < 0.1)
                {
                    size_t n ;
                    n = (*i)->variableCount() ;
                    (*i)->setVariable(drand48()*n, 5 * drand48() - 2.5) ;
                }

                i++;
            }
            else
            {
                delete *i ;
                i = hoomans.erase(i) ;
            }
        }
    }

    virtual ~Box2DWindow()
    {
        for (auto i = hoomans.begin() ;
             i != hoomans.end() ;
             ++i)
        {
            delete *i ;
        }

        delete world ;
    }

    void setupEGT(float width, float height)
    {
        auto& painter = screen()->painter();

        auto w = static_cast<float>(this->width());
        auto h = static_cast<float>(this->height());

        auto xs = w / width;
        auto ys = h / height;

        auto scale = std::min(xs, ys);
        auto ox = ((w / scale) - width) / 2;
        auto oy = ((h / scale) - height) / 2;

        painter.scale(scale, scale);
        painter.translate(egt::PointF(ox, oy));

        painter.line_width(1.0 / scale);

        painter.set(egt::Font("Lato", 0.65, egt::Font::Weight::bold));

        painter.scale(1, -1);
        painter.translate(egt::PointF(0, -height));
    }

    b2World* world ;
    std::vector<Hooman*> hoomans ;
};

int main(int argc, char** argv)
{
    Application app(argc, argv);

    Box2DWindow win;
    win.show();

    PeriodicTimer timer(std::chrono::milliseconds(30));
    timer.on_timeout([&win]()
    {
        win.damage();
    });
    timer.start();

    return app.run();
}
