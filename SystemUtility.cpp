
#include "SystemUtility.h"
#include <iostream>
#include <fstream>

using namespace Mi;
using namespace std;

namespace Mi
{

//------------------------------------------------------------------------------
double round( double r )
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}
//----------------------------------------------------------------------------
bool CreatePathFromFullPath( const char* acFullPath )
{
	char acPathName[1024] = { 0 };
	strcpy( acPathName , acFullPath );
	for( int i = strlen(acPathName)-1 ; i >= 0 ; i-- )
	{
		if( acPathName[i] == '/' || acPathName[i] == '\\' )
		{
			acPathName[i] = '\0';
			break;
		}
		else
		{
			acPathName[i] = '\0';
		}
	}
	if( acPathName[0] == '\0' )
		return false;
	char acCmd[1024] = { 0 };
	sprintf( acCmd , "@if not exist %s md %s" , acPathName, acPathName );
	for( int i = 0 ; i < strlen(acCmd) ; i++ )
	{
		if( acCmd[i] == '/' )
			acCmd[i] = '\\';
	}
	//system( "@echo off" );
	system( acCmd );
	return true;
}
//----------------------------------------------------------------------------
bool CreatePath( const char* acPathName ) 
{
	if( acPathName[0] == '\0' )
		return false;
	char acCmd[1024] = { 0 };
	sprintf( acCmd , "@if not exist %s md %s" , acPathName, acPathName );
	for( int i = 0 ; i < strlen(acCmd) ; i++ )
	{
		if( acCmd[i] == '/' )
			acCmd[i] = '\\';
	}
	//system( "@echo off" );
	system( acCmd );
	return true;
}
//------------------------------------------------------------------------------
vector<string> LoadFileList( const char* acFileName )
{
	ifstream kFile;
	kFile.open( acFileName );

	vector<string> kFileNames;
	string kPathName = GetPathName( acFileName );
	while( kFile )
	{
		char acFileName[1024] = { 0 };
		kFile.getline( acFileName, 1024 );
		if( !kFile )
			break;
		if( acFileName[0] == 0 )
			continue;
		string kFileName = kPathName;
		kFileName += acFileName;
		kFileNames.push_back( kFileName );
	}
	kFile.close();
	return kFileNames;
}
//------------------------------------------------------------------------------
string GetPathName( const char* acFileName )
{
	char acPathName[1024] = { 0 };
	strcpy( acPathName , acFileName );
	for( int i = strlen(acPathName)-1 ; i >= 0 ; i-- )
	{
		if( acPathName[i] == '/' || acPathName[i] == '\\' )
		{
			acPathName[i+1] = '\0';
			break;
		}
		else
		{
			acPathName[i] = '\0';
		}
	}
	string kPathName = acPathName;
	if( kPathName.empty() )
		kPathName = ".";
	return kPathName;
}
//------------------------------------------------------------------------------
string GetFileName( const char* acFileName )
{
	char acPathName[1024] = { 0 };
	strcpy( acPathName , acFileName );
	string kFileName;
	for( int i = strlen(acPathName)-1 ; i >= 0 ; i-- )
	{
		if( acPathName[i] == '/' || acPathName[i] == '\\' )
		{
			acPathName[i+1] = '\0';
			break;
		}
		else
		{
			kFileName.push_back( acPathName[i] );
			acPathName[i+1] = '\0';
		}
	}
	for( int i = 0; i < kFileName.size()/2; i++ )
	{
		swap( kFileName[i], kFileName[kFileName.size()-1-i] );
	}
	return kFileName;
}
//------------------------------------------------------------------------------
string GetExtName( const char* acFileName )
{
	char acFileNameCopy[1024] = { 0 };
	int iIndex = strlen(acFileName)-1;
	for( ; iIndex > 0; iIndex-- )
	{
		if( acFileName[iIndex] == '.' )
		{
			break;
		}
	}
	string kExtName = "";
	for( int i = iIndex+1; i < strlen(acFileName); i++ )
	{
		if( acFileName[i] != 0 && acFileName[i] != ' ' )
		{
			kExtName.push_back( acFileName[i] );
		}
		else
		{
			break;
		}
	}
	return kExtName;
}
//------------------------------------------------------------------------------
string RemoveExtName( const char* acFileName )
{
	char acFileNameCopy[1024] = { 0 };
	strcpy_s( acFileNameCopy, 1024, acFileName );
	int iIndex = strlen(acFileName)-1;
	for( ; iIndex > 0; iIndex-- )
	{
		if( acFileNameCopy[iIndex] == '.' )
		{
			acFileNameCopy[iIndex] = 0;
			break;
		}
	}
	return acFileNameCopy;
}
//------------------------------------------------------------------------------
//std::ostream& operator << ( std::ostream& rkStream, const std::string& rkStr )
//{
//	return rkStream<<rkStr.c_str();
//}
//------------------------------------------------------------------------------
//std::istream& operator >> ( std::istream& rkStream, std::string& rkStr )
//{
//	char acStr[1024] = { 0 };
//	rkStream>>acStr;
//	rkStr = std::string( acStr );
//	return rkStream;
//}
//------------------------------------------------------------------------------


}