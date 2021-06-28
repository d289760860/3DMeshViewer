
#ifndef MIMATH_H
#define MIMATH_H

#include <cmath>
#include <vector>
#include "MiVector3.h"
#include "MiMatrix3.h"

namespace Mi
{

extern unsigned char g_aucColorMap[192];
extern int g_iBinNum;


template<class Real>
class Math
{
public:
	static bool Equal( Real tLHS, Real tRHS );
	static bool GreaterEqual( Real tLHS, Real tRHS );
	static bool LessEqual( Real tLHS, Real tRHS );
	static bool Greater( Real tLHS, Real tRHS );
	static bool Less( Real tLHS, Real tRHS );
	static Real ms_tPresicion;

	static std::vector<Real> ZScoreNormalization( const std::vector<Real>& rkData );
	static std::vector<Real> MinMaxNormalization( const std::vector<Real>& rkData );

	static Vector3<Real> RGB2HSV( const Vector3<Real>& rkRGB, bool bProj = false );
	static Vector3<Real> RGB2HSL( const Vector3<Real>& rkRGB, bool bProj = false );
	static Vector3<Real> HSV2RGB( const Vector3<Real>& rkHSV, bool bProj = false );
	static Vector3<Real> HSL2RGB( const Vector3<Real>& rkHSL, bool bProj = false );

	static Vector3<Real> RGB2XYZ( const Vector3<Real>& rkRGB, bool bProj = false );
	static Vector3<Real> XYZ2LAB( const Vector3<Real>& rkXYZ, bool bProj = false );
	static Vector3<Real> RGB2LAB( const Vector3<Real>& rkRGB, bool bProj = false );

	static Vector3<Real> XYZ2RGB( const Vector3<Real>& rkXYZ, bool bProj = false );
	static Vector3<Real> LAB2XYZ( const Vector3<Real>& rkLAB, bool bProj = false );
	static Vector3<Real> LAB2RGB( const Vector3<Real>& rkLAB, bool bProj = false );

	static Vector3<Real> LAB2LCH( const Vector3<Real>& rkLAB, bool bProj = false );

	//Activity, Weight and Heat
	static Vector3<Real> LAB2AWH( const Vector3<Real>& rkLAB );

	static Vector3<Real> LABClamp( const Vector3<Real>& rkLAB );
	static Vector3<Real> HSVClamp( const Vector3<Real>& rkLAB );
	static Vector3<Real> HSLClamp( const Vector3<Real>& rkLAB );

	static Vector3<Real> GetColor( int iBinIndex, int iMaxIndex );

	static std::vector<int> SortIndex( const std::vector<Real>& rkData );

	static Real Mean( const std::vector<Real>& rkData );
	static Real Mean2( const std::vector<Real>& rkData );
	static Real Mean4( const std::vector<Real>& rkData );
	static Real WeightedMean( 
		const std::vector<Real>& rkData, const std::vector<Real>& rkWeight );
	static Real MeanSqrt( const std::vector<Real>& rkData );
	static Real MeanSqrtSqrt( const std::vector<Real>& rkData );

	static Real Max( const std::vector<Real>& rkData );
	static Real Max( const std::vector<std::vector<Real>>& rkData );
	static Real Min( const std::vector<Real>& rkData );
	static Real Min( const std::vector<std::vector<Real>>& rkData );


	static Real Median( const std::vector<Real>& rkData );
	static Real Median( 
		const std::vector<Real>& rkData, const std::vector<Real>& rkWeight );

	static Real Percentile( const std::vector<Real>& rkData, Real tPercentile );

	static Real Variance( const std::vector<Real>& rkData, Real tMean );
	static Real Skewness( const std::vector<Real>& rkData, Real tMean, Real tVariance );
	static Real Kurtosis( const std::vector<Real>& rkData, Real tMean, Real tVariance );

	static Real Mean( const std::vector<Real>& rkData, const std::vector<Real>& rkWeight );
	static Real Mean2( const std::vector<Real>& rkData, const std::vector<Real>& rkWeight );
	static Real Mean4( const std::vector<Real>& rkData, const std::vector<Real>& rkWeight );
	static Real MeanSqrt( const std::vector<Real>& rkData, const std::vector<Real>& rkWeight );
	static Real MeanSqrtSqrt( const std::vector<Real>& rkData, const std::vector<Real>& rkWeight );
	static Real Variance( const std::vector<Real>& rkData, Real tMean, const std::vector<Real>& rkWeight );
	static Real Skewness( const std::vector<Real>& rkData, Real tMean, Real tVariance, const std::vector<Real>& rkWeight );
	static Real Kurtosis( const std::vector<Real>& rkData, Real tMean, Real tVariance, const std::vector<Real>& rkWeight );

	static Real Sum( const std::vector<Real>& rkData );

	static Real Angle( const Vector3<Real>& rkV1, const Vector3<Real>& rkV2 );

	static Real ACos (Real tValue);
	static Real ASin (Real tValue);

	static Real Cot( Real tValue );

	static Real X2Test( 
		const std::vector<Real>& rkLHS, const std::vector<Real>& rkRHS );
	static Real L2Distance( 
		const std::vector<Real>& rkLHS, const std::vector<Real>& rkRHS );
	static std::vector<std::vector<Real>> Transpose( const std::vector<std::vector<Real>>& rkData );
	
	static const Real PI;
	static const Real HALF_PI;
};

#include "MiMath.inl"

template <class Real>
std::vector<Real> operator + ( const std::vector<Real>& rkLHS, const std::vector<Real>& rkRHS );
template <class Real>
std::vector<Real> operator - ( const std::vector<Real>& rkLHS, const std::vector<Real>& rkRHS );
template <class Real>
std::vector<Real> operator * ( const std::vector<Real>& rkData, Real tScalar );
template <class Real>
std::vector<Real> operator / ( const std::vector<Real>& rkLHS, Real tScalar );


typedef Math<double> Mathd;
typedef Math<float> Mathf;

}
#endif