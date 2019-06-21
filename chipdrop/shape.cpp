/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "shape.h"
#include <iostream>
#include <random>

using namespace std;

Shape::Shape(cpSpace* space, const Point& point)
    : RotateRectangleWidget(Color::rgbaf(1. * drand48(),
                            1. * drand48(),
                            1. * drand48(),
                            1.0)),
      m_space(space)
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

    auto x = to_meter(box().x);
    auto y = to_meter(480) - to_meter(box().y) - to_meter(superrect.height) * 0.5;

    m_body = createBoxElement(cpv(to_meter(width), to_meter(height)),
                              cpv(x, y));
}

Shape::~Shape()
{
    //m_world.DestroyBody(m_body);
}

cpBody* Shape::createBoxElement(const cpVect& size, const cpVect& position)
{
    auto mass = 1;
    cpBody* body = cpSpaceAddBody(m_space, cpBodyNew(mass, cpMomentForBox(mass, size.x, size.y)));
    cpBodySetPosition(body, position);

    cpShape* shape = cpSpaceAddShape(m_space, cpBoxShapeNew(body, size.x, size.y, 0.0));
    cpShapeSetElasticity(shape, 0.5f);
    cpShapeSetFriction(shape, 0.7f);
    cpShapeSetDensity(shape, 100);

    return body;
}

void Shape::update()
{
    auto pos = cpBodyGetPosition(m_body);
    auto angle = cpBodyGetAngle(m_body);

    double x = from_meter(pos.x);
    double y = from_meter(pos.y);
    Point p(x, 480 - y - height() * .5);

    move(p);
    set_angle(-angle);
}
