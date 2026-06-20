// ChildView.cpp: CChildView 클래스의 구현
//
//
#include "pch.h"
#include "framework.h"
#include "Homework_DrowingShape.h"
#include "ChildView.h"
//
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	shape = 0;
	mode = 0;
	push_shift = 0;
	numShapes = 0;
	numSelect = 0;
	m_pt1 = CPoint(0, 0);
	m_pt2 = CPoint(0, 0);
	PointShape = false;
}

CChildView::~CChildView()
{
	for (auto* shape : m_shapes)
	{
		delete shape;
	}
}



BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_DRAW_RECTANGLE, &CChildView::OnShapeRect)
	ON_COMMAND(ID_DRAW_CIRCLE, &CChildView::OnShapeCircle)
	ON_COMMAND(ID_DRAW_CURVE, &CChildView::OnShapeLine)
	ON_COMMAND(ID_DRAW_STAR, &CChildView::OnShapeStar)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ACTION_SELECT, &CChildView::OnActionSelect)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_ACTION_GROUP, &CChildView::OnActionGroup)
	ON_COMMAND(ID_ACTION_UNGROUP, &CChildView::OnActionUngroup)
	ON_COMMAND(ID_ALIGN_BRINGFRONT, &CChildView::OnAlignBringfront)
	ON_COMMAND(ID_ALIGN_BRINGBACK, &CChildView::OnAlignBringback)
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_ACTION_GROUP, &CChildView::OnUpdateActionGroup)
	ON_UPDATE_COMMAND_UI(ID_ACTION_UNGROUP, &CChildView::OnUpdateActionUngroup)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(rect);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CBitmap mbmp;
	mbmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memdc.SelectObject(mbmp);
	memdc.Rectangle(rect);

	// Draw watermark background text
	{
		CFont wFont;
		wFont.CreateFont(70, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
		CFont* pOldFont = memdc.SelectObject(&wFont);
		COLORREF oldColor = memdc.SetTextColor(RGB(255, 182, 193));
		int oldBkMode = memdc.SetBkMode(TRANSPARENT);
		CString watermark = _T("C++ Homework Final");
		CSize ts = memdc.GetTextExtent(watermark);
		int wx = (rect.Width() - ts.cx) / 2;
		int wy = (rect.Height() - ts.cy) / 2;
		memdc.TextOutW(wx, wy, watermark);
		memdc.SelectObject(pOldFont);
		memdc.SetTextColor(oldColor);
		memdc.SetBkMode(oldBkMode);
	}

	auto it = m_shapes.begin();
	while (it != m_shapes.end())
	{
		CBrush b((*it)->color);
		memdc.SelectObject(b);
		(*it)->draw(memdc);
		it++;
	}
	if (mode == 1)
	{
		for (auto* shape : m_shapes)
		{
			CBrush b;
			b.CreateStockObject(NULL_BRUSH);
			CPen pen(PS_DOT, 1, RGB(255, 0, 0));
			memdc.SelectObject(&b);
			memdc.SelectObject(&pen);

			if (shape->sel == 1 && !shape->Grouped())
			{
				shape->SelectRect(memdc);
			}

			if (shape->Grouped() && shape->sel == 1)
			{
				for (auto& group : m_G)
				{
					if (group.searchShape(shape) && !group.gr)
					{
						group.selectRect(memdc);
					}
				}
			}
		}
	}


	numShapes = 0;
	numSelect = 0;

	for (int i = 0; i < m_shapes.size(); i++)
	{
		if (m_shapes[i]->Grouped() == false)
		{
			numShapes++;
			if (m_shapes[i]->sel == true)
				numSelect++;
		}
	}

	if (PointShape == false && mode == 1)
	{
		CBrush b;
		b.CreateStockObject(NULL_BRUSH);
		CPen pen(PS_DOT, 1, RGB(255, 0, 0));
		memdc.SelectObject(b);
		memdc.SelectObject(pen);
		memdc.Rectangle(m_pt1.x, m_pt1.y, m_pt2.x, m_pt2.y);
	}

	for (int i = 0; i < m_G.size(); i++)
	{
		if (m_G[i].gr == false && m_G[i].group.size() != 0)
		{
			numShapes++;
			m_G[i].select_Group();
			if (m_G[i].sel == true)
				numSelect++;
		}
	}
	CString str1;
	str1.Format(_T("Number of Shapes: %d"), numShapes);
	memdc.TextOutW(5, 5, str1);
	CString str2;
	str2.Format(_T("Number of Selected: %d"), numSelect);
	memdc.TextOutW(5, 25, str2);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
}




