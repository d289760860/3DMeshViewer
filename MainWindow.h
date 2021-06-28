
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include<QLabel>
#include<QPushbutton>
#include<QTextEdit>
#include<QLineEdit>
#include<QComboBox>
#include<QTextCodec>
#include<QDebug>
#include<QFile>

#include <QRubberBand>    // 用于创建一个橡皮筋选框
#include <QDesktopWidget> // 用于获取屏幕尺寸
#include <QMouseEvent>    // 重载用于获取鼠标事件
#include <QKeyEvent>	//重载用于获取键盘事件
#include <QString>        // 配合上面的<QDateTime> 用于存储文件名
#include <windows.h>      // 调用win32API
#include <QImage>         // 用于储存图片对象
#include <QTextCodec>
#include <QDockWidget>
#include <QProgressDialog>
#include <QMainWindow>
#include "OsgViewer.h"
#include"screenshoot.h"
#include "DataBase.h"
#include "GenerateDoc.h"
#include "MarkManager.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* pkParent = 0);
	~MainWindow();
public:
	virtual void init();


private Q_SLOTS:
	void Open();
	void OpenDB();
	void StartPicking();
	void EndPicking();
	void ComputeVolume();
	void ChangeScreenshot();
	void onCompleteCaptureScreenshot(QImage img, QRect rect);
	void onCompleteCaptureBase(QImage capture_img, QRect rect);
	void onCompleteCaptureCreateNew(QImage capture_img, QRect rect);
	void Save();
	void addItems();
	void copyItem();
	void selectItem();
	void deleteItem();
	void changeItem(int index);
	void createNewItem();
	void GenerateDocument();
	void Exporttxt();
	void HideDock();
	void ShowDock();
	void NewObj();
	void ManageMarks();

private:
	//对文件的所有操作只有在保存才会生效，也就是不要在其他函数内进行文件以及文件夹操作，否则导致数据不一致
	ScreenShoot* instancec;
	ScreenShoot* instancea;
	QImage* capture_img;//选中的图片
	QRect selectedRect;//选中的矩形框
	QVector<QVector<QPoint>> osg_vertices;//存储选中物体的对角坐标

	QVector<QVector<QString>> iteminfo;//物品信息
	QString objpath;
	int currentItemNum;//当前物品个数
	QVector<QImage> itemImg;//存储截取的图片
	QVector<int> deleteIndex;//存储删除物体的索引
	QVector<QString> itemPos;

	QVector<QVector<osg::Vec3d>> itemPickedPointsPos;

	int openCount;//open次数
	bool delete_last_flag;//是否是删除最后一个

private:
	QPalette palette;
	QAction* m_pkOpenAction;
	QAction* m_pkOpenDBAction;
	QAction* m_pkStartPickAction;
	QAction* m_pkEndPickAction;
	QAction* m_pkComputeVolumeAction;
	//QAction* m_pkScreenShotAction;
	MarkManagerWindow * MarkManager;
	OsgViewer* m_pkViewer;
	QGridLayout *m_pkViewerLayout;
	QGridLayout *m_pkEditLayout;
	//QGridLayout *m_pkImgLayout;
	QGridLayout *m_pkMainLayout;
	QWidget* pkCentralWidget;
	GenerateDoc *generatedoc;

	QLabel* m_pkCaseTimelabel;//案发时间
	QLineEdit* m_pkCaseTime;

	QLabel* m_pkCaseNaturelabel;//案件性质
	QLineEdit* m_pkCaseNature;

	QLabel* m_pkCaseAddresslabel;//案发地点
	QLineEdit* m_pkCaseAddress;

	QLabel* m_pkCaseRemarklabel;//案件备注
	QTextEdit* m_pkCaseRemark;

	QLabel* m_pkCaseShotlabel;//物体图示
	QLabel* m_pkCaseShot;

	QLabel* m_pkItemNumlabel;//物体编号
	QComboBox* m_pkItemNum;

	QLabel* m_pkItemTypelabel;//物体类型
	QLineEdit* m_pkItemType;

	QLabel* m_pkItemRemarklabel;//物体备注
	QTextEdit* m_pkItemRemark;

	QLabel* m_pkItemPoslabel;//物体坐标
	QTextEdit* m_pkItemPos;//物体坐标位置

	//QPushButton* m_pkScaleButt;//添加标注
	/*
	QPushButton* m_pkScreenShotButt;//截图
	QPushButton* m_pkAddItemButt;//添加
	QPushButton* m_pkSaveButt;//保存
	QPushButton* m_pkDeleteButt;//删除
	QPushButton* m_pkChangeButt;//更改
	*/

	QAction* m_pkScreenShotAction;//更改截图
	QAction* m_pkAddItemAction;//复制
	QAction* m_pkNewAction;//新建
	QAction* m_pkSaveAction;//保存
	QAction* m_pkExporttxtAction;//保存
	QAction* m_pkDeleteAction;//删除
	QAction* m_pkGenerateDoc;//生成doc文档
	QAction* m_pkHideDock;//隐藏dock窗口
	QAction* m_pkShowDock;//显示dock窗口
	QAction* m_pkNewOBJ;//新建场景
	QAction* m_pkManageMark;//管理标注

	QAction* m_pkSaveShortAction;//保存快捷键
	QAction* m_pkDeleteShortAction;//删除快捷键
	QAction* m_pkChangeShortAction;//更改快捷键

	Connector* connector;
	int lastIndex;

	QString docfilename;
	QDockWidget* pDockWidget;
private:
	void displayImg(QImage* img);
	void initMenu();
	void initToolBar();
	void initShortcut();
	QByteArray Qstring2QByteArray(QString str);

	class MyWidget : public QWidget
	{
	public:
		QSize sizeHint() const
		{
			return QSize(500, 900); // QdockWidget的初始大小 
		}
	};

	class MyProcessDialog :public QProgressDialog
	{
	public:
		MyProcessDialog(QWidget * creator = 0) : QProgressDialog(creator)
		{
			setWindowModality(Qt::WindowModal);
			setMinimumDuration(0); 
			setAttribute(Qt::WA_DeleteOnClose, true); 
			setWindowTitle(QString::fromLocal8Bit("稍候"));
			//setWindowFlags(Qt::CustomizeWindowHint |Qt::WindowCloseButtonHint);
			setLabelText(QString::fromLocal8Bit("正在处理中，请勿关闭程序"));
			setCancelButtonText(QString::fromLocal8Bit("取消"));
			setRange(0, 100);
		}
		//setValue(i);
		//close();
	};
};


#endif