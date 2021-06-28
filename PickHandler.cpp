
#include "PickHandler.h"
#include <Windows.h>
#include "OsgViewer.h"

//------------------------------------------------------------------------------
PickHandler::PickHandler( OsgViewer* pkViewer)
	:
_mx(0.0), _my(0.0),
_usePolytopeIntersector(false),
_useWindowCoordinates(false)
{
	m_pkViewer = pkViewer;
}
//------------------------------------------------------------------------------
bool PickHandler::handle( const osgGA::GUIEventAdapter& rkEA, osgGA::GUIActionAdapter& rkAA )
{
	osgViewer::Viewer* pkViewer = dynamic_cast<osgViewer::Viewer*>(&rkAA);
	if (!pkViewer) 
		return false;
	
	switch ( rkEA.getEventType() )
	{
		case(osgGA::GUIEventAdapter::RELEASE):
		{
			if( rkEA.getButton() == 1 )
			{
				if( m_pkViewer->IsPicking )
					PickPoint( rkEA, pkViewer );
			}
			return true;
		}
		default:
			return false;
	}
}
//------------------------------------------------------------------------------
bool PickHandler::PickPoint( const osgGA::GUIEventAdapter& rkEA, osgViewer::Viewer* pkViewer )
{

	osgUtil::LineSegmentIntersector* pkPicker;
	if (!_useWindowCoordinates)//
	{
		// use non dimensional coordinates - in projection/clip space
		pkPicker = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::PROJECTION, rkEA.getXnormalized(), rkEA.getYnormalized());
	}
	else {
		// use window coordinates
		// remap the mouse x,y into viewport coordinates.
		osg::Viewport* viewport = pkViewer->getCamera()->getViewport();
		float mx = viewport->x() + (int)((float)viewport->width()*(rkEA.getXnormalized()*0.5f + 0.5f));//x y×ø±ê
		float my = viewport->y() + (int)((float)viewport->height()*(rkEA.getYnormalized()*0.5f + 0.5f));
		std::cout << "pickhandler  "<<viewport->width() << " " << viewport->height() << " " << mx << " " << my << std::endl;
		std::cout <<"pickhandler " <<m_pkViewer->width() << " " << m_pkViewer->height() <<std::endl;
		pkPicker = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, mx, my);
	}
	osgUtil::IntersectionVisitor kIV( pkPicker );
	pkViewer->getCamera()->accept( kIV );
	if ( pkPicker->containsIntersections())
	{
		osgUtil::LineSegmentIntersector::Intersection kIntersection = pkPicker->getFirstIntersection();
		//osg::notify(osg::NOTICE) << "Picked " << kIntersection.localIntersectionPoint << std::endl;
		m_pkViewer->AddPickedPoint( kIntersection.localIntersectionPoint );
        return true;
	}
	return false;
}
//------------------------------------------------------------------------------