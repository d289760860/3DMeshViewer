
#include "OsgViewer.h"

#include "osg/Light"
#include "osg/LightSource"
#include "PickHandler.h"
#include "GeometryBox.h"
#include <osg/MatrixTransform>
#include "MiMath.h"
#include "MiMatrix3.h"
#include <iostream>
#include "MiVector2.h"
#include "MiPolygon.h"
#include "ViewPortMoveEvent.h"
using namespace std;
//------------------------------------------------------------------------------
OsgViewer::OsgViewer(QWidget* parent, Qt::WindowFlags f, 
	osgViewer::ViewerBase::ThreadingModel threadingModel ) 
	: 
	QWidget(parent, f)
{
	setThreadingModel(threadingModel);
	// disable the default setting of viewer.done() by pressing Escape.
	setKeyEventSetsDone(0);
	/*
	QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readNodeFile("cow.osgt"));
	QWidget* widget2 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readNodeFile("glider.osgt"));
	QWidget* widget3 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readNodeFile("axes.osgt"));
	QWidget* widget4 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readNodeFile("fountain.osgt"));
	QWidget* popupWidget = addViewWidget(createGraphicsWindow(900, 100, 320, 240, "Popup window", true), osgDB::readNodeFile("dumptruck.osgt"));
	popupWidget->show();

	QGridLayout* grid = new QGridLayout;
	grid->addWidget(widget1, 0, 0);
	grid->addWidget(widget2, 0, 1);
	grid->addWidget(widget3, 1, 0);
	grid->addWidget(widget4, 1, 1);
	setLayout(grid);
	*/

	int maxNumLevels = 16;
    int targetNumIndicesPerLeaf = 16;
	osgDB::Registry::instance()->setBuildKdTreesHint(osgDB::ReaderWriter::Options::BUILD_KDTREES);

	m_dPickedPointScale = 0.005;
	PickedPointList = new osg::Vec3Array;


	//QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readNodeFile("Tile_14\\Tile_14.obj"));
	//QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), osgDB::readNodeFile("model.obj"));
	qDebug() << "osg test\n";
	QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), 0);
	qDebug() << "osg test_2\n";

	QGridLayout* grid = new QGridLayout;
	grid->addWidget(widget1, 0, 0);
	setLayout(grid);

	IsPicking = false;

	realize();

	connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
	_timer.start(10);
}
//------------------------------------------------------------------------------
QWidget * OsgViewer::addViewWidget(osgQt::GraphicsWindowQt * gw, osg::Node * scene)
{
	osgViewer::Viewer* view = new osgViewer::Viewer;
	addView(view);
	m_spkViewer = view;

	osg::Camera* camera = view->getCamera();
	camera->setGraphicsContext(gw);

	const osg::GraphicsContext::Traits* traits = gw->getTraits();

	//camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
	camera->setClearColor(osg::Vec4(220 / 255.f, 220 / 255.f, 220 / 255.f,0));

	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0f, 10000.0f);



	/*
	osg::ref_ptr<osg::Light> spkTopLight = new osg::Light;
	spkTopLight->setLightNum( 0 );
	spkTopLight->setPosition( osg::Vec4( 0.0, 0.0, 1.5, 1.0 ) );
	spkTopLight->setAmbient( osg::Vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	spkTopLight->setDiffuse( osg::Vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );

	osg::ref_ptr<osg::LightSource> spkLightSource = new osg::LightSource;
	spkLightSource->setLight( spkTopLight );
	spkLightSource->setLocalStateSetModes( osg::StateAttribute::ON );
	*/
		
	m_pkRoot = new osg::Group();

	osg::ref_ptr<osg::MatrixTransform> spkTransform = new osg::MatrixTransform;
	spkTransform->setMatrix( 
		osg::Matrix::scale( 1, 1, 1 ) );
	spkTransform->addChild( scene );

	//m_pkRoot->addChild( spkTransform.get() );
	//m_pkRoot->addChild( scene );

	/*
	osg::ref_ptr<osg::StateSet> spkStateSet = PickedGeode->getOrCreateStateSet();
	spkStateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
	spkStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	osg::ref_ptr<osg::PolygonMode> spkPolyMode = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	spkStateSet->setAttribute( spkPolyMode );
	*/
	
	m_spkPickedPointRoot = new osg::Group;

	m_pkRoot->addChild( m_spkPickedPointRoot.get() );

	/*
	spkTransform = new osg::MatrixTransform;
	spkTransform->setMatrix( 
		osg::Matrix::scale( 0.1, 0.1, 0.1 )*osg::Matrix::translate(osg::Vec3d( 0.5, 1, 0.5 )) );

	osg::ref_ptr<GeometryCube> spkCube = new GeometryCube;
	osg::ref_ptr<osg::Geode> spkGeode = new osg::Geode;
	spkGeode->addDrawable( spkCube.get() );

	spkTransform->addChild( spkGeode.get() );

	m_spkPickedPointRoot->addChild( spkTransform.get() );

	//osg::MatrixTransform* pkTransfrom = new osg::MatrixTransform;
	//pkTransfrom->addChild( spkTransform );

	m_pkRoot->addChild( m_spkPickedPointRoot.get() );
	*/
	view->setSceneData( m_pkRoot );
	view->addEventHandler(new osgViewer::StatsHandler);

	view->addEventHandler(new PickHandler(this));
	
	/* Change something here */
	view->setCameraManipulator(new ViewPortMoveEvent);
	//view->setCameraManipulator(new osgGA::MultiTouchTrackballManipulator);
	gw->setTouchEventsEnabled(true);
	/*
	for( int i = 0; i < 1000*1000; i++ )
	{

		osgUtil::LineSegmentIntersector* pkPicker =
			new osgUtil::LineSegmentIntersector(osgUtil::Intersector::MODEL, osg::Vec3d(0, 0, 0), osg::Vec3d(1, 1, 1));
		osgUtil::IntersectionVisitor kIV(pkPicker);
		view->getCamera()->accept(kIV);
		if (pkPicker->containsIntersections())
		{
			osgUtil::LineSegmentIntersector::Intersection kIntersection = pkPicker->getFirstIntersection();
		}
	}
	*/

	//FitPlane();
	//ComputeVolume();
	
	return gw->getGLWidget();
}
//------------------------------------------------------------------------------
osgQt::GraphicsWindowQt * OsgViewer::createGraphicsWindow(int x, int y, int w, int h, const std::string & name, bool windowDecoration)
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = ds->getNumMultiSamples();

	return new osgQt::GraphicsWindowQt(traits.get());
}
//------------------------------------------------------------------------------
void OsgViewer::paintEvent(QPaintEvent * event)
{
	frame();
}
//------------------------------------------------------------------------------
void OsgViewer::AddPickedPoint( const osg::Vec3d& rkPoint,bool flag )
{
	if (flag)
	{
		PickedPointList->push_back( rkPoint );
	}
	osg::ref_ptr<osg::MatrixTransform> spkTransform = new osg::MatrixTransform;
	spkTransform->setMatrix( 
		osg::Matrix::scale( m_dPickedPointScale, m_dPickedPointScale, m_dPickedPointScale ) *
		osg::Matrix::translate( rkPoint ) );

	osg::ref_ptr<GeometryCube> spkCube = new GeometryCube(1,osg::Vec4(1,0,0,0.2));
	osg::ref_ptr<osg::Geode> spkGeode = new osg::Geode;
	spkGeode->addDrawable( spkCube.get() );

	spkGeode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	spkGeode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);


	spkTransform->addChild( spkGeode.get() );

	m_spkPickedPointRoot->addChild( spkTransform.get() );


}
//------------------------------------------------------------------------------
void OsgViewer::FitPlane()
{
	/*
	ifstream kFile;
	kFile.open("Tmp.txt");

	while (kFile)
	{
		osg::Vec3d kPos;
		kFile >> kPos[0] >> kPos[1] >> kPos[2];
		if( !kFile )
			break;
		PickedPointList->push_back(kPos);
	}
	kFile.close();
	*/
	
	double dSumX = 0;
	double dSumY = 0;
	double dSumZ = 0;
	double dSumXX = 0;
	double dSumZZ = 0;
	double dSumXZ = 0;
	double dSumXY = 0;
	double dSumZY = 0;

	m_kX.clear();
	m_kY.clear();
	m_kZ.clear();
	for (int i = 0; i < PickedPointList->size(); i++)
	{
		osg::Vec3d kPos = PickedPointList->at(i);
		//osg::Vec3d kPos2 = kPos;
		//kPos[2] = kPos2[1];
		//kPos[1] = kPos2[2];

		m_kX.push_back(kPos[0]);
		m_kY.push_back(kPos[1]);
		m_kZ.push_back(kPos[2]);

		dSumX += kPos[0];
		dSumY += kPos[1];
		dSumZ += kPos[2];

		dSumXX += kPos[0] * kPos[0];
		dSumZZ += kPos[2] * kPos[2];
		dSumXZ += kPos[0] * kPos[2];
		dSumXY += kPos[0] * kPos[1];
		dSumZY += kPos[2] * kPos[1];
	}

	double dN = m_kX.size();
	Mi::Matrix3d kA;
	kA[0][0] = dSumXX; kA[0][1] = dSumXZ; kA[0][2] = dSumX;
	kA[1][0] = dSumXZ; kA[1][1] = dSumZZ; kA[1][2] = dSumZ;
	kA[2][0] = dSumX; kA[2][1] = dSumZ; kA[2][2] = dN;
	Mi::Vector3d kB( dSumXY, dSumZY, dSumY );
	Mi::Matrix3d kAInv = kA.Inverse();

	Mi::Vector3d kV = kAInv*kB;

	//kV.Normalize();

	m_dAx = kV[0];
	m_dBz = kV[1];
	m_dC = kV[2];

	m_kPlaneNormal[0] = m_dAx;
	m_kPlaneNormal[1] = -1;
	m_kPlaneNormal[2] = m_dBz;

}
//------------------------------------------------------------------------------
double OsgViewer::ComputeVolume()
{
	double dMinX = Mi::Mathd::Min( m_kX );
	double dMaxX = Mi::Mathd::Max( m_kX );
	double dMinZ = Mi::Mathd::Min( m_kZ );
	double dMaxZ = Mi::Mathd::Max( m_kZ );

	Mi::Vector3d kPlaneA( dMinX, m_dAx*dMinX+m_dBz*dMinZ+m_dC, dMinZ );
	Mi::Vector3d kPlaneB( dMaxX, m_dAx*dMaxX+m_dBz*dMinZ+m_dC, dMinZ);
	Mi::Vector3d kPlaneC( dMinX, m_dAx*dMinX+m_dBz*dMaxZ+m_dC, dMaxZ );
	Mi::Vector3d kN( m_kPlaneNormal[0], m_kPlaneNormal[1], m_kPlaneNormal[2] );

	std::vector<Mi::Vector2d> kPointList;
	for( int i = 0; i < PickedPointList->size(); i++ )
	{
		osg::Vec3d kPos = PickedPointList->at(i);
		Mi::Vector3d kPickedPoint( kPos[0], kPos[1], kPos[2] );
		double dT = (kN.Dot(kPickedPoint)+m_dC)/(kN.Dot(kN));
		Mi::Vector3d kPointOnPlane = kPickedPoint + dT * kN;
		
		kPointList.push_back( ComputeBarycentricCoordates( 
			kPlaneA, kPlaneB, kPlaneC, kPointOnPlane ) );
	}

	Mi::Polygon kPolygon;
	kPolygon.SetPoints( kPointList );
	//kPolygon.Generate( kPointList );

	osg::ref_ptr<osg::Vec3Array> kVertexList = new osg::Vec3Array;
	kVertexList->push_back( osg::Vec3d( dMinX, m_dAx*dMinX+m_dBz*dMinZ+m_dC, dMinZ ) );
	kVertexList->push_back( osg::Vec3d( dMinX, m_dAx*dMinX+m_dBz*dMaxZ+m_dC, dMaxZ ) );
	kVertexList->push_back( osg::Vec3d( dMaxX, m_dAx*dMaxX+m_dBz*dMaxZ+m_dC, dMaxZ ) );
	kVertexList->push_back( osg::Vec3d( dMaxX, m_dAx*dMaxX+m_dBz*dMinZ+m_dC, dMinZ ) );
	osg::ref_ptr<osg::Vec4Array> kColorList = new osg::Vec4Array;
	kColorList->push_back( osg::Vec4d( 0, 0, 1, 1 ) );
	osg::ref_ptr<osg::Vec3Array> kNormalList = new osg::Vec3Array;
	kNormalList->push_back( m_kPlaneNormal );
	osg::ref_ptr<osg::Geometry> spkGeometry = new osg::Geometry;
	spkGeometry->setVertexArray( kVertexList.get() );
	spkGeometry->setColorArray( kColorList.get() );
	spkGeometry->setColorBinding( osg::Geometry::BIND_OVERALL );
	spkGeometry->setNormalArray( kNormalList.get() );
	spkGeometry->setNormalBinding( osg::Geometry::BIND_OVERALL );
	spkGeometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );
	osg::ref_ptr<osg::Geode> spkGeode = new osg::Geode;
	spkGeode->addDrawable( spkGeometry.get() );
	m_pkRoot->addChild( spkGeode.get() );
	
	int iMicroUnit = 1000;
	double dXDelta = (dMaxX-dMinX)/iMicroUnit;
	double dZDelta = (dMaxZ-dMinZ)/iMicroUnit;

	Mi::Vector3d kP1 = Mi::Vector3d( dMinX, m_dAx*dMinX+m_dBz*dMinZ+m_dC, dMinZ );
	Mi::Vector3d kP2 = Mi::Vector3d( dMinX, m_dAx*dMinX+m_dBz*dMaxZ+m_dC, dMaxZ );
	Mi::Vector3d kP3 = Mi::Vector3d( dMaxX, m_dAx*dMaxX+m_dBz*dMaxZ+m_dC, dMaxZ );
	Mi::Vector3d kV1 = kP2 - kP1;
	Mi::Vector3d kV2 = kP3 - kP1;
	double dTotalArea = kV1.Cross( kV2 ).Length();
	double dMicroArea = dTotalArea/iMicroUnit/iMicroUnit;
	//ofstream kFile;
	//kFile.open( "Output.txt" );
	//kFile<<dTotalArea;
	//kFile.close();

	//ofstream kFile;
	//kFile.open( "Test.txt" );
	double dVolume = 0;
	for( int i = 0; i < iMicroUnit; i++ )
	{
		double dXPos = dMinX+dXDelta*(i+0.5);
		double dV = (iMicroUnit-(i+0.5))/((double)iMicroUnit);
		for( int j = 0; j < iMicroUnit; j++ )
		{
			double dU = (j+0.5)/((double)iMicroUnit);
			
			bool bFlag = kPolygon.IsIn( Mi::Vector2d( dU, dV ) );
			/*
			if( bFlag )
			{
				kFile<<1<<' ';
			}
			else
			{
				kFile<<0<<' ';
			}
			*/
			if( !bFlag )
				continue;

			double dZPos = dMinZ+dZDelta*(j+0.5);
			double dYPos = m_dAx*dXPos+m_dBz*dZPos+m_dC;
			/*
			Mi::Vector2d kUV = ComputeBarycentricCoordates( 
			kPlaneA, kPlaneB, kPlaneC, Mi::Vector3d( dXPos, dYPos, dZPos ) );
			bool bFlag = kPolygon.IsIn( kUV );
			kFile<<kUV[0]<<' ';
			
			if( bFlag )
			{
				kFile<<1<<' ';
			}
			else
			{
				kFile<<0<<' ';
			}
			*/
			osg::Vec3d kPos( dXPos, dYPos, dZPos );
			osg::Vec3d kTarget = kPos + m_kPlaneNormal*100;
			osgUtil::LineSegmentIntersector* pkPicker =
				new osgUtil::LineSegmentIntersector(osgUtil::Intersector::MODEL, kPos, kTarget);
			osgUtil::IntersectionVisitor kIV(pkPicker);
			m_spkViewer->getCamera()->accept(kIV);
			if (pkPicker->containsIntersections())
			{
				osgUtil::LineSegmentIntersector::Intersection kIntersection = pkPicker->getFirstIntersection();
				osg::Vec3d kIntersectPos = kIntersection.getLocalIntersectPoint();
				double dLength = (kIntersectPos-kPos).length();
				dVolume += dLength*dMicroArea;
			}
		}
		//kFile<<";"<<endl;
	}
	//kFile.close();
	return dVolume;
}
//------------------------------------------------------------------------------
Mi::Vector2d OsgViewer::ComputeBarycentricCoordates( const Mi::Vector3d& rkA, 
	const Mi::Vector3d& rkB, const Mi::Vector3d& rkC, const Mi::Vector3d& rkPoint )
{
	Mi::Vector3d kP = rkPoint;

	Mi::Vector3d kV0 = rkC - rkA;
	Mi::Vector3d kV1 = rkB - rkA;
	Mi::Vector3d kV2 = kP - rkA;

	double dDot00 = kV0.Dot( kV0 );
	double dDot01 = kV0.Dot( kV1 );
	double dDot02 = kV0.Dot( kV2 );
	double dDot11 = kV1.Dot( kV1 );
	double dDot12 = kV1.Dot( kV2 );

	double dInverDeno = 1.0f / ( dDot00*dDot11 - dDot01*dDot01 );
	double dU = ( dDot11*dDot02 - dDot01*dDot12 ) * dInverDeno;
	double dV = ( dDot00*dDot12 - dDot01*dDot02 ) * dInverDeno;


	return Mi::Vector2d( dV, dU );
}
//------------------------------------------------------------------------------
void OsgViewer::HighlightSelect(float fX1, float fY1, float fX2, float fY2)
{
	
	osg::Viewport* viewport = m_spkViewer->getCamera()->getViewport();
	fY1 = viewport->height() - fY1;
	fY2 = viewport->height() - fY2;

	float fXMin = osg::minimum(fX1, fX2);
	float fXMax = osg::maximum(fX1, fX2);
	float fYMin = osg::minimum(fY1, fY2);
	float fYMax = osg::maximum(fY1, fY2);


	//osg::Viewport* viewport = m_spkViewer->getCamera()->getViewport();
	//qDebug() << "Highlight viewport "<<viewport->x() << " " << viewport->y() << endl;

	//float fNXMin = viewport->x() + fXMin;
	//float fNXMax = viewport->x() + fXMax;
	//float fNYMin = viewport->y() + viewport->height()-fYMin;
	//float fNYMax = viewport->y() + viewport->height()-fYMax;
	//float fNXMin = viewport->x() + (fXMin/fWidth) * viewport->width();
	//float fNXMax = viewport->x() + (fXMax/fWidth) * viewport->width();
	//float fNYMin = viewport->y() + ((fHeight-fYMin)/fHeight) * viewport->height();
	//float fNYMax = viewport->y() + ((fHeight-fYMax)/fHeight) * viewport->height();



	osg::ref_ptr<osgUtil::PolytopeIntersector> spkPicker =
		new osgUtil::PolytopeIntersector(
		osgUtil::Intersector::WINDOW, fXMin, fYMin, fXMax, fYMax);

	m_dPickedPointScale = 0.05;
	osgUtil::IntersectionVisitor kIV(spkPicker.get());
	m_spkViewer->getCamera()->accept(kIV);
	if (spkPicker->containsIntersections())
	{
		for (osgUtil::PolytopeIntersector::Intersections::iterator hitr
			= spkPicker->getIntersections().begin();
			hitr != spkPicker->getIntersections().end();
		++hitr)
		{
			osg::Vec3d kPos = hitr->localIntersectionPoint;
			AddPickedPoint(kPos);
		}
	}

}
//------------------------------------------------------------------------------
