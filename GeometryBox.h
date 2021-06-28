
#ifndef GEOMETRYCube_H
#define GEOMETRYCube_H

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgUtil/SmoothingVisitor>

class GeometryCube : public osg::Geometry
{
public:
	GeometryCube( double dLength = 1, const osg::Vec4d& rkColor = osg::Vec4d( 1, 0, 0, 1 )  );

	void InitVertices();
	void AddFaces();

protected:
	osg::ref_ptr< osg::Vec3Array > m_spkVertices;
	osg::ref_ptr< osg::Vec3Array > m_spkNormals;
	osg::ref_ptr< osg::Vec4Array > m_spkColors;
	//osg::Vec4d m_kColor;
	double m_dLength;
};


#endif