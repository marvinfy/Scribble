// 
// Based on the Scribble Tutorial by Microsoft Corporation
// http://msdn.microsoft.com/en-us/library/aa314520(v=vs.60).aspx
//

#include "stdafx.h"
#include "Stroke.h"

IMPLEMENT_SERIAL(CStroke, CObject, 1)

////////////////////////////
// CStroke
CStroke::CStroke()
{
	// This empty constructor should be used by
	// the application framework for serialization only
}

CStroke::CStroke(UINT nPenWidth)
{
	m_nPenWidth = nPenWidth;
}

void CStroke::Serialize( CArchive& ar )
{
	if( ar.IsStoring( ) )
	{
		ar << (WORD)m_nPenWidth;
		m_pointArray.Serialize( ar );
	}
	else
	{
		WORD w;
		ar >> w;
		m_nPenWidth = w;
		m_pointArray.Serialize( ar );
	}
}

BOOL CStroke::DrawStroke( CDC* pDC )
{
	CPen penStroke;
	if( !penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)))
		return FALSE;
	CPen* pOldPen = pDC->SelectObject( &penStroke );
	pDC->MoveTo( m_pointArray[0] );
	for( int i=1; i < m_pointArray.GetSize(); i++ )
	{
		pDC->LineTo( m_pointArray[i] );
	}
	pDC->SelectObject( pOldPen );
	return TRUE;
}