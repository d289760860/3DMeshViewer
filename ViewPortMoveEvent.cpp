#include "ViewPortMoveEvent.h"




void ViewPortMoveEvent::keyDown(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa)
{
	switch (ea.getKey())
	{

	case osgGA::GUIEventAdapter::KEY_Control_L:
	case osgGA::GUIEventAdapter::KEY_Control_R:
		_ctrl = true;
		break;
	}
}

void ViewPortMoveEvent::keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa)
{
	switch (ea.getKey())
	{
	case osgGA::GUIEventAdapter::KEY_Control_L:
	case osgGA::GUIEventAdapter::KEY_Control_R:
		_ctrl = false;
		break;
	default:
		break;
	}
}

bool ViewPortMoveEvent::handleMouseDrag(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
	if (_ctrl && ea.getButtonMask() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
	{
		addMouseEvent(ea);

		if (MyperformMovement())
			us.requestRedraw();

		us.requestContinuousUpdate(false);
		_thrown = false;

		return true;
	}
	else
	{
		return osgGA::TrackballManipulator::handleMouseDrag(ea, us);
	}

	return true;
}

bool ViewPortMoveEvent::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
	switch (ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYUP):
		keyUp(ea, us);
		break;

	case(osgGA::GUIEventAdapter::KEYDOWN):
		keyDown(ea, us);
		break;
	}

	return osgGA::TrackballManipulator::handle(ea, us);
}

ViewPortMoveEvent::ViewPortMoveEvent() :TrackballManipulator(DEFAULT_SETTINGS)
{
	_ctrl = false;
}


ViewPortMoveEvent::~ViewPortMoveEvent()
{

}

bool ViewPortMoveEvent::MyperformMovement()
{
	
	// return if less then two events have been added
	if (_ga_t0.get() == NULL || _ga_t1.get() == NULL)
		return false;

	// get delta time
	double eventTimeDelta = _ga_t0->getTime() - _ga_t1->getTime();
	if (eventTimeDelta < 0.)
	{
		OSG_WARN << "Manipulator warning: eventTimeDelta = " << eventTimeDelta << std::endl;
		eventTimeDelta = 0.;
	}

	// get deltaX and deltaY
	float dx = _ga_t0->getXnormalized() - _ga_t1->getXnormalized();
	float dy = _ga_t0->getYnormalized() - _ga_t1->getYnormalized();

	// return if there is no movement.
	if (dx == 0. && dy == 0.)
		return false;

	float scale = -0.3f*_distance;

	osg::Matrix rotation_matrix;
	rotation_matrix.makeRotate(_rotation);

	osg::Vec3 dv(dx*scale, dy*scale, 0.0f);

	_center += dv * rotation_matrix;
	return true;
	
}