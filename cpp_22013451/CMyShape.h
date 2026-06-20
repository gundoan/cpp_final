#pragma once
//
#include <vector>
#include <algorithm>
class CMyShape
{
public:
	CPoint pt1, pt2; // 사각형 그릴 때 사용
	CPoint pt; //원과 별 그릴 때 사용
	std::vector<CPoint> pts;
	int radius;
	COLORREF color;
	bool sel; // 이 도형이 선택되어 있는지 확인
	std::vector<int> gr;
public:
	CMyShape()
	{ 
		radius = 0;  
		sel = 0; 
		color = RGB(0, 0, 0); 
	}
	virtual void draw(CDC& dc) {};
	virtual void select(CPoint point) {};
	virtual bool PointSelect(CPoint point) { return false; }
	virtual void SelectRect(CDC& dc) {};
	virtual void ShapeMove(double x, double y) {};
	virtual int returnX(bool M) { return 0; }
	virtual int returnY(bool M) { return 0; }
	bool Grouped()
	{
		for (int val : gr)
		{//
			if (val == 1)
				return true;
		}
		return false;
	}

};

