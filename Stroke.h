#ifndef __STROKE_H__
#define __STROKE_H__

/////////////////////////////////////////////////////
// class CStroke
// A stroke is a series of connected points in the Scribble drawing.
// A Scribble document may have multiple strokes.
class CStroke : public CObject
{
public:
	CStroke( UINT nPenWidth );

protected:
	CStroke( );
	DECLARE_SERIAL( CStroke )

	// Attributes	
protected:
	UINT   m_nPenWidth;  // One width applies to entire stroke
public:
	CArray<CPoint, CPoint>   m_pointArray;  // Series of connected
											// points

	// Operations
public:
	BOOL DrawStroke( CDC* pDC );

public:
	virtual void Serialize( CArchive& ar );
};

#endif __STROKE_H__
