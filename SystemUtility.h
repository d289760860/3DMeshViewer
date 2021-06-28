
#ifndef SYSTEMUTILITY_H
#define SYSTEMUTILITY_H

#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <queue>

namespace Mi
{


#define SAFE_DELETE(p)	\
	if( p )	\
	{	\
		delete p;	\
		p = 0;	\
	}

#define SAFE_DELETE_ARRAY(a)	\
	if( a )	\
	{	\
		delete[] a;	\
		a = 0; \
	}


template <typename T>
void DeleteVectorElems( std::vector<T>& rkVector )
{
	for( int i = 0; i < rkVector.size(); i++ )
	{
		//delete rkVector[i];
		SAFE_DELETE( rkVector[i] );
	}
	rkVector.clear();
}

template <typename T1, typename T2>
void DeleteMapElems( std::map<T1,T2>& rkMap )
{
	for( std::map<T1,T2>::iterator kIt = rkMap.begin();
		kIt != rkMap.end(); kIt++ )
	{
		SAFE_DELETE( kIt->second );
	}
	rkMap.clear();
}

double round( double r );
bool CreatePathFromFullPath( const char* acFullPath );
bool CreatePath( const char* acPathName );
std::vector<std::string> LoadFileList( const char* acFileName );
std::string GetPathName( const char* acFileName );
std::string GetFileName( const char* acFileName );
std::string GetExtName( const char* acFileName );
std::string RemoveExtName( const char* acFileName );

#define VAR2STR(Var) #Var
#define COUTVAR(Var) std::cout<<#Var<<": "<<(Var)<<std::endl
#define MIPAUSE system("pause");
#define MITIME system("@echo %time%");

//------------------------------------------------------------------------------
//std::ostream& operator << ( std::ostream& rkStream, const std::string& rkStr );
//------------------------------------------------------------------------------
//std::istream& operator >> ( std::istream& rkStream, std::string& rkStr );
//------------------------------------------------------------------------------
template <class T>
std::ostream& operator << ( std::ostream& rkStream, const std::vector<T>& rkVector )
{
	rkStream<<rkVector.size()<<' ';
	for( int i = 0; i < rkVector.size(); i++ )
	{
		rkStream<<rkVector[i]<<' ';
	}
	return rkStream;
}
//------------------------------------------------------------------------------
template <class T>
std::istream& operator >> ( std::istream& rkStream, std::vector<T>& rkVector )
{
	rkVector.clear();
	int iSize;
	rkStream>>iSize;
	for( int i = 0; i < iSize; i++ )
	{
		T tValue;
		rkStream>>tValue;
		rkVector.push_back( tValue );
	}
	return rkStream;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T>
std::ostream& operator << ( std::ostream& rkStream, const std::set<T>& rkSet )
{
	rkStream<<rkSet.size();
	for( set<T>::iterator kIt = rkSet.begin();
		kIt != rkSet.end(); kIt++ )
	{
		rkStream<<' '<<(*kIt);
	}
	return rkStream;
}
//------------------------------------------------------------------------------
template <class T>
std::istream& operator >> ( std::istream& rkStream, std::set<T>& rkSet )
{
	rkSet.clear();
	int iSize;
	rkStream>>iSize;
	for( int i = 0; i < iSize; i++ )
	{
		T tValue;
		rkStream>>tValue;
		rkSet.insert( tValue );
	}
	return rkStream;
}
//------------------------------------------------------------------------------
template <typename T>
std::vector<int> SortIndex(std::vector<T> const& values) {
	std::vector<int> indices(values.size());
	for( int i = 0; i < values.size(); i++ )
	{
		indices[i] = i;
	}

	std::sort(
		begin(indices), end(indices),
		[&](int a, int b) { return values[a] < values[b]; }
	);
	return indices;
}
//------------------------------------------------------------------------------
template <class T1,class T2>
std::istream& operator >> ( std::istream& rkStream, std::pair<T1,T2>& rkPair )
{
	return rkStream>>rkPair.first>>rkPair.second;
}
//------------------------------------------------------------------------------
template <class T1,class T2>
std::ostream& operator << ( std::ostream& rkStream, const std::pair<T1,T2>& rkPair )
{
	return rkStream<<rkPair.first<<' '<<rkPair.second<<' ';
}
//------------------------------------------------------------------------------
enum ColorType
{
	CT_RGB = 1,
	CT_LAB = 2,
	CT_HSV = 3,
	CT_HSL = 4
};
//------------------------------------------------------------------------------

}

#endif