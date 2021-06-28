#ifndef DATABASE_H
#define DATABASE_H

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <vector>
#include <QPixmap>
#include <QBuffer>
#include <QImageReader>
#include "sqlite3.h"
#include "DataBaseItem.h"

void ASCIIToUTF8(char cACSII[], char cUTF8[]);
void UTF8ToASCII(char *cUTF8, char ASCII[]);

class Connector
{
public:
	friend class MainWindow;
	Connector();
	~Connector();
	void show_all();
	void update();
	void insert_into_models(const char* name , const char* time, const char* location, const char* nature, const char *remarks,int obj_num );
	void insert_into_scene(const char* pic_url, const char* type, const char* position, const char* remarks, const char* obj_name,int vertex_num);
	void insert_into_vertex(int id,double val_x,double val_y,double val_z);
	void insert_into_image(int id, QImage img);
	void delete_from_models(const char* name);
	void select_from_models(const char* modelname);
	void select_from_scene(const char* modelname);
	void select_from_vertex(int id);
	QImage select_from_image(int id);
	bool connection_valid();
	int getLastInsertedId();
	void begin();
	void commit();
private:
	sqlite3 *db;
	static modelItem* modelit;
	static std::set<sceneItem> sceneit;
	static std::vector<vertexItem> vertexit;
	//static QPixmap picit;
	static int last_id;
	static int func(void *NotUsed, int argc, char **argv, char **azColName);
	static int output(void *NotUsed, int argc, char **argv, char **azColName);
	static int select_model_callback(void *NotUsed, int argc, char **argv, char **azColName);
	static int select_scene_callback(void *NotUsed, int argc, char **argv, char **azColName);
	static int select_vertex_callback(void *NotUsed, int argc, char **argv, char **azColName);
	//static int select_image_callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif

/*
创建表：
create table models
(
name vchar(255) primary key,
case_time vchar(25),
case_location vchar(25),
case_nature vchar(20),
case_remarks vchar(150),
obj_num integer
);

create table scene
(
id integer primary key autoincrement,
obj_pic_url vchar(255),
obj_position vchar(70),
obj_remarks vchar(150),
obj_name vchar(255),
vertex_num integer,
foreign key (obj_name) references models (name)
);

create table vertex
(
scene_id  integer,
val_x float(4),
val_y float(4),
val_z float(4),
foreign key (scene_id) references scene (id)
);

设置级联删除规则：
CREATE TRIGGER object_delete AFTER DELETE
ON models
BEGIN
DELETE FROM scene WHERE obj_name = old.name;
END;

CREATE TRIGGER scene_delete AFTER DELETE
ON scene
BEGIN
DELETE FROM vertex WHERE scene_id = old.id;
END;

插入数据：
insert into models(name,case_time,case_location,case_nature,case_remarks,obj_num) values('testmodel','199.9.12','江','纵火','无',0);
insert into scene(obj_pic_url,obj_position,obj_remarks,obj_name,vertex_num) values ('D:/','地上','无评价','testmodel',0);
insert into vertex(scene_id,val_x,val_y,val_z) values(1,0.553,1.234,3.12);
*/