
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

#include <QRubberBand>    // ���ڴ���һ����Ƥ��ѡ��
#include <QDesktopWidget> // ���ڻ�ȡ��Ļ�ߴ�
#include <QMouseEvent>    // �������ڻ�ȡ����¼�
#include <QKeyEvent>	//�������ڻ�ȡ�����¼�
#include <QString>        // ��������<QDateTime> ���ڴ洢�ļ���
#include <windows.h>      // ����win32API
#include <QImage>         // ���ڴ���ͼƬ����
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
	//���ļ������в���ֻ���ڱ���Ż���Ч��Ҳ���ǲ�Ҫ�����������ڽ����ļ��Լ��ļ��в��������������ݲ�һ��
	ScreenShoot* instancec;
	ScreenShoot* instancea;
	QImage* capture_img;//ѡ�е�ͼƬ
	QRect selectedRect;//ѡ�еľ��ο�
	QVector<QVector<QPoint>> osg_vertices;//�洢ѡ������ĶԽ�����

	QVector<QVector<QString>> iteminfo;//��Ʒ��Ϣ
	QString objpath;
	int currentItemNum;//��ǰ��Ʒ����
	QVector<QImage> itemImg;//�洢��ȡ��ͼƬ
	QVector<int> deleteIndex;//�洢ɾ�����������
	QVector<QString> itemPos;

	QVector<QVector<osg::Vec3d>> itemPickedPointsPos;

	int openCount;//open����
	bool delete_last_flag;//�Ƿ���ɾ�����һ��

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

	QLabel* m_pkCaseTimelabel;//����ʱ��
	QLineEdit* m_pkCaseTime;

	QLabel* m_pkCaseNaturelabel;//��������
	QLineEdit* m_pkCaseNature;

	QLabel* m_pkCaseAddresslabel;//�����ص�
	QLineEdit* m_pkCaseAddress;

	QLabel* m_pkCaseRemarklabel;//������ע
	QTextEdit* m_pkCaseRemark;

	QLabel* m_pkCaseShotlabel;//����ͼʾ
	QLabel* m_pkCaseShot;

	QLabel* m_pkItemNumlabel;//������
	QComboBox* m_pkItemNum;

	QLabel* m_pkItemTypelabel;//��������
	QLineEdit* m_pkItemType;

	QLabel* m_pkItemRemarklabel;//���屸ע
	QTextEdit* m_pkItemRemark;

	QLabel* m_pkItemPoslabel;//��������
	QTextEdit* m_pkItemPos;//��������λ��

	//QPushButton* m_pkScaleButt;//��ӱ�ע
	/*
	QPushButton* m_pkScreenShotButt;//��ͼ
	QPushButton* m_pkAddItemButt;//���
	QPushButton* m_pkSaveButt;//����
	QPushButton* m_pkDeleteButt;//ɾ��
	QPushButton* m_pkChangeButt;//����
	*/

	QAction* m_pkScreenShotAction;//���Ľ�ͼ
	QAction* m_pkAddItemAction;//����
	QAction* m_pkNewAction;//�½�
	QAction* m_pkSaveAction;//����
	QAction* m_pkExporttxtAction;//����
	QAction* m_pkDeleteAction;//ɾ��
	QAction* m_pkGenerateDoc;//����doc�ĵ�
	QAction* m_pkHideDock;//����dock����
	QAction* m_pkShowDock;//��ʾdock����
	QAction* m_pkNewOBJ;//�½�����
	QAction* m_pkManageMark;//�����ע

	QAction* m_pkSaveShortAction;//�����ݼ�
	QAction* m_pkDeleteShortAction;//ɾ����ݼ�
	QAction* m_pkChangeShortAction;//���Ŀ�ݼ�

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
			return QSize(500, 900); // QdockWidget�ĳ�ʼ��С 
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
			setWindowTitle(QString::fromLocal8Bit("�Ժ�"));
			//setWindowFlags(Qt::CustomizeWindowHint |Qt::WindowCloseButtonHint);
			setLabelText(QString::fromLocal8Bit("���ڴ����У�����رճ���"));
			setCancelButtonText(QString::fromLocal8Bit("ȡ��"));
			setRange(0, 100);
		}
		//setValue(i);
		//close();
	};
};


#endif