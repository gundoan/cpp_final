#include "pch.h"
#include "GroupShape.h"

void GroupShape::add_Shape(CMyShape* in)
{
	group.push_back(in);
	in->gr.back() = 1;
}

void GroupShape::remove_Shape(int index)
{
	for (auto it = group.begin(); it != group.end();)
	{
		(*it)->gr[index] = 0;
		it = group.erase(it);
	}
	sel = false;
}


void GroupShape::select_Group()
{
	sel = false; // 기본적으로 sel을 false로 초기화

	for (const auto& shape : group)
	{
		if (shape->sel)
		{
			sel = true;
			break;
		}
	}
}


void GroupShape::selectRect(CDC &dc)
{
	int top = group[0]->returnY(true);
	int bottom = group[0]->returnY(false);
	int left = group[0]->returnX(true);
	int right = group[0]->returnX(false);

	for (int i = 1; i < group.size(); i++)
	{
		if (top > group[i]->returnY(true))
			top = group[i]->returnY(true);
		if (bottom < group[i]->returnY(false))
			bottom = group[i]->returnY(false);
		if (left > group[i]->returnX(true))
			left = group[i]->returnX(true);
		if (right < group[i]->returnX(false))
			right = group[i]->returnX(false);
	}

	dc.Rectangle(left-5, top-5, right+5, bottom+5);
}

bool GroupShape::searchShape(CMyShape* in)
{
	for (int i = 0; i < group.size(); i++)
	{
		if (group[i] == in)
		{
			return true;
		}
	}
	return false;
}

void GroupShape::Grouped(int index)
{
	// group 벡터에서 각 그룹을 순회합니다.
	for (const auto& grp : group)
	{
		// 주어진 인덱스(index)보다 큰 인덱스를 갖는 요소들을 검사합니다.
		for (int j = index + 1; j < grp->gr.size(); j++)
		{
			// 그룹 내에 1이 존재하면 그룹화된 것으로 간주합니다.
			if (grp->gr[j] == 1)
			{
				gr = true; // 그룹화된 상태로 설정합니다.
				return; // 함수 종료
			}//
		}
	}
	gr = false; // 그룹화되지 않은 상태로 설정합니다.
}


int GroupShape::returnX(bool M)
{
	int left = group[0]->returnX(true);
	int right = group[0]->returnX(false);
	for (int i = 1; i < group.size(); i++)
	{
		if (left > group[i]->returnX(true))
			left = group[i]->returnX(true);
		if (right < group[i]->returnX(false))
			right = group[i]->returnX(false);
	}
	if (M == true)
		return left;
	else
		return right;
}
int GroupShape::returnY(bool M)
{
	int top = group[0]->returnY(true);
	int bottom = group[0]->returnY(false);

	for (int i = 1; i < group.size(); i++)
	{
		if (top > group[i]->returnY(true))
			top = group[i]->returnY(true);
		if (bottom < group[i]->returnY(false))
			bottom = group[i]->returnY(false);
	}
	if (M == true)
		return top;
	else
		return bottom;
}