//
// ChildView.h: CChildView 클래스의 인터페이스
////
//
#pragma once


// CChildView 창
#include <vector>
#include "CMyShape.h"
#include "CMyRect.h"
#include "CMyCircle.h"
#include "CMyStar.h"
#include "CMyCurve.h"
#include "GroupShape.h"

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	UINT shape; // 0 = 사각형, 1 = 원, 2 = 선, 3 = 별
	std::vector<CMyShape*> m_shapes;
	int mode; // 0 = draw , 1 = select
	bool push_shift; // 0 = up, 1 = down;
	int numShapes;
	int numSelect;
	CPoint pt;
	CPoint m_pt1, m_pt2;
	bool PointShape;
	std::vector<GroupShape> m_G;
// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShapeRect();
	afx_msg void OnShapeCircle();
	afx_msg void OnShapeLine();
	afx_msg void OnShapeStar();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnActionSelect();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnActionGroup();
	afx_msg void OnActionUngroup();
	afx_msg void OnAlignBringfront();
	afx_msg void OnAlignBringback();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnUpdateActionGroup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActionUngroup(CCmdUI* pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};