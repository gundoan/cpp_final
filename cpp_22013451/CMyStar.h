#pragma once
#include "CMyShape.h"
//
class CMyStar : public CMyShape
{
public:
	CMyStar(CPoint point, int r);//
	virtual void draw(CDC& dc);
	virtual void select(CPoint point);
	virtual void SelectRect(CDC& dc);
	virtual bool PointSelect(CPoint point);
	virtual void ShapeMove(double x, double y);
	virtual int returnX(bool M);
	virtual int returnY(bool M);
};



