#include "DataBase.h"

int Connector::last_id = 0;
modelItem* Connector::modelit;
std::set<sceneItem> Connector::sceneit;
std::vector<vertexItem> Connector::vertexit;
//QPixmap Connector::picit;

Connector::Connector()
{
	int rc;
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		std::cout << "不能成功打开数据库：" << sqlite3_errmsg(db)<<std::endl;
		db = NULL;
	}
	else {
		std::cout<<"成功打开数据库。"<<std::endl;
	}
	modelit = NULL;
	sceneit.clear();
	vertexit.clear();
	//QDataStream::Qt_DefaultCompiledVersion;
	//QPixmap clearPix = QPixmap();
	//picit = clearPix;
}


bool Connector::connection_valid()
{
	if (db == NULL)
		return false;
	else
		return true;
}

void  Connector::update()
{
	if (connection_valid()==false) return;
}

Connector::~Connector()
{
	if (connection_valid() == true)
		sqlite3_close(db);
}

void Connector::show_all()
{
	if (connection_valid() == false) return;
	char * errMsg = NULL;
	char sql[255];
	char sql_utf8[255];
	sprintf(sql,"select * from models;");
	int(*callback) (void *NotUsed, int argc, char **argv, char **azColName);
	callback = func;
	ASCIIToUTF8(sql, sql_utf8);
	sqlite3_exec(db, sql_utf8, callback, 0, &errMsg);
	//std::cout << "flag" << std::endl;
}

void Connector::select_from_models(const char* modelname)
{
	if (connection_valid() == false) return;
	char * errMsg = NULL;
	char sql[255];
	char sql_utf8[255];
	sprintf(sql,
		"select * from models where name='%s';",
		modelname);
	//std::cout << sql<<std::endl;
	int(*callback) (void *NotUsed, int argc, char **argv, char **azColName);
	callback = select_model_callback;
	ASCIIToUTF8(sql, sql_utf8);
	sqlite3_exec(db, sql_utf8,callback, 0, &errMsg);
}

QImage Connector::select_from_image(int id)
{
	int nRet = ERROR;
	sqlite3_stmt* pstmt = NULL;
	char sql[125];
	sprintf(sql,
		"select * from image where scene_id=%d;",
		id);
	nRet = sqlite3_prepare_v2(db, sql, -1, &pstmt, NULL);
	/*
	if (nRet != SQLITE_OK)
	{
		return;
	}
	*/
	nRet = sqlite3_step(pstmt);
	/*
	if (nRet != SQLITE_ROW)
	{
		sqlite3_finalize(pstmt);
		return;
	}
	*/
	nRet = SQLITE_OK;
	const void* pV = sqlite3_column_blob(pstmt, 1);
	int len = sqlite3_column_bytes(pstmt, 1);
	QByteArray ba;
	ba.resize(len);
	memcpy(ba.data(), pV, len);
	//ba.fromRawData(pV, strlen(pV));
	QBuffer buffer(&ba);
	buffer.open(QIODevice::ReadOnly);
	QImageReader reader(&buffer, "PNG");
	QImage img = reader.read();
	sqlite3_finalize(pstmt);
	return img;
}

void Connector::select_from_vertex(int id)
{
	if (connection_valid() == false) return;
	char * errMsg = NULL;
	char sql[255];
	char sql_utf8[255];
	sprintf(sql,
		"select * from vertex where scene_id=%d;",
		id);
	//std::cout << sql<<std::endl;
	vertexit.clear();
	int(*callback) (void *NotUsed, int argc, char **argv, char **azColName);
	callback = select_vertex_callback;
	ASCIIToUTF8(sql, sql_utf8);
	sqlite3_exec(db, sql_utf8, callback, 0, &errMsg);
}


void Connector::select_from_scene(const char* modelname)
{
	if (connection_valid() == false) return;
	char * errMsg = NULL;
	char sql[255];
	char sql_utf8[255];
	sprintf(sql,
		"select * from scene where obj_name='%s';",
		modelname);
	//std::cout << sql<<std::endl;
	int(*callback) (void *NotUsed, int argc, char **argv, char **azColName);
	callback = select_scene_callback;
	ASCIIToUTF8(sql, sql_utf8);
	sceneit.clear();
	sqlite3_exec(db, sql_utf8, callback, 0, &errMsg);
}

