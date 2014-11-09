
#include "stdafx.h"
#include "Stroke.h"

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

}

