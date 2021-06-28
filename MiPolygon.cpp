
#include "MiPolygon.h"
#include <osgDB/fstream>
#include "MiMath.h"

//using namespace std;
using namespace Mi;
//------------------------------------------------------------------------------
void Polygon::SetPoints( const std::vector<Vector2d>& rkPositionList )
{
	m_kPointList = rkPositionList;
	osgDB::ofstream kFile;
	kFile.open( "Polygon.txt" );
	for( int i = 0; i < m_kPointList.size(); i++ )
	{
		kFile<<m_kPointList[i]<<std::endl;
	}
	kFile.close();
}
//------------------------------------------------------------------------------
void Polygon::Generate( const std::vector<Vector2d>& rkPositionList )
{
	std::vector<Vector2d> kPointPool = rkPositionList;
	m_kPointList.push_back( kPointPool[0] );
	//kPointPool.erase( kPointPool.begin() );
	
	std::swap( kPointPool[0], kPointPool[kPointPool.size()-1] );
	kPointPool.pop_back();
	
	while( !kPointPool.empty() )
	{
		Vector2d kEnd = m_kPointList[m_kPointList.size()-1];
		double dMin = DBL_MAX;
		int iInd = 0;
		for( int i = 0; i < kPointPool.size(); i++ )
		{
			double dLength2 = (kEnd-kPointPool[i]).SquaredLength();
			if( dLength2 < dMin )
			{
				dMin = dLength2;
				iInd = i;
			}
		}
		m_kPointList.push_back( kPointPool[iInd] );
		//kPointPool.erase( kPointPool.begin()+iInd );
		std::swap( kPointPool[iInd], kPointPool[kPointPool.size()-1] );
		kPointPool.pop_back();
	}
	
	osgDB::ofstream kFile;
	kFile.open( "Polygon.txt" );
	for( int i = 0; i < m_kPointList.size(); i++ )
	{
		kFile<<m_kPointList[i]<<std::endl;
	}
	kFile.close();
	
}
//------------------------------------------------------------------------------
bool Polygon::IsIn( const Vector2d& rkPoint ) const
{
	int iCount = 0;
	Vector2d kDir( 1, 0 );
	for( int i = 0; i < m_kPointList.size(); i++ )
	{
		//iCount += Ray2LineSegmentIntersection(
		//	rkPoint, kDir, m_kPointList[i], m_kPointList[(i+1)%m_kPointList.size()] );
			//rkPoint, kDir, m_kPointList[(i+1)%m_kPointList.size()], m_kPointList[i] );
		Vector2d kP0 = m_kPointList[(i-1+m_kPointList.size())%m_kPointList.size()];
		Vector2d kP1 = m_kPointList[i];
		Vector2d kP2 = m_kPointList[(i+1)%m_kPointList.size()];
		Vector2d kP3 = m_kPointList[(i+2)%m_kPointList.size()];
		if( Mi::Mathd::Equal( rkPoint[1], kP1[1] )  )
		{
			if( (kP0[1] < kP1[1] && kP1[1] < kP2[1]) || (kP2[1] < kP1[1] && kP1[1] < kP1[1]) )
			{
				if (Mi::Mathd::Equal(rkPoint[0], kP1[0]) || rkPoint[0] < kP1[0])
					iCount++;
			}
		}
		else if( Mi::Mathd::Equal( rkPoint[1], kP2[1] ) )
		{
			if( (kP1[1] < kP2[1] && kP2[1] < kP3[1]) || (kP3[1] < kP2[1] && kP2[1] < kP1[1]))
			{
				if (Mi::Mathd::Equal(rkPoint[0], kP2[0]) || rkPoint[0] < kP2[0])
					iCount++;
			}
		}
		else if( (kP1[1] < rkPoint[1] && rkPoint[1] < kP2[1]) || (kP2[1] < rkPoint[1] && rkPoint[1] < kP1[1]) )
		{
			Vector2d kIntersect( 0, rkPoint[1] );
			double dT = (rkPoint[1]-kP1[1])/(kP2[1]-kP1[1]);
			kIntersect[0] = kP1[0] + dT*(kP2[1]-kP1[1]);
			if( Mi::Mathd::Equal( rkPoint[0], kIntersect[0] ) || rkPoint[0] < kIntersect[0] )
			{
				iCount++;
			}
		}

	}
	if( iCount%2 == 1 )
		return true;
	return false;
}
//------------------------------------------------------------------------------
int Polygon::Ray2LineSegmentIntersection( 
	const Vector2d& rkRayOrig, const Vector2d& rkRayDir, 
	const Vector2d& rkLineSegP1, const Vector2d& rkLineSegP2 ) const
{
	Vector2d kLineSegDir = rkLineSegP2-rkLineSegP1;

	Vector2d kD0 = rkRayDir;
	Vector2d kD1 = kLineSegDir;

	Vector2d kDiff = rkRayOrig - rkLineSegP1;

	double dCrossD0D1 = kD0[0]*kD1[1]-kD0[1]*kD1[0];
	double dSqrCrossD0D1 = dCrossD0D1*dCrossD0D1;
	double dSqrLen0 = kD0.SquaredLength();
	double dSqrLen1 = kD1.SquaredLength();

	if( dSqrCrossD0D1 > 1e-6 * dSqrLen0 * dSqrLen1 )
	{
		double dRayT = kDiff[0]*kLineSegDir[1] - kDiff[1]*kLineSegDir[0];
		dRayT /= dCrossD0D1;
		if( dRayT < 0 )
			return 0;
		double dLineSegT = kDiff[0]*rkRayDir[1] - kDiff[1]*rkRayDir[0];
		dLineSegT /= dCrossD0D1;

		if( abs( dLineSegT-0 ) < 1e-7 )
		{
			return 1;
		}
		else if( abs( dLineSegT-1 ) < 1e-7 )
		{
			return 0;
		}
		else if( 0 < dLineSegT && dLineSegT < 1 )
		{
			return 1;
		}
		else 
		{
			return 0;
		}

	}

	double dCrossDiffD0 = kDiff[0]*kD0[1] - kDiff[1]*kD0[0];
	double dSqrCrossDiffD0 = dCrossDiffD0*dCrossDiffD0;
	double dSqrLenDiff = kDiff.SquaredLength();
	if( dSqrCrossDiffD0 > 1e-6 * dSqrLen0 * dSqrLenDiff )
	{
		return 0;
	}

	return 2;
}
//------------------------------------------------------------------------------