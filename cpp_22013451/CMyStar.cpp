#include "pch.h"
#include "CMyStar.h"
//
CMyStar::CMyStar(CPoint point, int r)
{
	pt = point;
	radius = r;
}

void CMyStar::draw(CDC& dc)
{
    int centerX = pt.x;
    int centerY = pt.y;
	int bigR = radius;
	int smallR = radius/3;

    int numPoints = 5;  // º°ÀÇ ²ÀÁþÁ¡ °³¼ö
    double angle = 2 * 3.1415926 / numPoints;

    CPoint* points = new CPoint[numPoints * 2];

    // º°ÀÇ ²ÀÁþÁ¡ ÁÂÇ¥ °è»ê
    for (int i = 0; i < numPoints; i++)
    {
        double angle_i = i * angle;
        double angle_i_half = (i + 0.5) * angle;

        int outerX = static_cast<int>(centerX + bigR * sin(angle_i));
        int outerY = static_cast<int>(centerY - bigR * cos(angle_i));

        points[i * 2] = CPoint(outerX, outerY);

        int innerX = static_cast<int>(centerX + smallR * sin(angle_i_half));
        int innerY = static_cast<int>(centerY - smallR * cos(angle_i_half));

        points[i * 2 + 1] = CPoint(innerX, innerY);
    }



    // º° ±×¸®±â
    CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
    dc.SelectObject(pen);
    CBrush b(color);
    dc.SelectObject(b);
    dc.Polygon(points, numPoints * 2);

    delete[] points;
}

void CMyStar::select(CPoint point)
{
    int numPoints = 5;
    double angle = 2 * 3.1415926 / numPoints;

    // °¢ ²ÀÁþÁ¡ ÁÂÇ¥ °è»ê
    std::vector<CPoint> vertices;
    for (int i = 0; i < numPoints; i++)
    {
        int outerX = static_cast<int>(pt.x + radius * sin(i * angle));
        int outerY = static_cast<int>(pt.y - radius * cos(i * angle));
        vertices.push_back(CPoint(outerX, outerY));

        int innerX = static_cast<int>(pt.x + (radius / 3) * sin((i + 0.5) * angle));
        int innerY = static_cast<int>(pt.y - (radius / 3) * cos((i + 0.5) * angle));
        vertices.push_back(CPoint(innerX, innerY));
    }

    int intersectCount = 0;
    int j = 2 * numPoints - 1;

    for (int i = 0; i < 2 * numPoints; i++)
    {
        if ((vertices[i].y < point.y && vertices[j].y >= point.y) ||
            (vertices[j].y < point.y && vertices[i].y >= point.y))
        {
            if (vertices[i].x + (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) * (vertices[j].x - vertices[i].x) < point.x)
            {
                intersectCount++;
            }
        }
        j = i;
    }

    if (intersectCount % 2 != 0)
    {
        sel = true;
    }
    else 
    {
        sel = false;
    }
}

void CMyStar::SelectRect(CDC& dc)
{
    int numPoints = 5;
    double angle = 2 * 3.1415926 / numPoints;

    // °¢ ²ÀÁþÁ¡ ÁÂÇ¥ °è»ê
    std::vector<CPoint> vertices;
    double left = pt.x + radius * sin(0 * angle);
    double right = pt.x + radius * sin(0 * angle);
    double top = pt.y - radius * cos(0 * angle);
    double bottom = pt.y - radius * cos(0 * angle);

    for (int i = 0; i < numPoints; i++)
    {
        double outerX = pt.x + radius * sin(i * angle);
        if (left > outerX) left = outerX;
        if (right < outerX) right = outerX;
        double outerY = pt.y - radius * cos(i * angle);
        if (top > outerY) top = outerY;
        if (bottom < outerY) bottom = outerY;
    }

    dc.Rectangle(left-5, top-5, right+5, bottom+5);
}


void CMyStar::ShapeMove(double x, double y)
{
    pt.x += x;
    pt.y += y;
}

int CMyStar::returnX(bool M)
{
    if (M == false)
        return pt.x + radius;
    else
        return pt.x - radius;
}

int CMyStar::returnY(bool M)
{
    if (M == false)
        return pt.y + radius;
    else
        return pt.y - radius;
}


bool CMyStar::PointSelect(CPoint point)
{
    int numPoints = 5;
    double angle = 2 * 3.1415926 / numPoints;

    // °¢ ²ÀÁþÁ¡ ÁÂÇ¥ °è»ê
    std::vector<CPoint> vertices;
    for (int i = 0; i < numPoints; i++)
    {
        double outerX = pt.x + radius * sin(i * angle);
        double outerY = pt.y - radius * cos(i * angle);
        vertices.push_back(CPoint(outerX, outerY));

        double innerX = pt.x + (radius / 3) * sin((i + 0.5) * angle);
        double innerY = pt.y - (radius / 3) * cos((i + 0.5) * angle);
        vertices.push_back(CPoint(innerX, innerY));
    }
    int intersectCount = 0;
    int j = 2 * numPoints - 1;

    for (int i = 0; i < 2 * numPoints; i++)
    {
        if ((vertices[i].y < point.y && vertices[j].y >= point.y) ||
            (vertices[j].y < point.y && vertices[i].y >= point.y))
        {
            if (vertices[i].x + (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) * (vertices[j].x - vertices[i].x) < point.x)
            {
                intersectCount++;
            }
        }
        j = i;
    }

    if (intersectCount % 2 != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}