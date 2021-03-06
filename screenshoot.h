#ifndef SCREENSHOOT_H
#define SCREENSHOOT_H

#include <QWidget>
#include <QRubberBand>    // 用于创建一个橡皮筋选框
#include <QLabel>         // 动态显示截图区域尺寸
#include <QDateTime>      // 用当前系统时间动态生成截图的文件名
#include <QScreen>        // 用来截取全屏
#include <QDesktopWidget> // 用于获取屏幕尺寸
#include <QApplication>
#include <QPalette>       // 对话框的调色板，用于将图片设置为窗体背景
#include <QMouseEvent>    // 重载用于获取鼠标事件
#include <QString>        // 配合上面的<QDateTime> 用于存储文件名
#include <windows.h>      // 调用win32API
#include <QImage>         // 用于储存图片对象
#include <QDir>           // 用于获取当前程序目录，得到截图的路径
#include <QDesktopServices>  //配合 <QDir>  用系统浏览器打开图片
#include <QFile>           // 删除文件
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
	void mouseMoveEvent(QMouseEvent *e);      // 处理鼠标移动
	void mousePressEvent(QMouseEvent *e);     // 处理鼠标按下
	void mouseReleaseEvent(QMouseEvent *e);   // 处理鼠标释放
	void setbackground(int width, int height); // 初始化程序背景
	void grabScreen();                        // 根据选取截屏，保存并打开图片
	void setLabel();                          // 动态显示截图区域尺寸
	void keyPressEvent(QKeyEvent *e);         // 处理esc取消按键
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
	QPoint origin;                            // 记录鼠标按下坐标
	QPoint end;                               // 记录鼠标释放坐标
	QLabel* label;                            // 显示截图区域尺寸
	QImage* bg;                               // 记录全屏图片
	int g_width;                              // 屏幕宽度
	int g_height;                             // 屏幕高度
	static ScreenShoot* instancec;
	static ScreenShoot* instancea;
	QImage result_pic;
	QRect selectedRect;
	ScreenShoot();	
};

#endif // SCREENSHOOT_H
