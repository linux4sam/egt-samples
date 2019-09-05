/*
 * RotateImageWidget.h
 *
 *  Created on: May 15, 2019
 *      Author: Microchip
 */

#ifndef ROTATEIMAGEWIDGET_H_
#define ROTATEIMAGEWIDGET_H_

#include <Box2D/Box2D.h>
#include <egt/ui>

inline double to_meter(double x)
{
	return x * 0.01;
}

inline double from_meter(double x)
{
	return x * 100.0;
}

class RotateImageWidget: public egt::Widget
{
public:
	explicit RotateImageWidget();

	void set_angle(double angle);
	void set_image(const egt::Image& image);
	void set_drawBoundingBox(bool bDraw) { m_drawBox = bDraw; }
	virtual void draw(egt::Painter& painter, const egt::Rect&) override;

protected:
	egt::Image m_image;
	double m_angle{0.0};
	egt::Size m_shapeSize;
	bool m_drawBox;
};

#endif /* ROTATEIMAGEWIDGET_H_ */
