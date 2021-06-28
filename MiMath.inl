

//------------------------------------------------------------------------------
template <class Real>
bool Math<Real>::Equal( Real tLHS, Real tRHS )
{
	if( abs(tLHS-tRHS) < ms_tPresicion )
	{
		return true;
	}
	return false;
};
//------------------------------------------------------------------------------
template <class Real>
bool Math<Real>::GreaterEqual( Real tLHS, Real tRHS )
{
	return Equal( tLHS, tRHS ) || tLHS > tRHS;
};
//------------------------------------------------------------------------------
template <class Real>
bool Math<Real>::LessEqual( Real tLHS, Real tRHS )
{
	return Equal( tLHS, tRHS ) || tLHS < tRHS;
};
//------------------------------------------------------------------------------
template <class Real>
bool Math<Real>::Greater( Real tLHS, Real tRHS )
{
	return !Equal( tLHS, tRHS ) && tLHS > tRHS;
};
//------------------------------------------------------------------------------
template <class Real>
bool Math<Real>::Less( Real tLHS, Real tRHS )
{
	return !Equal( tLHS, tRHS ) && tLHS < tRHS;
};
//------------------------------------------------------------------------------
template <class Real>
std::vector<Real> Math<Real>::ZScoreNormalization( const std::vector<Real>& rkData )
{
	std::vector<Real> kResult;
	Real tStandardDeviation = 0;
	Real tAverage = 0;
	Real tSum = 0; 
	for( int i = 0; i < rkData.size(); i++ )
	{
		tSum += rkData[i];
	}
	tAverage = tSum / rkData.size();
	for( int i = 0; i < rkData.size(); i++ )
	{
		tSum += (rkData[i]-tAverage) * ( rkData[i]-tAverage);
	}
	tSum /= rkData.size();
	tStandardDeviation = sqrt( tSum );
	for( int i = 0; i < rkData.size(); i++ )
	{
		kResult.push_back( (rkData[i]-tAverage)/tStandardDeviation );
	}
	return kResult;
}
//------------------------------------------------------------------------------
template <class Real>
std::vector<Real> Math<Real>::MinMaxNormalization( const std::vector<Real>& rkData )
{
	std::vector<Real> kResult;
	if( rkData.empty() )
	{
		return kResult;
	}
	Real tMin = rkData[0];
	Real tMax = rkData[0];
	for( int i = 0; i < rkData.size(); i++ )
	{
		if( rkData[i] > tMax )
			tMax = rkData[i];
		if( rkData[i] < tMin )
			tMin = rkData[i];
	}
	for( int i = 0; i < rkData.size(); i++ )
	{
		kResult.push_back( (rkData[i]-tMin)/(tMax-tMin) );
	}
	return kResult;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::RGB2HSV( const Vector3<Real>& rkRGB, bool bProj = false )
{
	Vector3<Real> kRGB = rkRGB;
	if( !bProj )
	{
		kRGB /= 255.0f;
	}

	Real tMax = kRGB[0];
	Real tMin = kRGB[0];
	int iMaxIndex = 0;
	for( int i = 1; i < 3; i++ )
	{
		if( kRGB[i] > tMax )
		{
			iMaxIndex = i;
			tMax = kRGB[i];
		}
		if( kRGB[i] < tMax )
		{
			tMin = kRGB[i];
		}
	}
	Vector3<Real> kHSV;

	if( Equal( tMax, tMin ) )
	{
		kHSV[0] = 0;
	}
	else if( iMaxIndex == 0 && kRGB[1] >= kRGB[2] )
	{
		kHSV[0] = 60 * (kRGB[1]-kRGB[2]) / (tMax-tMin);
	}
	else if( iMaxIndex == 0 && kRGB[1] < kRGB[2] )
	{
		kHSV[0] = 60 * (kRGB[1]-kRGB[2]) / (tMax-tMin) + 360;
	}
	else if( iMaxIndex == 1 )
	{
		kHSV[0] = 60 * (kRGB[2]-kRGB[0]) / (tMax-tMin) + 120;
	}
	else if( iMaxIndex == 2 )
	{
		kHSV[0] = 60 * (kRGB[0]-kRGB[1]) / (tMax-tMin) + 240;
	}
	if( Equal( tMax, 0 ) )
		kHSV[1] = 0;
	else
		kHSV[1] = (tMax-tMin)/tMax;
	kHSV[2] = tMax;

	if( GreaterEqual( kHSV[0], 360 ) )
	{
		kHSV[0] = 360;
	}
	if( LessEqual( kHSV[0], 0 ) )
	{
		kHSV[0] = 0;
	}
	for( int i = 1; i < 3; i++ )
	{
		if( GreaterEqual( kHSV[i], 1 ) )
		{
			kHSV[i] = 1;
		}
		if( LessEqual( kHSV[i], 0 ) )
		{
			kHSV[i] = 0;
		}
	}

	return kHSV;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::RGB2HSL( const Vector3<Real>& rkRGB, bool bProj = false )
{
	Vector3<Real> kRGB = rkRGB;
	if( !bProj )
	{
		kRGB /= 255.0f;
	}

	Real tMax = kRGB[0];
	Real tMin = kRGB[0];
	int iMaxIndex = 0;
	for( int i = 1; i < 3; i++ )
	{
		if( kRGB[i] > tMax )
		{
			iMaxIndex = i;
			tMax = kRGB[i];
		}
		if( kRGB[i] < tMax )
		{
			tMin = kRGB[i];
		}
	}
	Vector3<Real> kHSL;

	if( Equal( tMax, tMin ) )
	{
		kHSL[0] = 0;
	}
	else if( iMaxIndex == 0 && kRGB[1] >= kRGB[2] )
	{
		kHSL[0] = 60 * (kRGB[1]-kRGB[2]) / (tMax-tMin);
	}
	else if( iMaxIndex == 0 && kRGB[1] < kRGB[2] )
	{
		kHSL[0] = 60 * (kRGB[1]-kRGB[2]) / (tMax-tMin) + 360;
	}
	else if( iMaxIndex == 1 )
	{
		kHSL[0] = 60 * (kRGB[2]-kRGB[0]) / (tMax-tMin) + 120;
	}
	else if( iMaxIndex == 2 )
	{
		kHSL[0] = 60 * (kRGB[0]-kRGB[1]) / (tMax-tMin) + 240;
	}

	kHSL[2] = (tMax+tMin)*0.5f;
	if( Equal( kHSL[2], 0 ) || Equal( tMax, tMin ) )
	{
		kHSL[1] = 0;
	}
	else if( 0 < kHSL[2] && kHSL[2] <= 0.5 )
	{
		kHSL[1] = (tMax-tMin)/(tMax+tMin);
	}
	else if( kHSL[2] > 0.5 )
	{
		kHSL[1] = (tMax-tMin)/(2-(tMax+tMin));
	}

	if( GreaterEqual( kHSL[0], 360 ) )
	{
		kHSL[0] = 360;
	}
	if( LessEqual( kHSL[0], 0 ) )
	{
		kHSL[0] = 0;
	}
	for( int i = 1; i < 3; i++ )
	{
		if( GreaterEqual( kHSL[i], 1 ) )
		{
			kHSL[i] = 1;
		}
		if( LessEqual( kHSL[i], 0 ) )
		{
			kHSL[i] = 0;
		}
	}

	return kHSL;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::HSV2RGB( const Vector3<Real>& rkHSV, bool bProj = false )
{
	Vector3<Real> kRGB;
	//int iHi = ((int)rkHSV[0])%60;
	int iHi = ((int)rkHSV[0])/60;
	Real tF = rkHSV[0]/60.0 - iHi;
	Real tP = rkHSV[2] * ( 1 - rkHSV[1] );
	Real tQ = rkHSV[2] * ( 1 - tF * rkHSV[1] );
	Real tT = rkHSV[2] * ( 1 - (1-tF) * rkHSV[1] );
	switch( iHi )
	{
	case 0:
		kRGB = Vector3<Real>( rkHSV[2], tT, tP );
		break;
	case 1:
		kRGB = Vector3<Real>( tQ, rkHSV[2], tP );
		break;
	case 2:
		kRGB = Vector3<Real>( tP, rkHSV[2], tT );
		break;
	case 3:
		kRGB = Vector3<Real>( tP, tQ, rkHSV[2] );
		break;
	case 4:
		kRGB = Vector3<Real>( tT, tP, rkHSV[2] );
		break;
	case 5:
		kRGB = Vector3<Real>( rkHSV[2], tP, tQ );
		break;
	}
	if( bProj )
	{
		for( int i = 0; i < 3; i++ )
		{
			if( GreaterEqual( kRGB[i], 1 ) )
			{
				kRGB[i] = 1;
			}
			if( LessEqual( kRGB[i], 0 ) )
			{
				kRGB[i] = 0;
			}
		}
	}
	else
	{
		for( int i = 0; i < 3; i++ )
		{
			kRGB[i] *= 255;
			if( GreaterEqual( kRGB[i], 255 ) )
			{
				kRGB[i] = 255;
			}
			if( LessEqual( kRGB[i], 0 ) )
			{
				kRGB[i] = 0;
			}
		}
	}
	return kRGB;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::HSL2RGB( const Vector3<Real>& rkHSL, bool bProj = false )
{
	Vector3<Real> kRGB;
	if( Equal( rkHSL[1], 0 ) )
	{
		kRGB[0] = rkHSL[2];
		kRGB[1] = rkHSL[2];
		kRGB[2] = rkHSL[2];
	}
	else
	{
		Real tQ = 0;
		if( rkHSL[2] < 0.5 )
		{
			tQ = rkHSL[2] * ( 1 + rkHSL[1] );
		}
		else
		{
			tQ = rkHSL[2] + rkHSL[1] - ( rkHSL[2] * rkHSL[1] );
		}
		Real tP = 2*rkHSL[2] - tQ;
		Vector3<Real> kT;
		kT[0] = rkHSL[0]/360.0f + 1/3.0f;
		kT[1] = rkHSL[0]/360.0f;
		kT[2] = rkHSL[0]/360.0f - 1/3.0f;
		for( int i = 0; i < 3; i++ )
		{
			if( kT[i] < 0 )
				kT[i] += 1;
			if( kT[i] > 1 )
				kT[i] -= 1;
		}
		for( int i = 0; i < 3; i++ )
		{
			if( kT[i] < 1/6.0f )
			{
				kRGB[i] = tP + (tQ-tP)*6*kT[i];
			}
			else if( 1/6.0f <= kT[i] && kT[i] < 1/2.0f )
			{
				kRGB[i] = tQ;
			}
			else if( 1/2.0f <= kT[i] && kT[i] < 2/3.0f )
			{
				kRGB[i] = tP + (tQ-tP)*6*(2/3.0f-kT[i]);
			}
			else
			{
				kRGB[i] = tP;
			}
		}
	}
	if( bProj )
	{
		for( int i = 0; i < 3; i++ )
		{
			if( GreaterEqual( kRGB[i], 1 ) )
			{
				kRGB[i] = 1;
			}
			if( LessEqual( kRGB[i], 0 ) )
			{
				kRGB[i] = 0;
			}
		}
	}
	else
	{
		for( int i = 0; i < 3; i++ )
		{
			kRGB[i] *= 255;
			if( GreaterEqual( kRGB[i], 255 ) )
			{
				kRGB[i] = 255;
			}
			if( LessEqual( kRGB[i], 0 ) )
			{
				kRGB[i] = 0;
			}
		}
	}
	return kRGB;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::RGB2XYZ( const Vector3<Real>& rkRGB, bool bProj = false )
{
	Vector3<Real> kRGB = rkRGB;
	if( !bProj )
	{
		kRGB /= 255.0;
	}

	Vector3<Real> kXYZ = kRGB;

	
	for( int i = 0; i < 3; i++ )
	{
		//Inverse sRGB Companding
		if( LessEqual( kXYZ[i], 0.04045 ) )
		{
			kXYZ[i] /= 12.92;
		}
		else
		{
			kXYZ[i] = pow( (kXYZ[i]+0.055)/1.055, 2.4 );
		}
		
		//Inverse Gamma Companding
		//kXYZ[i] = pow( kXYZ[i], 2.2 );
	}

	
	Matrix3<Real> kM;
	
	//D65 White
	kM[0][0] = 0.4124564; kM[0][1] = 0.3575761; kM[0][2] = 0.1804375;
	kM[1][0] = 0.2126729; kM[1][1] = 0.7151522; kM[1][2] = 0.0721750;
	kM[2][0] = 0.0193339; kM[2][1] = 0.1191920; kM[2][2] = 0.9503041;
	
	/*
	//D50 White
	kM[0][0] = 0.4360747; kM[0][1] = 0.3850649; kM[0][2] = 0.1430804;
	kM[1][0] = 0.2225045; kM[1][1] = 0.7168786; kM[1][2] = 0.0606169;
	kM[2][0] = 0.0139322; kM[2][1] = 0.0971045; kM[2][2] = 0.7141733;
	*/
	kXYZ = kM*kXYZ;

	return kXYZ;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::XYZ2LAB( const Vector3<Real>& rkXYZ, bool bProj = false )
{
	//D65 White
	Vector3<Real> kWhite( 0.9504, 1.0, 1.0889 );
	Vector3<Real> kRef;
	Vector3<Real> kLAB;
	Vector3<Real> kF;
	for( int i = 0; i < 3; i++ )
	{
		kRef[i] = rkXYZ[i] / kWhite[i];
		if( Greater( kRef[i], 0.008856 ) )
		//if( Greater( kRef[i], 216/(Real)24389 ) )
		{
			kF[i] = pow( kRef[i], 1/(Real)3.0 );
		}
		else
		{
			kF[i] = ( kRef[i]*903.3 + 16 ) / (Real)116.0;
			//kF[i] = ( kRef[i]*24389/(Real)27 + 16 ) / (Real)116;
		}
	}
	kLAB[0] = 116*kF[1] - 16;
	kLAB[1] = 500*( kF[0] - kF[1] );
	kLAB[2] = 200*( kF[1] - kF[2] );
	return kLAB;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::RGB2LAB( const Vector3<Real>& rkRGB, bool bProj = false )
{
	return XYZ2LAB( RGB2XYZ( rkRGB, bProj ), bProj );
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::LAB2LCH( const Vector3<Real>& rkLAB, bool bProj = false )
{
	Vector3<Real> kLCH;
	kLCH[0] = rkLAB[0];
	kLCH[1] = sqrt( rkLAB[1]*rkLAB[1] + rkLAB[2]*rkLAB[2] );
	kLCH[2] = atan2( rkLAB[2], rkLAB[1] )*180.0/3.1415926;
	//kLCH[2] = atan2( rkLAB[1], rkLAB[2] );
	if( kLCH[2] > 360 )
	{
		kLCH[2] -= 360;
	}
	else if( kLCH[2] < 0 )
	{
		kLCH[2] += 360;
	}
	return kLCH;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::XYZ2RGB( const Vector3<Real>& rkXYZ, bool bProj = false )
{
	Matrix3<Real> kM;

	//D65 White
	kM[0][0] = 3.2404542; kM[0][1] = -1.5371385; kM[0][2] = -0.4985314;
	kM[1][0] = -0.9692660; kM[1][1] = 1.8760108; kM[1][2] = 0.0415560;
	kM[2][0] = 0.0556434; kM[2][1] = -0.2040259; kM[2][2] = 1.0572252;

	Vector3<Real> kRGB = kM*rkXYZ;

	for( int i = 0; i < 3; i++ )
	{
		//Inverse sRGB Companding
		if( LessEqual( kRGB[i], 0.0031308 ) )
		{
			kRGB[i] *= 12.92;
		}
		else
		{
			kRGB[i] = pow( kRGB[i], 1/2.4 )*1.055 - 0.055;
		}

		//Inverse Gamma Companding
		//kRGB[i] = pow( kRGB[i], 1/2.2 );
	}

	if( bProj )
	{
		for( int i = 0; i < 3; i++ )
		{
			if( GreaterEqual( kRGB[i], 1 ) )
			{
				kRGB[i] = 1;
			}
			if( LessEqual( kRGB[i], 0 ) )
			{
				kRGB[i] = 0;
			}
		}
	}
	else
	{
		for( int i = 0; i < 3; i++ )
		{
			kRGB[i] *= 255;
			if( GreaterEqual( kRGB[i], 255 ) )
			{
				kRGB[i] = 255;
			}
			if( LessEqual( kRGB[i], 0 ) )
			{
				kRGB[i] = 0;
			}
		}
	}
	return kRGB;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::LAB2XYZ( const Vector3<Real>& rkLAB, bool bProj = false )
{
	//D65 White
	Vector3<Real> kWhite( 0.9504, 1.0, 1.0889 );
	Vector3<Real> kF;
	Vector3<Real> kRef;
	Vector3<Real> kXYZ;
	kF[1] = ( rkLAB[0] + 16 ) / (Real)116.0;
	kF[0] = rkLAB[1]/(Real)500 + kF[1];
	kF[2] = kF[1] - rkLAB[2]/(Real)200;
	for( int i = 0; i < 3; i++ )
	{
		if( i == 1 )
		{
			if( Greater( rkLAB[0], 0.008856*903.3 ) )
			{
				kRef[i] = pow( ( rkLAB[0] + 16 ) / (Real)116.0, 3 );
			}
			else
			{
				kRef[i] = rkLAB[0] / (Real)903.3;
			}
		}
		else
		{
			Real tValue = pow( kF[i], 3 );
			if( Greater( tValue, 0.008856 ) )
			{
				kRef[i] = tValue;
			}
			else
			{
				kRef[i] = (116*kF[i]-16)/(Real)903.3;
			}
		}


		kXYZ[i] = kRef[i] * kWhite[i];
	}
	return kXYZ;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::LAB2RGB( const Vector3<Real>& rkLAB, bool bProj = false )
{
	return XYZ2RGB( LAB2XYZ( rkLAB, bProj ), bProj );
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::LAB2AWH( const Vector3<Real>& rkLAB )
{
	Vector3<Real> kAWH;

	Vector3<Real> kLCH = LAB2LCH( rkLAB );
	Real tActivity = -2.1 + 0.06*sqrt( pow(rkLAB[0]-50,2)+pow(rkLAB[1]-3,2)+pow((rkLAB[2]-17)/1.4,2) );
	Real tWeight = -1.8 + 0.04*(100-rkLAB[0]) + 0.45*cos( (kLCH[2]-100)/180.0*3.1415926 );
	Real tHeat = -0.5 + 0.02 * pow( kLCH[1], 1.07 ) * cos( (kLCH[2]-50)/180.0*3.1415926 );

	kAWH[0] = tActivity;
	kAWH[1] = tWeight;
	kAWH[2] = tHeat;

	return kAWH;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::LABClamp( const Vector3<Real>& rkLAB )
{
	Vector3<Real> kRes = rkLAB;
	/*
	if( Less( kRes[0], 0 ) )
		kRes[0] = 0;
	else if( Greater( kRes[0], 100 ) )
		kRes[0] = 100;

	if( Less( kRes[1], -86.1739 ) )
		kRes[1] = -86.1739;
	else if( Greater( kRes[1], 98.2448 ) )
		kRes[1] = 98.2448;

	if( Less( kRes[2], -107.856 ) )
		kRes[2] = -107.856;
	else if( Greater( kRes[2], 94.4801 ) )
		kRes[2] = 94.4801;
		*/
	if( kRes[0] < 0 )
		kRes[0] = 0;
	else if( kRes[0] > 100 )
		kRes[0] = 100;

	if( kRes[1] < -86.1739 )
		kRes[1] = -86.1739;
	else if( kRes[1] > 98.2448 )
		kRes[1] = 98.2448;

	if( kRes[2] < -107.856 )
		kRes[2] = -107.856;
	else if( kRes[2] > 94.4801 )
		kRes[2] = 94.4801;
	return kRes;
}
//------------------------------------------------------------------------------
template<class Real>
Vector3<Real> Math<Real>::GetColor( int iBinIndex, int iMaxIndex )
{
	if( iBinIndex < 0 )
		return Vector3<Real>( 0, 0, 0 );
	
	Real tTemp = iBinIndex / (Real)iMaxIndex * (g_iBinNum-1);
	int iFloor = (int)floor( tTemp );
	int iCeil = (int)ceil( tTemp );
	double dSigma = tTemp - iFloor;
	Vector3<Real> kV1( g_aucColorMap[iCeil*3], g_aucColorMap[iCeil*3+1], g_aucColorMap[iCeil*3+2] );
	Vector3<Real> kV2( g_aucColorMap[iFloor*3], g_aucColorMap[iFloor*3+1], g_aucColorMap[iFloor*3+2] );
	Vector3<Real> kColor = dSigma*kV1 +	( 1.0 - dSigma ) * kV2;
	std::swap( kColor[0], kColor[2] );
	return kColor;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Mean( const std::vector<Real>& rkData )
{
	Real tMean = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tMean += rkData[i];
	}
	tMean /= (Real)rkData.size();
	return tMean;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Mean2( const std::vector<Real>& rkData )
{
	Real tSquaredMean = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tSquaredMean += rkData[i]*rkData[i];
	}
	tSquaredMean /= (Real)rkData.size();
	return tSquaredMean;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Mean4( const std::vector<Real>& rkData )
{
	Real tSquaredMean = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tSquaredMean += rkData[i]*rkData[i]*rkData[i]*rkData[i];
	}
	tSquaredMean /= (Real)rkData.size();
	return tSquaredMean;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Max( const std::vector<Real>& rkData )
{
	if( rkData.empty() )
		return 0;
	Real tMax = rkData[0];
	for( int i = 1; i < rkData.size(); i++ )
	{
		if( tMax < rkData[i] )
		{
			tMax = rkData[i];
		}
	}
	return tMax;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Max( const std::vector<std::vector<Real>>& rkData )
{
	if( rkData.empty() )
		return 0;
	Real tMax = Max(rkData[0]);
	for( int i = 1; i < rkData.size(); i++ )
	{
		Real tValue = Max( rkData[i] );
		if( tMax < tValue )
		{
			tMax = tValue;
		}
	}
	return tMax;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Min( const std::vector<Real>& rkData )
{
	if( rkData.empty() )
		return 0;
	Real tMin = rkData[0];
	for( int i = 1; i < rkData.size(); i++ )
	{
		if( tMin > rkData[i] )
		{
			tMin = rkData[i];
		}
	}
	return tMin;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Min( const std::vector<std::vector<Real>>& rkData )
{
	if( rkData.empty() )
		return 0;
	Real tMin = Min(rkData[0]);
	for( int i = 1; i < rkData.size(); i++ )
	{
		Real tValue = Max( rkData[i] );
		if( tMin < tValue )
		{
			tMin = tValue;
		}
	}
	return tMin;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::WeightedMean( 
	const std::vector<Real>& rkData, const std::vector<Real>& rkWeight )
{
	Real tWeight = 0;
	Real tMean = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tMean += rkData[i] * rkWeight[i];
		tWeight += rkWeight[i];
	}
	tMean /= tWeight;
	return tMean;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Median( const std::vector<Real>& rkData)
{
	if( rkData.empty() )
		return 0;
	std::vector<Real> kData = rkData;
	std::sort( kData.begin(), kData.end() );
	if( kData.size()%2 == 0)
	{
		return (kData[kData.size()/2-1]+kData[kData.size()/2])/2;
	}
	else
	{
		return kData[kData.size()/2];
	}
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Median( 
	const std::vector<Real>& rkData, const std::vector<Real>& rkWeight )
{
	if( rkData.empty() )
		return 0;
	vector<int> kSortedIndices = SortIndex( rkData );
	Real tWeight = 0;
	Real tWeightAcc = 0;
	for( int i = 0; i < rkWeight.size(); i++ )
	{
		tWeight += rkWeight[i];
	}
	int iIndex = 0;
	for( ; iIndex < rkWeight.size(); iIndex++ )
	{
		tWeightAcc += rkWeight[kSortedIndices[iIndex]]/tWeight;
		if( tWeightAcc >= 0.5 )
			break;
	}
	return rkData[kSortedIndices[iIndex]];
}
//------------------------------------------------------------------------------
template <class Real>
std::vector<int> Math<Real>::SortIndex( const std::vector<Real>& rkData ) 
{
	std::vector<int> kIndices( rkData.size() );
	for( int i = 0; i < rkData.size(); i++ )
	{
		kIndices[i] = i;
	}

	std::sort(
		begin(kIndices), end(kIndices),
		[&](int a, int b) { return rkData[a] < rkData[b]; }
	);
	return kIndices;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::Percentile( const std::vector<Real>& rkData, Real tPercentile )
{
	if( rkData.empty() )
		return 0;
	std::vector<Real> kData = rkData;
	std::sort( kData.begin(), kData.end() );
	return kData[ (int)floor( tPercentile*kData.size() ) ];
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::MeanSqrt( const std::vector<Real>& rkData )
{
	Real tMean = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tMean += sqrt( rkData[i] );
	}
	tMean /= (Real)rkData.size();
	return tMean;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::MeanSqrtSqrt( const std::vector<Real>& rkData )
{
	Real tMean = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tMean += sqrt( sqrt( rkData[i] ) );
	}
	tMean /= (Real)rkData.size();
	return tMean;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::Variance( const std::vector<Real>& rkData, Real tMean )
{
	Real tVariance = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tVariance += ( rkData[i] - tMean ) * ( rkData[i] - tMean );
	}
	tVariance /= (Real)rkData.size();
	return tVariance;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::Skewness( const std::vector<Real>& rkData, Real tMean, Real tVariance )
{
	Real tResult = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tResult += ( rkData[i] - tMean ) * ( rkData[i] - tMean ) * ( rkData[i] - tMean ); 
	}
	tResult /= rkData.size();
	tResult /= sqrt( tVariance*tVariance*tVariance + ms_tPresicion );
	return tResult;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::Kurtosis( const std::vector<Real>& rkData, Real tMean, Real tVariance )
{
	Real tResult = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tResult += 
			( rkData[i] - tMean ) * ( rkData[i] - tMean ) * 
			( rkData[i] - tMean ) * ( rkData[i] - tMean ); 
	}
	tResult /= rkData.size();
	tResult /= sqrt( tVariance*tVariance + ms_tPresicion );
	return tResult;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::Angle( const Vector3<Real>& rkV1, const Vector3<Real>& rkV2 )
{
	//Vector3<Real> kV1 = rkV1;
	//Vector3<Real> kV2 = rkV2;
	Real tCosPhi = rkV1.Dot( rkV2 );
	Real tSinPhi = (rkV1.Cross( rkV2 )).Length();
	return atan2( tSinPhi, tCosPhi ) * (180.0 / PI);
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Mean( const std::vector<Real>& rkData, const std::vector<Real>& rkWeight )
{
	Real tMean = 0;
	Real tWeight = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tMean += rkData[i] * rkWeight[i];
		tWeight += rkWeight[i];
	}
	tMean /= tWeight;
	return tMean;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Mean2( const std::vector<Real>& rkData, const std::vector<Real>& rkWeight )
{
	Real tSquaredMean = 0;
	Real tWeight = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tSquaredMean += rkData[i]*rkData[i]* rkWeight[i];
		tWeight += rkWeight[i];
	}
	tSquaredMean /= tWeight;
	return tSquaredMean;
}
//------------------------------------------------------------------------------
template<class Real>
Real Math<Real>::Mean4( const std::vector<Real>& rkData, const std::vector<Real>& rkWeight )
{
	Real tSquaredMean = 0;
	Real tWeight = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tSquaredMean += rkData[i]*rkData[i]*rkData[i]*rkData[i]* rkWeight[i];
		tWeight += rkWeight[i];
	}
	tSquaredMean /= tWeight;
	return tSquaredMean;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::MeanSqrt( const std::vector<Real>& rkData, const std::vector<Real>& rkWeight )
{
	Real tMean = 0;
	Real tWeight = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tMean += sqrt( rkData[i] ) * rkWeight[i];
		tWeight += rkWeight[i];
	}
	tMean /= tWeight;
	return tMean;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::MeanSqrtSqrt( const std::vector<Real>& rkData, const std::vector<Real>& rkWeight )
{
	Real tMean = 0;
	Real tWeight = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tMean += sqrt( sqrt( rkData[i] ) ) * rkWeight[i];
		tWeight += rkWeight[i];
	}
	tMean /= tWeight;
	return tMean;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::Variance( const std::vector<Real>& rkData, Real tMean, 
	const std::vector<Real>& rkWeight )
{
	Real tVariance = 0;
	Real tWeight = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tVariance += ( rkData[i] - tMean ) * ( rkData[i] - tMean ) * rkWeight[i];
		tWeight += rkWeight[i];
	}
	tVariance /= tWeight;
	return tVariance;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::Skewness( const std::vector<Real>& rkData, Real tMean, 
	Real tVariance, const std::vector<Real>& rkWeight )
{
	Real tResult = 0;
	Real tWeight = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tResult += ( rkData[i] - tMean ) * ( rkData[i] - tMean ) * ( rkData[i] - tMean ) * rkWeight[i]; 
		tWeight += rkWeight[i];
	}
	tResult /= tWeight;
	tResult /= sqrt( tVariance*tVariance*tVariance + ms_tPresicion );
	return tResult;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::Kurtosis( const std::vector<Real>& rkData, Real tMean, 
	Real tVariance, const std::vector<Real>& rkWeight )
{
	Real tResult = 0;
	Real tWeight = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tResult += 
			( rkData[i] - tMean ) * ( rkData[i] - tMean ) * 
			( rkData[i] - tMean ) * ( rkData[i] - tMean ) * rkWeight[i]; 
		tWeight += rkWeight[i];
	}
	tResult /= tWeight;
	tResult /= sqrt( tVariance*tVariance + ms_tPresicion );
	return tResult;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::ACos (Real fValue)
{
	if ( -(Real)1.0 < fValue )
	{
		if ( fValue < (Real)1.0 )
			return (Real)acos((double)fValue);
		else
			return (Real)0.0;
	}
	else
	{
		return PI;
	}
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::ASin (Real fValue)
{
	if ( -(Real)1.0 < fValue )
	{
		if ( fValue < (Real)1.0 )
			return (Real)asin((double)fValue);
		else
			return HALF_PI;
	}
	else
	{
		return -HALF_PI;
	}
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::Cot( Real tValue )
{
	return (Real)tan( HALF_PI-tValue );

}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::Sum( const std::vector<Real>& rkData )
{
	Real tSum = 0;
	for( int i = 0; i < rkData.size(); i++ )
	{
		tSum += rkData[i];
	}
	return tSum;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::X2Test( 
	const std::vector<Real>& rkLHS, const std::vector<Real>& rkRHS )
{
	assert( rkLHS.size() == rkRHS.size() );
	int iSize = std::min( rkLHS.size(), rkRHS.size() );
	Real tSum = 0;
	for( int i = 0; i < iSize; i++ )
	{
		Real tDenom = rkLHS[i]+rkRHS[i];
		if( tDenom != 0 )
		{
			tSum += (rkLHS[i]-rkRHS[i])*(rkLHS[i]-rkRHS[i])/tDenom;
		}
	}
	tSum /= (Real)2;
	return tSum;
}
//------------------------------------------------------------------------------
template <class Real>
Real Math<Real>::L2Distance( 
	const std::vector<Real>& rkLHS, const std::vector<Real>& rkRHS )
{
	assert( rkLHS.size() == rkRHS.size() );
	int iSize = std::min( rkLHS.size(), rkRHS.size() );
	Real tSum = 0;
	for( int i = 0; i < iSize; i++ )
	{
		tSum += (rkLHS[i]-rkRHS[i])*(rkLHS[i]-rkRHS[i]);
	}
	tSum = sqrt( tSum );
	return tSum;
}
//------------------------------------------------------------------------------
template <class Real>
std::vector<std::vector<Real>> Math<Real>::Transpose( const std::vector<std::vector<Real>>& rkData )
{
	if( rkData.empty() )
		return rkData;
	int iRow = rkData.size();
	int iCol = rkData[0].size();

	std::vector<std::vector<Real>> kResults( iCol, std::vector<Real>( iRow ) );
	for( int i = 0; i < iRow; i++ )
	{
		for( int j = 0; j < iCol; j++ )
		{
			kResults[j][i] = rkData[i][j];
		}
	}
	return kResults;
}
//------------------------------------------------------------------------------
template <class Real>
std::vector<Real> operator + ( const std::vector<Real>& rkLHS, const std::vector<Real>& rkRHS )
{
	assert( rkLHS.size() == rkRHS.size() );
	int iSize = std::min( rkLHS.size(), rkRHS.size() );
	std::vector<Real> kVector( iSize );
	for( int i = 0; i < iSize; i++ )
	{
		kVector[i] = rkLHS[i] + rkRHS[i];
	}
}
//------------------------------------------------------------------------------
template <class Real>
std::vector<Real> operator - ( const std::vector<Real>& rkLHS, const std::vector<Real>& rkRHS )
{
	assert( rkLHS.size() == rkRHS.size() );
	int iSize = std::min( rkLHS.size(), rkRHS.size() );
	std::vector<Real> kVector( iSize );
	for( int i = 0; i < iSize; i++ )
	{
		kVector[i] = rkLHS[i] - rkRHS[i];
	}
}
//------------------------------------------------------------------------------
template <class Real>
std::vector<Real> operator * ( const std::vector<Real>& rkData, Real tScalar )
{

	int iSize = rkData.size();
	std::vector<Real> kVector( iSize );
	for( int i = 0; i < iSize; i++ )
	{
		kVector[i] = rkData[i] * tScalar;
	}
	return kVector;
}
//------------------------------------------------------------------------------
template <class Real>
std::vector<Real> operator / ( const std::vector<Real>& rkData, Real tScalar )
{

	int iSize = rkData.size();
	std::vector<Real> kVector( iSize );
	for( int i = 0; i < iSize; i++ )
	{
		kVector[i] = rkData[i] / tScalar;
	}
	return kVector;
}
//------------------------------------------------------------------------------