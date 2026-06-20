#pragma once
#include "CMyShape.h"
//
class CMyRect : public CMyShape
{
public://
	CMyRect();
	CMyRect(CPoint point1, CPoint point2);
	virtual void draw(CDC& dc);
	virtual void select(CPoint point);
	virtual void SelectRect(CDC& dc);
	virtual void ShapeMove(double x, double y);
	virtual bool PointSelect(CPoint point);
	virtual int returnX(bool M);
	virtual int returnY(bool M);
};

