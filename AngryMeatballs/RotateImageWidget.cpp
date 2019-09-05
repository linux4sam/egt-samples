/*
 * RotateImageWidget.cpp
 *
 *  Created on: May 15, 2019
 *      Author: Microchip
 */

#include <Box2D/Box2D.h>
#include <RotateImageWidget.h>
#include <cairo.h>
#include <egt/ui>

using namespace egt;
using namespace std;

RotateImageWidget::RotateImageWidget() :
	m_shapeSize(0, 0), m_drawBox(false)
{
	set_theme(theme());
}

void RotateImageWidget::set_image(const Image& image)
{
	// set the image
	m_image = image;

	// update the size
	m_shapeSize.set_width(image.width());
	m_shapeSize.set_height(image.height());
}

void RotateImageWidget::set_angle(double angle)
{
	if (detail::change_if_diff<>(m_angle, angle))
	{
		damage();
	}
}

void RotateImageWidget::draw(Painter& painter, const Rect&)
{
	auto cr = painter.context().get();

	Point drawPoint1(center());
	drawPoint1.set_x(drawPoint1.x() - m_shapeSize.width() / 2);
	drawPoint1.set_y(drawPoint1.y() - m_shapeSize.height() / 2);
	Point drawPoint2(center());
	drawPoint2.set_x(drawPoint2.x() + m_shapeSize.width() / 2);
	drawPoint2.set_y(drawPoint2.y() + m_shapeSize.height() / 2);

	// draw the rotate image
	cairo_save(cr);

	cairo_translate(cr, center().x(), center().y());
	cairo_rotate(cr, m_angle);
	cairo_set_source_surface(cr, m_image.surface().get(), -(m_shapeSize.width() / 2), -(m_shapeSize.height() / 2));
	cairo_paint(cr);

	cairo_restore(cr);

	if (m_drawBox)
	{
		// Draw a bounding box to help identify issues
		cairo_save(cr);
		cairo_translate(cr, center().x(), center().y());
		cairo_rotate(cr, m_angle);

		Rect drawbox(Point(), m_shapeSize);
		drawbox.set_x(drawbox.x() - m_shapeSize.width() / 2);
		drawbox.set_y(drawbox.y() - m_shapeSize.height() / 2);
		drawbox.shrink_around_center(4);
		//drawbox.move_to_center(center());

		theme().draw_box(painter, Theme::boxtype::blank, drawbox,
                                 Color(128, 128, 128),
                                 Palette::transparent,
                                 theme().default_border());

		cairo_restore(cr);
	}
}
