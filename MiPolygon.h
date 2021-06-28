

#ifndef MIPOLYGON_H
#define MIPOLYGON_H

#include "MiVector2.h"
#include <vector>

namespace Mi
{

class Polygon 
{
public:
	void SetPoints( const std::vector<Vector2d>& rkPositionList );
	void Generate( const std::vector<Vector2d>& rkPositionList );
	bool IsIn( const Vector2d& rkPoint ) const;
	int Ray2LineSegmentIntersection( 
		const Vector2d& rkRayOrig, const Vector2d& rkRayDir,
		const Vector2d& rkLineSegP1, const Vector2d& rkLineSegP2 ) const;

protected:
	std::vector<Vector2d> m_kPointList;

};

}

#endif