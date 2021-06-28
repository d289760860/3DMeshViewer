#include "DataBaseItem.h"

modelItem::modelItem(const char* name, const char* time, const char* location, const char* nature, const char *remarks, int obj_num)
{
	qname = QString::fromLocal8Bit(name);
	qtime = QString::fromLocal8Bit(time);
	qlocation = QString::fromLocal8Bit(location);
	qnature = QString::fromLocal8Bit(nature);
	qremarks = QString::fromLocal8Bit(remarks);
	num = obj_num;
}

sceneItem::sceneItem(int iden,const char* pic_url, const char* type, const char* position, const char* remarks, const char* obj_name, int vertex_num)
{
	id = iden;
	qpic = QString::fromLocal8Bit(pic_url);
	qtype = QString::fromLocal8Bit(type);
	qposition = QString::fromLocal8Bit(position);
	qremarks = QString::fromLocal8Bit(remarks);
	qobj = QString::fromLocal8Bit(obj_name);
	ver_num = vertex_num;
}

vertexItem::vertexItem(int id, double val_x, double val_y, double val_z)
{
	identity = id;
	x = val_x;
	y = val_y;
	z = val_z;
}