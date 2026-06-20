#include "pch.h"
#include "CMyCircle.h"

CMyCircle::CMyCircle()
{
	pt = CPoint(0, 0);
	radius = 0;
}
CMyCircle::CMyCircle(CPoint point, int r)
{
	pt = point;
	radius = r;
}

void CMyCircle::draw(CDC& dc)
{
	// 기존 GDI 객체 저장
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);

	CBrush b(color);
	CBrush* pOldBrush = dc.SelectObject(&b);
	//
	// 원 그리기
	dc.Ellipse(pt.x - radius, pt.y - radius, pt.x + radius, pt.y + radius);

	// 기존 GDI 객체 복원
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}


void CMyCircle::select(CPoint point)
{
	int dx = point.x - pt.x;
	int dy = point.y - pt.y;
	int distanceSquared = dx * dx + dy * dy;
	int radiusSquared = radius * radius;

	sel = (distanceSquared <= radiusSquared);
}


void CMyCircle::SelectRect(CDC& dc)
{
	dc.Rectangle(pt.x - radius - 5, pt.y - radius - 5, pt.x + radius + 5, pt.y + radius + 5);
}

void CMyCircle::ShapeMove(double x, double y)
{
	pt.x += x;
	pt.y += y;
}

int CMyCircle::returnX(bool M)
{
	if (M == false)
		return pt.x + radius;
	else
		return pt.x - radius;
}

int CMyCircle::returnY(bool M)
{
	if (M == false)
		return pt.y + radius;
	else
		return pt.y - radius;
}
bool CMyCircle::PointSelect(CPoint point)
{
	int distance = sqrt(pow(point.x - pt.x, 2) + pow(point.y - pt.y, 2));

	if (distance <= radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}