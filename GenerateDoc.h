#ifndef GENERATEDOC_H
#define GENERATEDOC_H

#include <QObject>
#include <QAxObject>
#include <QAxWidget>
#include <QtCore>

class GenerateDoc : public QObject
{
public:
	GenerateDoc();
	~GenerateDoc();
	/// 打开Word文件，如果sFile路径为空或错误，则打开新的Word文档
	bool Open(QString sFile, bool bVisible = true);
	void save(QString sSavePath);
	void close(bool bSave = true);

	bool replaceText(QString sLabel, QString sText);
	bool replacePic(QString sLabel, QString sFile);

	
	//设置列宽
	void setColumnWidth(QAxObject *table, int column, int width);

	//在表格固定单元格内插入文字
	void SetTableCellString(QAxObject *table, int row, int column, QString text);
	
	//在表格固定单元格内插入图片
	void SetTableCellPic(QAxObject *table, int row, int column, QString file);


	//插入一个几行几列表格
	QAxObject *insertTable(QString sLabel, int row, int column);
	//插入特定表格，并设置表头
	QAxObject *insertTable(QString sLabel, int num,QStringList headlist);

private:
	QAxObject *m_pWord;      //指向整个Word应用程序
	QAxObject *m_pWorkDocument;   //指向m_sFile对应的文档，就是要操作的文档
	QString m_sFile;
	bool m_bIsOpen;
	bool m_bNewFile;


};

#endif
