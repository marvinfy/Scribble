// 
// Based on the Scribble Tutorial by Microsoft Corporation
// http://msdn.microsoft.com/en-us/library/aa314520(v=vs.60).aspx
//

// ScribbleDoc.cpp : implementation of the CScribbleDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Scribble.h"
#endif

#include "ScribbleDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CScribbleDoc

IMPLEMENT_DYNCREATE(CScribbleDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribbleDoc, CDocument)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CScribbleDoc::OnEditClearAll)
	ON_COMMAND(ID_EDIT_UNDO, &CScribbleDoc::OnEditUndo)
END_MESSAGE_MAP()


// CScribbleDoc construction/destruction

CScribbleDoc::CScribbleDoc()
{
	// TODO: add one-time construction code here

}

CScribbleDoc::~CScribbleDoc()
{
}

BOOL CScribbleDoc::OnNewDocument()
{
	if(!CDocument::OnNewDocument())
		return FALSE;
	InitDocument();
	return TRUE;
}

BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if( !CDocument::OnOpenDocument( lpszPathName ) )
		return FALSE;
	InitDocument( );
	return TRUE;
}

void CScribbleDoc::OnEditClearAll()
{
	DeleteContents( );
	SetModifiedFlag();
	UpdateAllViews( NULL );
}

void CScribbleDoc::OnEditUndo()
{
	if(!m_strokeList.IsEmpty())
	{
		delete m_strokeList.RemoveTail();
		SetModifiedFlag();
		UpdateAllViews( NULL );
	}
}

// CScribbleDoc serialization

void CScribbleDoc::Serialize(CArchive& ar)
{
	m_strokeList.Serialize( ar );
}

void CScribbleDoc::DeleteContents()
{
	while( !m_strokeList.IsEmpty( ) )
	{
		delete m_strokeList.RemoveHead( );
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CScribbleDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CScribbleDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CScribbleDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CScribbleDoc diagnostics

#ifdef _DEBUG
void CScribbleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScribbleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CScribbleDoc commands


CStroke* CScribbleDoc::NewStroke(void)
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);
	m_strokeList.AddTail( pStrokeItem );
	SetModifiedFlag( );    // Mark document as modified
	// to confirm File Close.
	return pStrokeItem;
}

void CScribbleDoc::InitDocument(void)
{
	m_nPenWidth = 2;  // Default 2-pixel pen width
	// Solid black pen
	m_penCur.CreatePen( PS_SOLID, m_nPenWidth, RGB(0,0,0) );
}
