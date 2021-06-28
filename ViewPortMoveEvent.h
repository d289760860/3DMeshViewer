
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
	//键盘按键
	void keyDown(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa);
	void keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa);

	//拖动视口变换处理
	bool MyperformMovement();

private:
	bool _ctrl;//是否按下ctrl
};

#endif