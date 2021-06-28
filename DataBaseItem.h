#ifndef DATABASEITEM_H_
#define DATABASEITEM_H_

#include <QString>

class modelItem
{
public:
	friend class MainWindow;
	modelItem(const char* name, const char* time, const char* location, const char* nature, const char *remarks, int obj_num);
private:
	QString qname;
	QString qtime;
	QString qlocation;
	QString qnature;
	QString qremarks;
	int num;
};

class sceneItem
{
public:
	friend class MainWindow;
	sceneItem(int id,const char* pic_url, const char* type, const char* position, const char* remarks, const char* obj_name, int vertex_num);
	bool operator<(const sceneItem& rhs) const { return id < rhs.id; }
	bool operator>(const sceneItem& rhs) const { return id > rhs.id; }
private:
	int id;
	QString qpic;
	QString qtype;
	QString qposition;
	QString qremarks;
	QString qobj;
	int ver_num;
};

class vertexItem
{
public:
	friend class MainWindow;
	vertexItem(int id, double val_x, double val_y, double val_z);
	bool operator<(const vertexItem& rhs) const { return identity < rhs.identity; }
	bool operator>(const vertexItem& rhs) const { return identity > rhs.identity; }
private:
	int identity;
	double x;
	double y;
	double z;
};


#endif