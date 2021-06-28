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
	/// ��Word�ļ������sFile·��Ϊ�ջ��������µ�Word�ĵ�
	bool Open(QString sFile, bool bVisible = true);
	void save(QString sSavePath);
	void close(bool bSave = true);

	bool replaceText(QString sLabel, QString sText);
	bool replacePic(QString sLabel, QString sFile);

	
	//�����п�
	void setColumnWidth(QAxObject *table, int column, int width);

	//�ڱ��̶���Ԫ���ڲ�������
	void SetTableCellString(QAxObject *table, int row, int column, QString text);
	
	//�ڱ��̶���Ԫ���ڲ���ͼƬ
	void SetTableCellPic(QAxObject *table, int row, int column, QString file);


	//����һ�����м��б��
	QAxObject *insertTable(QString sLabel, int row, int column);
	//�����ض���񣬲����ñ�ͷ
	QAxObject *insertTable(QString sLabel, int num,QStringList headlist);

private:
	QAxObject *m_pWord;      //ָ������WordӦ�ó���
	QAxObject *m_pWorkDocument;   //ָ��m_sFile��Ӧ���ĵ�������Ҫ�������ĵ�
	QString m_sFile;
	bool m_bIsOpen;
	bool m_bNewFile;


};

#endif
