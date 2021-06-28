#include "GeometryBox.h"

//------------------------------------------------------------------------------
GeometryCube::GeometryCube( double dLength /* = 1 */, 
	const osg::Vec4d& rkColor /* = osg::Vec4d( 1, 0, 0, 1 ) */ )
{
	m_dLength = dLength;
	m_spkColors = new osg::Vec4Array;
	m_spkColors->push_back( rkColor );

	InitVertices();
	AddFaces();
}
//------------------------------------------------------------------------------
void GeometryCube::InitVertices()
{
	double dHalfLength = m_dLength/2;
	m_spkVertices = new osg::Vec3Array;
	m_spkVertices->push_back(osg::Vec3d(-dHalfLength, -dHalfLength, dHalfLength));
	m_spkVertices->push_back(osg::Vec3d(dHalfLength, -dHalfLength, dHalfLength));
	m_spkVertices->push_back(osg::Vec3d(dHalfLength, dHalfLength, dHalfLength));
	m_spkVertices->push_back(osg::Vec3d(-dHalfLength, dHalfLength, dHalfLength));
	m_spkVertices->push_back(osg::Vec3d(-dHalfLength, -dHalfLength, -dHalfLength));
	m_spkVertices->push_back(osg::Vec3d(dHalfLength, -dHalfLength, -dHalfLength));
	m_spkVertices->push_back(osg::Vec3d(dHalfLength, dHalfLength, -dHalfLength));
	m_spkVertices->push_back(osg::Vec3d(-dHalfLength, dHalfLength, -dHalfLength));
}
//------------------------------------------------------------------------------
void GeometryCube::AddFaces()
{
	setVertexArray( m_spkVertices.get() );

	osg::ref_ptr< osg::DrawElementsUInt> spkQuad;
	spkQuad	= new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS, 0);
	spkQuad->push_back( 0 ); 
	spkQuad->push_back( 1 ); 
	spkQuad->push_back( 2 ); 
	spkQuad->push_back( 3 );
	addPrimitiveSet( spkQuad.get() );
	spkQuad	= new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS, 0);
	spkQuad->push_back( 1 ); 
	spkQuad->push_back( 5 ); 
	spkQuad->push_back( 6 ); 
	spkQuad->push_back( 2 );
	addPrimitiveSet( spkQuad.get() );
	spkQuad	= new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS, 0);
	spkQuad->push_back( 4 ); 
	spkQuad->push_back( 5 ); 
	spkQuad->push_back( 1 ); 
	spkQuad->push_back( 0 );
	addPrimitiveSet( spkQuad.get() );
	spkQuad	= new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS, 0);
	spkQuad->push_back( 4 ); 
	spkQuad->push_back( 0 ); 
	spkQuad->push_back( 3 ); 
	spkQuad->push_back( 7 );
	addPrimitiveSet( spkQuad.get() );
	spkQuad	= new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS, 0);
	spkQuad->push_back( 3 ); 
	spkQuad->push_back( 2 ); 
	spkQuad->push_back( 6 ); 
	spkQuad->push_back( 7 );
	addPrimitiveSet( spkQuad.get() );
	spkQuad	= new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS, 0);
	spkQuad->push_back( 5 ); 
	spkQuad->push_back( 4 ); 
	spkQuad->push_back( 7 ); 
	spkQuad->push_back( 6 );
	addPrimitiveSet( spkQuad.get() );

	m_spkNormals = new osg::Vec3Array;
	m_spkNormals->push_back( osg::Vec3d( 0, 0, 1 ) );
	m_spkNormals->push_back( osg::Vec3d( 1, 0, 0 ) );
	m_spkNormals->push_back( osg::Vec3d( 0, -1, 0 ) );
	m_spkNormals->push_back( osg::Vec3d( -1, 0, 0 ) );
	m_spkNormals->push_back( osg::Vec3d( 0, 1, 0 ) );
	m_spkNormals->push_back( osg::Vec3d( 0, 0, -1 ) );

	setNormalArray( m_spkNormals.get() );
	setNormalBinding( osg::Geometry::BIND_PER_PRIMITIVE_SET );

	setColorArray( m_spkColors.get() );
	setColorBinding( osg::Geometry::BIND_OVERALL );
}
//------------------------------------------------------------------------------