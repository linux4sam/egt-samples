/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "hooman.h"
#include <Box2D/Box2D.h>
#include <cairo.h>
#include <egt/ui>
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

static cairo_t* createCairo(cairo_t* cr, double width, double height)
{
    double x1, x2, y1, y2 ;
    cairo_matrix_t matrix ;
    double scale, xs, ys ;
    double ox, oy ;

    cairo_clip_extents(cr, &x1, &y1, &x2, &y2) ;

    xs = (x2 - y1) / width ;
    ys = (y2 - y1) / height ;

    scale = xs > ys ? ys : xs ;
    ox = (((x2 - x1) / scale) - width) / 2 ;
    oy = (((y2 - y1) / scale) - height) / 2 ;

    cairo_matrix_init_scale(&matrix, scale, scale) ;
    cairo_matrix_translate(&matrix, ox, oy) ;
    cairo_set_matrix(cr, &matrix) ;

    cairo_set_line_width(cr, 1.0 / scale) ;

    cairo_select_font_face(cr, "Lato",
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_BOLD);

    cairo_set_font_size(cr, 0.65);

    return cr ;
}

struct Box2DWindow : public Window
{
    Box2DWindow()
    {
        set_boxtype(Theme::boxtype::none);

        auto cr = screen()->context().get();

        height = 2.5 ;
        width = 1.5 * height ;
        xTranslation = 0 ;

        createCairo(cr, width, height) ;
        world = createWorld(width, height) ;

        cairo_matrix_init_scale(&matrix, 1, -1) ;
        cairo_matrix_translate(&matrix, 0, -height) ;

        cairo_transform(cr, &matrix) ;
    }

    virtual void draw(Painter& painter, const Rect&)
    {
        auto  cr = painter.context().get();

        while (hoomans.size() < 1)
        {
            hoomans.push_back(new Hooman(*world)) ;
        }

        for (auto i = hoomans.begin() ;
             i != hoomans.end() ;
             ++i)
        {
            (*i)->render_to_cairo(cr, true) ;
        }

        world->Step((1.0 / 25), 8, 8) ;

        for (auto i = hoomans.begin();
             i != hoomans.end();)
        {
            if ((*i)->isAlive())
            {
                (*i)->render_to_cairo(cr) ;

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

    b2World* world ;
    cairo_matrix_t matrix ;
    std::vector<Hooman*> hoomans ;
    double width, height ;
    double xTranslation ;
};

int main(int argc, const char** argv)
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