void Connector::insert_into_models(const char* name, const  char* time, const  char* location, const  char* nature, const char *remarks, int obj_num)
{
	if (connection_valid() == false) return;
	char * errMsg = NULL;
	char sql[255];
	char sql_utf8[255];
	sprintf(sql, 
		"insert into models(name,case_time,case_location,case_nature,case_remarks,obj_num) values('%s','%s','%s','%s','%s',%d);",
		name, time,location,nature,remarks,obj_num);
	//std::cout << sql<<std::endl;
	ASCIIToUTF8(sql, sql_utf8);
	sqlite3_exec(db, sql_utf8,0,0, &errMsg);
	//std::cout << "flag"<<std::endl;
}

void Connector::insert_into_scene(const char* pic_url, const char* type, const char* position, const char* remarks, const char* obj_name, int vertex_num)
{
	if (connection_valid() == false) return;
	char * errMsg = NULL;
	char sql[255];
	char sql_utf8[255];
	sprintf(sql,
		"insert into scene(obj_pic_url,obj_type,obj_position,obj_remarks,obj_name,vertex_num) values ('%s','%s','%s','%s','%s',%d);",
		pic_url,type, position, remarks, obj_name,vertex_num);
	//std::cout << sql << std::endl;
	ASCIIToUTF8(sql, sql_utf8);
	sqlite3_exec(db, sql_utf8, 0, 0, &errMsg);
	//std::cout << "flag" << std::endl;
}

void Connector::insert_into_vertex(int id, double val_x, double val_y, double val_z)
{
	char sql[255];
	char sql_utf8[255];
	sprintf(sql,
		"insert into vertex(scene_id, val_x, val_y, val_z) values(%d, %f, %f, %f);",
		id, val_x, val_y, val_z);
	sqlite3_exec(db, sql, 0, 0, 0);
}

void Connector::insert_into_image(int id, QImage img)
{
	if (connection_valid() == false) return;
	char * errMsg = NULL;
	char sql[255]="insert into image values (:1, :2);";
	sqlite3_stmt * stmt = NULL;
	//sqlite3_prepare(db, sql, -1, &stmt, 0);
	QByteArray ba;
	QBuffer buffer(&ba);
	buffer.open(QIODevice::WriteOnly);
	img.save(&buffer, "PNG");
	int nRet = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (nRet != SQLITE_OK)
	{
		return;
	}
	sqlite3_bind_int(stmt, 1, id);
	int size = ba.size();
	int len = strlen(ba);
	sqlite3_bind_blob(stmt, 2, ba.data(), ba.size(), NULL);
	//sqlite3_bind_blob(stmt, 1, img, filesize, NULL);
	sqlite3_step(stmt);
}

int Connector::getLastInsertedId()
{
	if (connection_valid() == false) return -1;
	char * errMsg = NULL;
	char sql[255];
	char sql_utf8[255];
	sprintf(sql,
		"select last_insert_rowid() from scene;");
	//std::cout << sql << std::endl;
	ASCIIToUTF8(sql, sql_utf8);
	int(*callback) (void *NotUsed, int argc, char **argv, char **azColName);
	callback = func;
	sqlite3_exec(db, sql_utf8, callback, 0, &errMsg);
	//std::cout << "flag" << std::endl;
	return 0;
}

void Connector::begin()
{
	sqlite3_exec(db, "begin;", 0, 0, 0);
}

void Connector::commit()
{
	sqlite3_exec(db, "commit;", 0, 0, 0);
}

void Connector::delete_from_models(const char* name)
{
	if (connection_valid() == false) return;
	if (connection_valid() == false) return;
	char * errMsg = NULL;
	char sql[255];
	char sql_utf8[255];
	sprintf(sql,
		"delete from models where name = '%s';",
		name);
	//std::cout << sql << std::endl;
	ASCIIToUTF8(sql, sql_utf8);
	sqlite3_exec(db, sql_utf8, 0, 0, &errMsg);
	//std::cout << "flag" << std::endl;
}


