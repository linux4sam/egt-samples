/*
 * RotateImageWidget.cpp
 *
 *  Created on: May 15, 2019
 *      Author: Microchip
 */

#include <Box2D/Box2D.h>
#include <RotateImageWidget.h>
#include <egt/ui>

using namespace egt;
using namespace std;

RotateImageWidget::RotateImageWidget() :
	m_shapeSize(0, 0), m_drawBox(false)
{
}

void RotateImageWidget::image(const Image& image)
{
	// set the image
	m_image = image;

	// update the size
	m_shapeSize.width(image.width());
	m_shapeSize.height(image.height());
}

void RotateImageWidget::angle(double angle)
{
	if (detail::change_if_diff<>(m_angle, angle))
	{
		damage();
	}
}

void RotateImageWidget::draw(Painter& painter, const Rect&)
{
	Point drawPoint1(center());
	drawPoint1.x(drawPoint1.x() - m_shapeSize.width() / 2);
	drawPoint1.y(drawPoint1.y() - m_shapeSize.height() / 2);
	Point drawPoint2(center());
	drawPoint2.x(drawPoint2.x() + m_shapeSize.width() / 2);
	drawPoint2.y(drawPoint2.y() + m_shapeSize.height() / 2);

	// draw the rotate image
	{
		Painter::AutoSaveRestore sr(painter);

		painter.translate(center());
		painter.rotate(m_angle);
		painter.source(m_image, Point(-(m_shapeSize.width() / 2), -(m_shapeSize.height() / 2)));
		painter.paint();
	}

	if (m_drawBox)
	{
		Painter::AutoSaveRestore sr(painter);

		// Draw a bounding box to help identify issues
		painter.translate(center());
		painter.rotate(m_angle);

		Rect drawbox(Point(), m_shapeSize);
		drawbox.x(drawbox.x() - m_shapeSize.width() / 2);
		drawbox.y(drawbox.y() - m_shapeSize.height() / 2);
		drawbox.shrink_around_center(4);
		//drawbox.move_to_center(center());

		theme().draw_box(painter, Theme::FillFlag::blend, drawbox,
                                 Color(128, 128, 128),
                                 Palette::transparent,
                                 theme().default_border());

	}
}
