#ifndef SCREENSHOOT_H
#define SCREENSHOOT_H

#include <QWidget>
#include <QRubberBand>    // ���ڴ���һ����Ƥ��ѡ��
#include <QLabel>         // ��̬��ʾ��ͼ����ߴ�
#include <QDateTime>      // �õ�ǰϵͳʱ�䶯̬���ɽ�ͼ���ļ���
#include <QScreen>        // ������ȡȫ��
#include <QDesktopWidget> // ���ڻ�ȡ��Ļ�ߴ�
#include <QApplication>
#include <QPalette>       // �Ի���ĵ�ɫ�壬���ڽ�ͼƬ����Ϊ���屳��
#include <QMouseEvent>    // �������ڻ�ȡ����¼�
#include <QString>        // ��������<QDateTime> ���ڴ洢�ļ���
#include <windows.h>      // ����win32API
#include <QImage>         // ���ڴ���ͼƬ����
#include <QDir>           // ���ڻ�ȡ��ǰ����Ŀ¼���õ���ͼ��·��
#include <QDesktopServices>  //��� <QDir>  ��ϵͳ�������ͼƬ
#include <QFile>           // ɾ���ļ�
#include<QDebug>

class ScreenShoot : public QWidget
{
	Q_OBJECT

	Q_SIGNALS :
	void signalCompleteCature(QImage catureImage,QRect selectedrect);

public:
	ScreenShoot(QWidget *parent);
	~ScreenShoot();
	static ScreenShoot* InstanceChange()
	{
		if (!instancec)
			instancec = new ScreenShoot();
		return instancec;
	}
	static ScreenShoot* InstanceAdd()
	{
		if (!instancea)
			instancea = new ScreenShoot();
		return instancea;
	}
	void mouseMoveEvent(QMouseEvent *e);      // ��������ƶ�
	void mousePressEvent(QMouseEvent *e);     // ������갴��
	void mouseReleaseEvent(QMouseEvent *e);   // ��������ͷ�
	void setbackground(int width, int height); // ��ʼ�����򱳾�
	void grabScreen();                        // ����ѡȡ���������沢��ͼƬ
	void setLabel();                          // ��̬��ʾ��ͼ����ߴ�
	void keyPressEvent(QKeyEvent *e);         // ����escȡ������
	QImage getCapture()
	{
		return result_pic;
	}
	void show();
	QString getImgName()
	{
		return imgname;
	}
	void setImgName(QString objpath);
private:
	QString imgname;
	QRubberBand* g_rubber;
	QPoint origin;                            // ��¼��갴������
	QPoint end;                               // ��¼����ͷ�����
	QLabel* label;                            // ��ʾ��ͼ����ߴ�
	QImage* bg;                               // ��¼ȫ��ͼƬ
	int g_width;                              // ��Ļ���
	int g_height;                             // ��Ļ�߶�
	static ScreenShoot* instancec;
	static ScreenShoot* instancea;
	QImage result_pic;
	QRect selectedRect;
	ScreenShoot();	
};

#endif // SCREENSHOOT_H
