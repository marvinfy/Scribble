// 
// Based on the Scribble Tutorial by Microsoft Corporation
// http://msdn.microsoft.com/en-us/library/aa314520(v=vs.60).aspx
//

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

