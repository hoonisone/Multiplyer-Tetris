#pragma once
#include "Painter.h"

class ColorPainter : public Painter{
private:
	Color pointColor, backgroundColor;
	void setting(Color pointColor, Color backgroundColor) const {
		Consol::changeTextColor(pointColor);
		Consol::changeBackgroundColor(backgroundColor);
	}
public: 
	ColorPainter(const ColorPainter* painter) : ColorPainter(*painter) {}
	ColorPainter(const ColorPainter &painter) : ColorPainter(painter.pointShape, painter.pointColor, painter.backgroundColor){}
	ColorPainter(PointShape pointShape = { "*" }, Color pointColor = WHITE, Color backgroundColor = BLACK) :Painter(pointShape), pointColor(pointColor), backgroundColor(backgroundColor) {
	};
	virtual ColorPainter* getCopy() const override {
		return new ColorPainter(this);
	}
	void setColor(Color pointColor, Color bacgroundColor)  {
		this->pointColor = pointColor;
		this->backgroundColor = backgroundColor;
	}	// pencil의 컬러를 설정하는 것으로 콜솔의 색을 설정하는 것과는 별개
	Color getPointColor() const{
		return pointColor;
	}
	virtual void point(int x, int y) const {
		setting(pointColor, backgroundColor);
		Painter::point(x, y);
	}
	virtual void horizontal(int x, int y, int w) const {
		setting(pointColor, backgroundColor);
		Painter::horizontal(x, y, w);
	}
	virtual void vertical(int x, int y, int h) const {
		setting(pointColor, backgroundColor);
		Painter::vertical(x, y, h);
	}
	virtual void rectBorder(int x, int y, int w, int h) const {
		setting(pointColor, backgroundColor);
		Painter::rectBorder(x, y, w, h);
	}
	virtual void rect(int x, int y, int w, int h) const {
		setting(pointColor, backgroundColor);
		Painter::rect(x, y, w, h);
	}
};