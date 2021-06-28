
#ifndef PICKHANDLER_H
#define PICKHANDLER_H

#include <osg/Timer>
#include <osg/io_utils>
#include <osg/observer_ptr>

#include <osgUtil/IntersectionVisitor>
#include <osgUtil/PolytopeIntersector>
#include <osgUtil/LineSegmentIntersector>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>

#include <osgViewer/Viewer>

#include <osgFX/Scribe>

#include <iostream>

class OsgViewer;
class PickHandler : public osgGA::GUIEventHandler
{
public:

	PickHandler( OsgViewer* pkViewer );

	bool handle( const osgGA::GUIEventAdapter& rkEA, osgGA::GUIActionAdapter& rkAA );

	bool PickPoint( const osgGA::GUIEventAdapter& rkEA, osgViewer::Viewer* pkViewer );

protected:
	float _mx, _my;
	bool _usePolytopeIntersector;
	bool _useWindowCoordinates;
	OsgViewer* m_pkViewer;
};

#endif