void CChildView::OnShapeRect()
{
	mode = 0;
	for (int i = 0; i < m_shapes.size(); i++)
	{
		m_shapes[i]->sel = false;
	}
	shape = 0;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildView::OnShapeCircle()
{
	mode = 0;
	for (int i = 0; i < m_shapes.size(); i++)
	{
		m_shapes[i]->sel = false;
	}
	shape = 1;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildView::OnShapeLine()
{
	mode = 0;
	for (int i = 0; i < m_shapes.size(); i++)
	{
		m_shapes[i]->sel = false;
	}
	shape = 2;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildView::OnShapeStar()
{
	mode = 0;
	for (int i = 0; i < m_shapes.size(); i++)
	{
		m_shapes[i]->sel = false;
	}
	shape = 3;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	if (mode == 0)
	{
		if (shape == 0)
		{
			m_shapes.push_back(new CMyRect(point, point));
			for (int i = 0; i < m_G.size(); i++)
			{
				m_shapes.back()->gr.push_back(0);
			}
		}
		if (shape == 1)
		{
			m_shapes.push_back(new CMyCircle(point, 0));
			for (int i = 0; i < m_G.size(); i++)
			{
				m_shapes.back()->gr.push_back(0);
			}
		}
		if (shape == 2)
		{
			m_shapes.push_back(new CMyCurve(point));
			for (int i = 0; i < m_G.size(); i++)
			{
				m_shapes.back()->gr.push_back(0);
			}
		}
		if (shape == 3)
		{
			m_shapes.push_back(new CMyStar(point, 0));
			for (int i = 0; i < m_G.size(); i++)
			{
				m_shapes.back()->gr.push_back(0);
			}
		}
		m_shapes.back()->color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	if (mode == 1)
	{
		pt = point;

		

		if (push_shift == false)
		{
			int index = m_shapes.size();
			for (int i = m_shapes.size() - 1; i >= 0; i--)
			{
				m_shapes[i]->select(point);
				if (m_shapes[i]->sel == true)
				{
					index = i;
					break;
				}
			}
			if (index != m_shapes.size())
			{
				for (int i = 0; i < m_shapes.size(); i++)
				{
					if (m_shapes[index] != m_shapes[i])
						m_shapes[i]->sel = false;
				}
			}
			
			if (index != m_shapes.size())
			{
				if (m_shapes[index]->Grouped() == true)
				{
					int groupindex = m_G.size();
					for (int i = m_G.size() - 1; i >= 0; i--)
					{
						if (m_G[i].searchShape(m_shapes[index]) == true)
						{
							groupindex = i;
							break;
						}
					}
					if (groupindex != m_G.size())
					{
						for (int j = 0; j < m_G[groupindex].group.size(); j++)
						{
							m_G[groupindex].group[j]->sel = true;
						}
					}
				}
			}
		}
		else
		{
			int index = m_shapes.size();
			for (int i = m_shapes.size() - 1; i >= 0; i--)
			{
				if (m_shapes[i]->sel == true)
					continue;
				else
				{
					m_shapes[i]->select(point);
					if (m_shapes[i]->sel == true)
					{
						index = i;
						break;
					}
				}
			}
			if (index != m_shapes.size())
			{
				if (m_shapes[index]->Grouped() == true)
				{
					int groupindex = m_G.size();
					for (int i = m_G.size() - 1; i >= 0; i--)
					{
						if (m_G[i].searchShape(m_shapes[index]) == true)
						{
							groupindex = i;
							break;
						}
					}
					if (groupindex != m_G.size())
					{
						for (int j = 0; j < m_G[groupindex].group.size(); j++)
						{
							m_G[groupindex].group[j]->sel = true;
						}
					}
				}
			}
		}

		m_pt1 = point;
		for (int i = 0; i < m_shapes.size(); i++)
		{
			PointShape = m_shapes[i]->PointSelect(m_pt1);
			if (m_shapes[i]->PointSelect(m_pt1))
			{
				break;
			}
		}
		m_pt2 = point;
	}

	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (mode == 0)
	{
		if (shape == 0 && nFlags == MK_LBUTTON)
		{
			m_shapes.back()->pt2 = point;
		}
		if (shape == 1 && nFlags == MK_LBUTTON)
		{
			int x = point.x - m_shapes.back()->pt.x;
			int y = point.y - m_shapes.back()->pt.y;
			m_shapes.back()->radius = sqrt(x * x + y * y);
		}
		if (shape == 2 && nFlags == MK_LBUTTON)
		{
			m_shapes.back()->pts.push_back(point);
		}
		if (shape == 3 && nFlags == MK_LBUTTON)
		{
			int x = point.x - m_shapes.back()->pt.x;
			int y = point.y - m_shapes.back()->pt.y;
			m_shapes.back()->radius = sqrt(x * x + y * y);
		}
	}
	if (mode == 1 && (nFlags & MK_LBUTTON))
	{
		if (PointShape)
		{
			double x = point.x - pt.x;
			double y = point.y - pt.y;
			for (auto* shape : m_shapes)
			{
				if (shape->sel)
				{
					shape->ShapeMove(x, y);
				}
			}
			pt = point;
		}
		else
		{
			m_pt2 = point;
		}
	}

	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
}


void CChildView::OnActionSelect()
{
	mode = 1;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SHIFT)
	{
		push_shift = 1;
	}
	if (nChar == VK_DELETE)
	{
		auto it = m_shapes.begin();
		while (it != m_shapes.end())
		{
			if ((*it)->sel == true)
			{
				it = m_shapes.erase(it);
			}
			else
			{
				it++;
			}
		}
		Invalidate();
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SHIFT)
	{
		push_shift = 0;
	}
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}



void CChildView::OnActionGroup()
{
	m_G.push_back(GroupShape());

	for (int i = 0; i < m_shapes.size(); i++)
	{
		m_shapes[i]->gr.push_back(0);
	}
	for (int i = 0; i < m_shapes.size(); i++)
	{
		if (m_shapes[i]->sel == true)
			m_G.back().add_Shape(m_shapes[i]);
	}
	for (int i = 0; i < m_G.size() - 1; i++)
	{
		m_G[i].Grouped(i);
	}

	push_shift = 0;
	Invalidate();
}


void CChildView::OnActionUngroup()
{
	for (int i = m_G.size() - 1; i >= 0; i--)
	{
		m_G[i].select_Group();
		if (m_G[i].sel == true)
		{
			m_G[i].remove_Shape(i);
			break;
		}
	}
	for (int i = 0; i < m_G.size(); i++)
	{
		m_G[i].Grouped(i);
	}
	push_shift = 0;
	Invalidate();
}


void CChildView::OnAlignBringfront()
{
	std::vector<CMyShape*> p;
	auto it = m_shapes.begin();
	while (it != m_shapes.end())
	{
		if ((*it)->sel == true)
		{
			p.push_back(*it);
			it = m_shapes.erase(it);
		}
		else
		{
			it++;
		}
	}
	for (int i = 0; i < p.size(); i++)
		m_shapes.push_back(p[i]);
	push_shift = 0;
	Invalidate();
}


void CChildView::OnAlignBringback()
{
	std::vector<CMyShape*> p;
	auto it = m_shapes.begin();
	while (it != m_shapes.end())
	{
		if ((*it)->sel == true)
		{
			p.push_back(*it);
			it = m_shapes.erase(it);
		}
		else
		{
			it++;
		}
	}
	for (int i = p.size()-1; i >= 0; i--)
		m_shapes.insert(m_shapes.begin(),p[i]);
	push_shift = 0;
	Invalidate();
}


void CChildView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu Menu;
	Menu.LoadMenuW(IDR_MAINFRAME);

	CMenu* pmenu = Menu.GetSubMenu(5);

	pmenu->TrackPopupMenu(	TPM_LEFTALIGN | TPM_RIGHTBUTTON,	point.x, point.y, AfxGetMainWnd());
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CChildView::OnUpdateActionGroup(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(numSelect >= 2);
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildView::OnUpdateActionUngroup(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(numSelect >= 1);
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (mode == 1 && PointShape == 0)
	{
		int left = m_pt1.x;
		int right = m_pt2.x;
		if (left > right) std::swap(left, right);
		int top = m_pt1.y;
		int bottom = m_pt2.y;
		if (top > bottom) std::swap(top, bottom);

		for (int i = 0; i < m_shapes.size(); i++)
		{
			if (m_shapes[i]->Grouped() == false)
			{
				if (m_shapes[i]->returnX(true) > left && m_shapes[i]->returnX(false) < right &&
					m_shapes[i]->returnY(true) > top && m_shapes[i]->returnY(false) < bottom)
					m_shapes[i]->sel = true;
			}
		}

		for (int i = 0; i < m_G.size(); i++)
		{
			if (m_G[i].gr == false && m_G[i].group.size() != 0)
			{
				if (m_G[i].returnX(true) > left && m_G[i].returnX(false) < right && m_G[i].returnY(true) > top && m_G[i].returnY(false) < bottom)
				{
					for (int j = 0; j < m_G[i].group.size(); j++)
					{
						m_G[i].group[j]->sel = true;
					}
				}
			}
		}
	}

	m_pt1 = CPoint(0, 0);
	m_pt2 = CPoint(0, 0);
	ReleaseCapture();
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}
