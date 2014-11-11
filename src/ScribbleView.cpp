// 
// Based on the Scribble Tutorial by Microsoft Corporation
// http://msdn.microsoft.com/en-us/library/aa314520(v=vs.60).aspx
//

// ScribbleView.cpp : implementation of the CScribbleView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Scribble.h"
#endif

#include "ScribbleDoc.h"
#include "ScribbleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScribbleView

IMPLEMENT_DYNCREATE(CScribbleView, CView)

BEGIN_MESSAGE_MAP(CScribbleView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CScribbleView construction/destruction

CScribbleView::CScribbleView()
{
	// TODO: add construction code here

}

CScribbleView::~CScribbleView()
{
}

BOOL CScribbleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CScribbleView drawing

void CScribbleView::OnDraw(CDC* pDC)
{
	CScribbleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// The view delegates the drawing of individual strokes to
	// CStroke::DrawStroke( ).
	CTypedPtrList<CObList, CStroke*>& strokeList =
		pDoc->m_strokeList;
	POSITION pos = strokeList.GetHeadPosition( );
	while (pos != NULL)
	{
		CStroke* pStroke = strokeList.GetNext(pos);
		pStroke->DrawStroke( pDC );
	}
}


// CScribbleView printing

BOOL CScribbleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CScribbleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CScribbleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CScribbleView::OnLButtonDown( UINT nFlags, CPoint point )
{
	// Pressing the mouse button in the view window
	// starts a new stroke.

	m_pStrokeCur = GetDocument( )->NewStroke( );
	// Add first point to the new stroke
	m_pStrokeCur->m_pointArray.Add(point);

	SetCapture( );  // Capture the mouse until button up
	m_ptPrev = point;  // Serves as the MoveTo( ) anchor point
	// for the LineTo() the next point, as
	// the user drags the mouse
	return;
}

void CScribbleView::OnLButtonUp( UINT nFlags, CPoint point )
{
	// Mouse button up is interesting in the Scribble
	// application only if the user is currently drawing a new
	// stroke by dragging the captured mouse.

	if( GetCapture( ) != this )
		return;    // If this window (view) didn't capture the
	// mouse, the user isn't drawing in this window.

	CScribbleDoc* pDoc = GetDocument();
	CClientDC dc( this );
	CPen* pOldPen = dc.SelectObject( pDoc->GetCurrentPen( ) );
	dc.MoveTo( m_ptPrev );
	dc.LineTo( point );
	dc.SelectObject( pOldPen );
	m_pStrokeCur->m_pointArray.Add(point);

	ReleaseCapture( );    // Release the mouse capture established
	// at the beginning of the mouse drag.
	return;
}

void CScribbleView::OnMouseMove( UINT nFlags, CPoint point )
{
    // TODO: Add your message handler code here
    // and/or call default
    CView::OnMouseMove( nFlags, point );
}

// CScribbleView diagnostics

#ifdef _DEBUG
void CScribbleView::AssertValid() const
{
	CView::AssertValid();
}

void CScribbleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CScribbleDoc* CScribbleView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScribbleDoc)));
	return (CScribbleDoc*)m_pDocument;
}
#endif //_DEBUG


// CScribbleView message handlers
