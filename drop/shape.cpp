/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "shape.h"
#include <iostream>
#include <random>

using namespace std;

Shape::Shape(b2World& world, const Point& point)
    : RotateRectangleWidget(Color::rgbaf(1. * drand48(),
                                         1. * drand48(),
                                         1. * drand48(),
                                         1.0)),
      m_world(world)
{
    const vector<int> widths = { 50, 25, 75 };
    const vector<int> heights = { 50, 75 };

    std::random_device r;
    std::default_random_engine e1 {r()};
    std::uniform_int_distribution<int> width_dist {0, static_cast<int>(widths.size()) - 1};
    std::uniform_int_distribution<int> height_dist {0, static_cast<int>(heights.size()) - 1};

    auto width = widths[width_dist(e1)];
    auto height = heights[height_dist(e1)];

    /*
     * EGT does not currently support widget rotation. So, handle it at the
     * widget level here in a rather rudimentary way. Create a widget box()
     * that is actually large enough to handle the area of rotating the
     * rectangle of the requested size inside of the widget itself. Save off the
     * real rectangle size to m_shapesize and use it in draw().  This way,
     * all damage rectangles work as expected, except we only draw a smaller
     * portion of the widget.
     */
    m_shapesize = Size(width, height);

    // create our "bigger" rectangle to handle any area covered by rotating our
    // real rectangle of size m_shapesize
    auto maxd = std::max(width, height);
    auto superrect = Rect(Point(), Size(maxd, maxd));
    superrect.move_to_center(point);
    superrect.grow_around_center(maxd);

    // real widget size is the big rect, center is a common point
    resize(superrect.size());
    move_to_center(superrect.center());

    auto x = to_meter(box().x());
    auto y = to_meter(480) - to_meter(box().y()) - to_meter(superrect.height()) * 0.5;

    m_body = createBoxElement(b2Vec2(to_meter(width), to_meter(height)),
                              b2Vec2(x, y));
}

Shape::~Shape()
{
    m_world.DestroyBody(m_body);
}

b2Body* Shape::createBoxElement(const b2Vec2& size, const b2Vec2& position)
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

    b2PolygonShape prototypeShape ;
    prototypeShape.SetAsBox(size(0) *.5, size(1) *.5);

    b2FixtureDef prototypeFixtureDef ;
    prototypeFixtureDef.restitution = 0.4;
    prototypeFixtureDef.friction = 0.2;
    prototypeFixtureDef.density = 50;
    prototypeFixtureDef.shape = &prototypeShape;

    result->CreateFixture(&prototypeFixtureDef);

    return result ;
}

void Shape::update()
{
    b2Vec2 position = m_body->GetPosition() ;
    float32 angle = m_body->GetAngle() ;

    double x = from_meter(position(0));
    double y = from_meter(position(1));
    Point p(x, 480 - y - height() * .5);

    move(p);
    set_angle(-angle);
}
