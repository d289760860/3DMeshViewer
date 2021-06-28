
#ifndef OSGVIEWER_H
#define OSGVIEWER_H

#include <QTimer>
#include <QApplication>
#include <QGridLayout>
#include<QDebug>

#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/MultiTouchTrackballManipulator>

#include <osgDB/ReadFile>

#include <osgQt/GraphicsWindowQt>

#include <iostream>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>

#include "MiVector3.h"
#include "MiVector2.h"


class OsgViewer : public QWidget, public osgViewer::CompositeViewer
{
public:
	OsgViewer(QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::CompositeViewer::SingleThreaded);


	QWidget* addViewWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene );

	osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false );

	virtual void paintEvent( QPaintEvent* event );

	void AddPickedPoint( const osg::Vec3d& rkPoint,bool flag=true );

	void FitPlane();
	double ComputeVolume();

	Mi::Vector2d ComputeBarycentricCoordates( const Mi::Vector3d& rkA,
		const Mi::Vector3d& rkB, const Mi::Vector3d& rkC, const Mi::Vector3d& rkPoint );

	void HighlightSelect(float fX1, float fY1, float fX2, float fY2);

public:

	osg::ref_ptr<osg::Vec3Array> PickedPointList;

	double m_dPickedPointScale;


	osg::ref_ptr<osg::Group> m_spkPickedPointRoot;

	bool IsPicking;

	double m_dAx;
	double m_dBz;
	double m_dC;
	osg::Vec3d m_kPlaneNormal;
	std::vector<double> m_kX;
	std::vector<double> m_kY;
	std::vector<double> m_kZ;

	osg::ref_ptr<osgViewer::Viewer> m_spkViewer;
	
	osg::ref_ptr<osg::Group> m_pkRoot;
	
	double aspectratio_width;
	double aspectratio_height;

protected:

	QTimer _timer;


};

#endif