void ASCIIToUTF8(char cACSII[], char cUTF8[]) 
{	
	//先将ASCII码转换为Unicode编码	
	int nlen= MultiByteToWideChar(CP_ACP,0,cACSII,-1,NULL,NULL);	
	wchar_t *pUnicode = new wchar_t[255];	
	memset(pUnicode,0,nlen*sizeof(wchar_t));	
	MultiByteToWideChar(CP_ACP,0,cACSII,-1,(LPWSTR)pUnicode,nlen);	
	std::wstring wsUnicode = pUnicode ;	
	//将Unicode编码转换为UTF-8编码	
	nlen = WideCharToMultiByte(CP_UTF8,0,wsUnicode.c_str(),-1,NULL,0,NULL,NULL);	
	WideCharToMultiByte(CP_UTF8,0,wsUnicode.c_str(),-1,cUTF8,nlen,NULL,NULL);
}

void UTF8ToASCII(char *cUTF8, char ASCII[]) {
	std::string str = cUTF8;	
	//先将UTF8编码转换为Unicode编码	
	int nLen = MultiByteToWideChar(CP_UTF8,0,str.c_str(),-1,NULL,0);	
	wchar_t *pwcUnicode = new wchar_t[nLen] ;	
	memset(pwcUnicode,0,nLen*sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8,0,str.c_str(),-1,(LPWSTR)pwcUnicode,nLen);	
	//将Unicode编码转换为ASCII编码	
	nLen = WideCharToMultiByte(CP_ACP,0,pwcUnicode,-1,NULL,0,NULL,NULL);	
	WideCharToMultiByte(CP_ACP,0,pwcUnicode,-1,ASCII,nLen,NULL,NULL);
}

int Connector::func(void *NotUsed, int argc, char **argv, char **azColName) {
	Connector::last_id = atoi(argv[0]);
	std::cout << azColName[0] << " is " << last_id << std::endl;
	return 0;
}

int Connector::output(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int Connector::select_model_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	if(argv[0]==NULL || argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[4] == NULL || argv[5] == NULL)
		modelit = NULL;
	else
	{
		char name[255];
		char time[25];
		char location[25];
		char nature[20];
		char remarks[150];
		UTF8ToASCII(argv[0], name);
		UTF8ToASCII(argv[1], time);
		UTF8ToASCII(argv[2], location);
		UTF8ToASCII(argv[3], nature);
		UTF8ToASCII(argv[4], remarks);
		modelit = new modelItem(name, time, location, nature, remarks, atoi(argv[5]));
		//std::cout << "select from models," << name << "|" << time << "|" << location
		//	<< "|" << nature << "|" << remarks << "|" << argv[5]  << std::endl;
	}
	return 0;
}

int Connector::select_scene_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	if (argv[0] != NULL && argv[1] != NULL && argv[2] != NULL && argv[3] != NULL && argv[4] != NULL && argv[5] != NULL && argv[6] != NULL)
	{
		char pic[255];
		char type[30];
		char position[70];
		char remarks[150];
		char name[255];
		UTF8ToASCII(argv[1], pic);
		UTF8ToASCII(argv[2], type);
		UTF8ToASCII(argv[3], position);
		UTF8ToASCII(argv[4], remarks);
		UTF8ToASCII(argv[5], name);
		sceneit.insert(sceneItem(atoi(argv[0]),pic,type,position,remarks,name,atoi(argv[6])));
		//std::cout << "select from scene," << argv[0] << "|" << pic << "|" << type 
		//	<< "|" << position << "|" << remarks << "|" << name << "|" << argv[6] << std::endl;
	}
	return 0;
}

int Connector::select_vertex_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	if (argv[0] != NULL && argv[1] != NULL && argv[2] != NULL && argv[3] != NULL)
	{
		vertexit.push_back(vertexItem(atoi(argv[0]), atof(argv[1]), atof(argv[2]), atof(argv[3])));
		//std::cout << "select from vertex,"<<argv[0]<<"|"<<argv[1]<< "|" << argv[2] << "|" << argv[3] << std::endl;
	}
	return 0;
}

/*
int Connector::select_image_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	if (argv[0] != NULL && argv[1] != NULL)
	{
		//QPixmap clearPix = QPixmap();
		//picit = clearPix;
		//picit.loadFromData(argv[1]);
	}
	return 0;
}
*/