/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef SHAPE_H
#define SHAPE_H

#include "chipmunk/chipmunk.h"
#include <cairo.h>
#include <egt/ui>
#include <iostream>
#include <map>

using namespace egt;
using namespace std;

inline double to_meter(double x)
{
  //return x;
    return x * .1;
}

inline double from_meter(double x)
{
  //return x;
    return x * 10.;
}

/**
 * A special widget that supports rotating a rectangle within it.
 */
class RotateRectangleWidget : public Widget
{
public:

    explicit RotateRectangleWidget(const Color& fill)
    {
	set_border(2);
	set_theme(theme());
	set_color(Palette::ColorId::bg, fill);
    }

    void set_angle(double angle)
    {
      if (detail::change_if_diff<>(m_angle, angle))
	damage();
    }

    virtual void draw(Painter& painter, const Rect&) override
    {
        auto cr = painter.context().get();
        cairo_translate(cr, center().x(), center().y());
        cairo_rotate(cr, m_angle);
        cairo_translate(cr, -center().x(), -center().y());

	Rect drawbox(Point(), m_shapesize);
	drawbox.move_to_center(center());

	theme().draw_box(painter,
			 Theme::boxtype::blank | Theme::boxtype::solid,
			 drawbox,
			 color(Palette::ColorId::border),
			 color(Palette::ColorId::bg),
			 border(),
			 margin());
    }

protected:
    double m_angle{0.0};
    Size m_shapesize;
};

class Shape : public RotateRectangleWidget
{
public:
    Shape(cpSpace *space, const Point& point);

    std::unique_ptr<Widget> clone()
    {
        return std::unique_ptr<Widget>();
    }

    void update();

    bool is_alive() const
    {
        return true;
    }

    void toss()
    {
	cpBodySetVelocity(m_body, cpv(50,10));
	cpBodySetAngularVelocity(m_body, -4.);
    }

    virtual ~Shape();

protected:

    cpSpace* m_space;

    cpBody* createBoxElement(const cpVect& size,
                             const cpVect& position);

private:

    cpBody* m_body;
};

#endif
