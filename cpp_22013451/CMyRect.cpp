#include "pch.h"
#include "CMyRect.h"
//
CMyRect::CMyRect()
{
	pt1 = CPoint(0, 0);
	pt2 = CPoint(0, 0);
}
CMyRect::CMyRect(CPoint point1, CPoint point2)
{
	pt1 = point1;
	pt2 = point2;
}

void CMyRect::draw(CDC& dc)
{
	CPen pen(PS_SOLID, 3, RGB(0,0,0));
	dc.SelectObject(pen);
	CBrush b(color);
	dc.SelectObject(b);
	dc.Rectangle(pt1.x, pt1.y, pt2.x, pt2.y);
}

void CMyRect::select(CPoint point)
{
	int left = pt1.x;
	int right = pt2.x;
	if (left > right) std::swap(left, right);
	int top = pt1.y;
	int bottom = pt2.y;
	if (top > bottom) std::swap(top, bottom);

	sel = (point.x >= left && point.x <= right && point.y >= top && point.y <= bottom);
}


void CMyRect::SelectRect(CDC& dc)
{
	int left = pt1.x;
	int right = pt2.x;
	int top = pt1.y;
	int bottom = pt2.y;

	// 정렬하여 왼쪽, 오른쪽, 위, 아래 값을 결정
	if (left > right) std::swap(left, right);
	if (top > bottom) std::swap(top, bottom);

	// 사각형 그리기
	dc.Rectangle(left - 5, top - 5, right + 5, bottom + 5);
}


void CMyRect::ShapeMove(double x, double y)
{
	pt1.x += x;
	pt1.y += y;
	pt2.x += x;
	pt2.y += y;
}

int CMyRect::returnX(bool M)
{
	int left = pt1.x;
	int right = pt2.x;
	if (left > right) std::swap(left, right);

	if (M == false)
	{
		return right;
	}
	else
	{
		return left;
	}
}

int CMyRect::returnY(bool M)
{
	int top = pt1.y;
	int bottom = pt2.y;
	if (top > bottom) std::swap(top, bottom);

	if (M == false)
	{
		return bottom;
	}
	else
	{
		return top;
	}
}

bool CMyRect::PointSelect(CPoint point)
{
	int left = pt1.x;
	int right = pt2.x;
	if (left > right) std::swap(left, right);
	int top = pt1.y;
	int bottom = pt2.y;
	if (top > bottom) std::swap(top, bottom);

	return (point.x >= left && point.x <= right && point.y >= top && point.y <= bottom);
}
