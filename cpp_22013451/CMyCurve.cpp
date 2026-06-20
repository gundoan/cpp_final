#include "pch.h"
#include "CMyCurve.h"

CMyCurve::CMyCurve(CPoint point)
{
	pts.push_back(point);
}
//
void CMyCurve::draw(CDC& dc)
{
	CPen pen(PS_SOLID, 3, color);
	dc.SelectObject(pen);
	auto it = pts.begin();
	dc.MoveTo(*it);
	it++;
	while (it != pts.end())
	{
		dc.LineTo(*it);
		it++;
	}
}

void CMyCurve::select(CPoint point)
{
	sel = false; // 초기화

	for (const auto& pt : pts)
	{
		int dx = point.x - pt.x;
		int dy = point.y - pt.y;
		int distanceSquared = dx * dx + dy * dy;

		if (distanceSquared <= 400) // 20의 제곱
		{
			sel = true;
			break;
		}
	}
}


void CMyCurve::SelectRect(CDC& dc)
{
	int top = pts[0].y;
	int bottom = pts[0].y;
	int left = pts[0].x;
	int right = pts[0].x;
	
	for (int i = 1; i < pts.size(); i++)
	{
		if (top > pts[i].y)
		{
			top = pts[i].y;
		}
		if (bottom < pts[i].y)
		{
			bottom = pts[i].y;
		}
		if (left > pts[i].x)
		{
			left = pts[i].x;
		}
		if (right < pts[i].x)
		{
			right = pts[i].x;
		}
	}
	dc.Rectangle(left-5, top-5, right+5, bottom+5);
}

void CMyCurve::ShapeMove(double x, double y)
{
	for (int i = 0; i < pts.size(); i++)
	{
		pts[i].x += x;
		pts[i].y += y;
	}
}

int CMyCurve::returnX(bool M)
{
	int left = pts[0].x;
	int right = pts[0].x;

	if (!pts.empty())
	{
		int left = pts[0].x;
		int right = pts[0].x;

		for (int i = 1; i < pts.size(); ++i)
		{
			if (left > pts[i].x)
			{
				left = pts[i].x;
			}
			if (right < pts[i].x)
			{
				right = pts[i].x;
			}
		}
	}


	if (M == false)
		return right;
	else
		return left;
}
int CMyCurve::returnY(bool M)
{
	int top = pts[0].y;
	int bottom = pts[0].y;

	for (int i = 1; i < pts.size(); i++)
	{
		if (top > pts[i].y)
		{
			top = pts[i].y;
		}
		if (bottom < pts[i].y)
		{
			bottom = pts[i].y;
		}
	}

	if (M == false)
		return bottom;
	else
		return top;
}

bool CMyCurve::PointSelect(CPoint point)
{
	for (const auto& pt : pts)
	{
		int distance = static_cast<int>(sqrt(pow(point.x - pt.x, 2) + pow(point.y - pt.y, 2)));
		if (distance <= 20)
		{
			return true;
		}
	}
	return false;
}
