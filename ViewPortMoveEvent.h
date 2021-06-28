
#ifndef VIEW_PORT_MOVE_EVENT_H
#define VIEW_PORT_MOVE_EVENT_H

#include <osgGA/MultiTouchTrackballManipulator>

class ViewPortMoveEvent : public osgGA::TrackballManipulator
{
public:
	ViewPortMoveEvent();
	~ViewPortMoveEvent();

	
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

	
	virtual bool handleMouseDrag(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

private:
	//���̰���
	void keyDown(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa);
	void keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa);

	//�϶��ӿڱ任����
	bool MyperformMovement();

private:
	bool _ctrl;//�Ƿ���ctrl
};

#endif