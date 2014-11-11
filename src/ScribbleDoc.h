// 
// Based on the Scribble Tutorial by Microsoft Corporation
// http://msdn.microsoft.com/en-us/library/aa314520(v=vs.60).aspx
//

// ScribbleDoc.h : interface of the CScribbleDoc class
//

#include "Stroke.h"

#pragma once


class CScribbleDoc : public CDocument
{
protected: // create from serialization only
	CScribbleDoc();
	DECLARE_DYNCREATE(CScribbleDoc)

	// Attributes
public:
protected:
	UINT m_nPenWidth;
	CPen m_penCur;

	// Operations
public:
	CTypedPtrList<CObList, CStroke*> m_strokeList;
	CPen*   GetCurrentPen( ) { return &m_penCur; }
	CStroke* NewStroke(void);
	void InitDocument(void);

	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents(); // delete doc items etc

	void OnEditClearAll();
	void OnEditUndo();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CScribbleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
