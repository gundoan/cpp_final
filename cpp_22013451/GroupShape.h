#pragma once
#include "CMyShape.h"
#include <vector>
//
class GroupShape
{
public:
	std::vector<CMyShape*> group;
	bool sel;//
	bool gr;
public:
	GroupShape() { sel = false; gr = false; }
	void add_Shape(CMyShape* in);
	void remove_Shape(int index);
	void select_Group();
	void selectRect(CDC& dc);
	bool searchShape(CMyShape* in);
	void Grouped(int index);
	int returnX(bool M);
	int returnY(bool M);
};

