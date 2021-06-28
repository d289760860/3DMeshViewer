#include "MainWindow.h"
#include "OsgViewer.h"

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QScrollArea>
#include <QIcon>
#include <QToolBar>
#include <QFileDialog>
#include "MiMatrix3.h"

#include <Windows.h>

#include <iostream>
using namespace std;
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget* pkParent /* = 0 */)
	:
	QMainWindow(pkParent)
{
	qDebug() << "begin test";
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

	setWindowTitle(QString::fromLocal8Bit("江苏警院案件现场三维保存软件"));

	palette.setBrush(QPalette::Background, QBrush(QColor(255, 255, 255)));//红色
	setPalette(palette);

	initMenu();

	initToolBar();



	/*QMenu* pkEditMenu = menuBar()->addMenu(QString::fromLocal8Bit("编辑"));
	m_pkStartPickAction = new QAction( "Start Picking", this );
	connect( m_pkStartPickAction, &QAction::triggered, this, &MainWindow::StartPicking );
	pkEditMenu->addAction( m_pkStartPickAction );

	m_pkEndPickAction = new QAction( "End Picking", this );
	connect( m_pkEndPickAction, &QAction::triggered, this, &MainWindow::EndPicking );
	pkEditMenu->addAction( m_pkEndPickAction );
	m_pkEndPickAction->setDisabled( true );

	m_pkComputeVolumeAction = new QAction( "Compute Volume", this );
	connect( m_pkComputeVolumeAction, &QAction::triggered, this, &MainWindow::ComputeVolume );
	pkEditMenu->addAction( m_pkComputeVolumeAction );*/


	m_pkViewer = new OsgViewer(this);

	m_pkViewerLayout = new QGridLayout();
	m_pkViewerLayout->addWidget(m_pkViewer);

	m_pkEditLayout = new QGridLayout();

	QImage* timeimg = new QImage();
	timeimg->load("icons/rili.png");
	QImage tmp = timeimg->scaled(20, 20, Qt::KeepAspectRatioByExpanding);
	m_pkCaseTimelabel = new QLabel(QString::fromLocal8Bit("<img src = 'icons/rili.png' width='20' height='20' / >案发时间: "));
	//m_pkCaseTimelabel->setPixmap(QPixmap::fromImage(tmp));
	m_pkCaseTime = new QLineEdit;
	m_pkEditLayout->addWidget(m_pkCaseTimelabel, 0, 0);
	m_pkEditLayout->addWidget(m_pkCaseTime, 0, 1);

	m_pkCaseAddresslabel = new QLabel(QString::fromLocal8Bit("<img src = 'icons/dingwei.png' width='20' height='20' / >案发地点: "));
	m_pkCaseAddress = new QLineEdit;
	m_pkEditLayout->addWidget(m_pkCaseAddresslabel, 1, 0);
	m_pkEditLayout->addWidget(m_pkCaseAddress, 1, 1);

	m_pkCaseNaturelabel = new QLabel(QString::fromLocal8Bit("<img src = 'icons/shuju.png' width='20' height='20' / >案件性质: "));
	m_pkCaseNature = new QLineEdit;
	m_pkEditLayout->addWidget(m_pkCaseNaturelabel, 2, 0);
	m_pkEditLayout->addWidget(m_pkCaseNature, 2, 1);

	m_pkCaseRemarklabel = new QLabel(QString::fromLocal8Bit("<img src = 'icons/xinxi.png' width='20' height='20' / >案件备注: "));
	m_pkCaseRemark = new QTextEdit;
	m_pkEditLayout->addWidget(m_pkCaseRemarklabel, 3, 0);
	m_pkEditLayout->addWidget(m_pkCaseRemark, 3, 1);
	qDebug() << "textedit size :" << m_pkCaseRemark->width() << " " << m_pkCaseRemark->height() << endl;

	m_pkCaseShotlabel = new QLabel(QString::fromLocal8Bit("<img src = 'icons/tupian.png' width='20' height='20' / >物体图示: "));
	m_pkCaseShot = new QLabel;
	//m_pkImgLayout = new QGridLayout();
	//m_pkScaleButt = new QPushButton(QString::fromLocal8Bit("管理标注"));
	//m_pkImgLayout->addWidget(m_pkCaseShotlabel);
	//m_pkImgLayout->addWidget(m_pkScaleButt);
	//m_pkEditLayout->addLayout(m_pkImgLayout, 4, 0);
	m_pkEditLayout->addWidget(m_pkCaseShotlabel, 4, 0);
	m_pkEditLayout->addWidget(m_pkCaseShot, 4, 1);

	m_pkItemNumlabel = new QLabel(QString::fromLocal8Bit("<img src = 'icons/tiaoshi.png' width='20' height='20' / >物体编号: "));
	m_pkItemNum = new QComboBox;
	m_pkEditLayout->addWidget(m_pkItemNumlabel, 5, 0);
	m_pkEditLayout->addWidget(m_pkItemNum, 5, 1);

	m_pkItemTypelabel = new QLabel(QString::fromLocal8Bit("<img src = 'icons/biji.png' width='20' height='20' / >物体类型: "));
	m_pkItemType = new QLineEdit;
	m_pkEditLayout->addWidget(m_pkItemTypelabel, 6, 0);
	m_pkEditLayout->addWidget(m_pkItemType, 6, 1);

	m_pkItemPoslabel = new QLabel(QString::fromLocal8Bit("<img src = 'icons/sousuo.png' width='20' height='20' / >物体位置: "));
	m_pkItemPos = new QTextEdit;
	m_pkEditLayout->addWidget(m_pkItemPoslabel, 7, 0);
	m_pkEditLayout->addWidget(m_pkItemPos, 7, 1);

	m_pkItemRemarklabel = new QLabel(QString::fromLocal8Bit("<img src = 'icons/guanli.png' width='20' height='20' / >物体备注: "));
	m_pkItemRemark = new QTextEdit;
	m_pkEditLayout->addWidget(m_pkItemRemarklabel, 8, 0);
	m_pkEditLayout->addWidget(m_pkItemRemark, 8, 1);

	pDockWidget = new QDockWidget("Edit information", this);
	pDockWidget->setFeatures(QDockWidget::DockWidgetFloatable| QDockWidget::DockWidgetMovable);
	pDockWidget-> setAllowedAreas(Qt::AllDockWidgetAreas);
	MyWidget *m_pktmpWidget = new MyWidget();
	m_pktmpWidget->setLayout(m_pkEditLayout);
	pDockWidget->setWidget(m_pktmpWidget);

	m_pkMainLayout = new QGridLayout(this);
	m_pkMainLayout->setRowMinimumHeight(0, 800);
	m_pkMainLayout->setColumnMinimumWidth(0, 1280);
	m_pkMainLayout->setSpacing(10);
	m_pkMainLayout->addLayout(m_pkViewerLayout, 0, 0);
	//m_pkMainLayout->addLayout(m_pkEditLayout, 0, 1);
	//m_pkMainLayout->addWidget(pDockWidget,0,1);
	//pDockWidget->setLayout(m_pkEditLayout);

	pkCentralWidget = new QWidget(this);
	pkCentralWidget->setLayout(m_pkMainLayout);
	setCentralWidget(pkCentralWidget);
	this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, pDockWidget);
	
	currentItemNum = 0;

	//open次数
	openCount = 0;
	//是否是删除最后一个
	delete_last_flag = false;
	//截图数据
	capture_img = new QImage;
	//combobox选择

	connect(m_pkItemNum, SIGNAL(currentIndexChanged(int)), this, SLOT(selectItem()));
	//disconnect(m_pkItemNum, SIGNAL(currentIndexChanged(int)), this, SLOT(selectItem()));

	initShortcut();

	//g_width = m_pkViewer->width();
	//g_height = m_pkViewer->height();
	//qDebug() << g_height << " " << g_width << endl;
	connector = new Connector();
	lastIndex = 1;

	generatedoc = NULL;
	docfilename = QString::fromLocal8Bit("E:/MyFiles/homework/Projects/code/template.dot");
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	delete connector;
}

void MainWindow::OpenDB()
{
	objpath = QFileDialog::getOpenFileName(this, tr("Open Model"), ".", tr("Obj Files(*.obj)"));
	qDebug() << objpath << " and length is " << objpath.length() << endl;
	QByteArray ba = objpath.toLatin1();
	const char *c_str2 = ba.data();
	if (objpath.length() == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("选择模型"), QString::fromLocal8Bit("请选择模型!"));
		return;
	}
	//导入事先存储数据

	MyProcessDialog process(this);
	process.setValue(3);

	QFileInfo file_info = QFileInfo(objpath);
	QString file_name_info = file_info.fileName();
	QString imgname;

	connector->select_from_models(Qstring2QByteArray(file_name_info).data());

	connector->select_from_scene(Qstring2QByteArray(file_name_info).data());
	if (connector->modelit == NULL)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("选择模型"), QString::fromLocal8Bit("数据库中不存在此模型，请确认后重新选择。"));
		return;
	}
	if (openCount == 0)
	{
		m_pkViewer->m_pkRoot = new osg::Group();
		//		m_pkViewer->m_pkRoot->removeChildren(0,1);
		process.setValue(5);
		m_pkViewer->m_pkRoot->addChild(osgDB::readNodeFile(c_str2));
		process.setValue(20);
		m_pkViewer->m_spkViewer->setSceneData(m_pkViewer->m_pkRoot);
		m_pkViewer->m_spkPickedPointRoot = new osg::Group;
		m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());
	}
	else
	{
		m_pkViewer->m_pkRoot->removeChildren(openCount - 1, 1);
		process.setValue(5);
		m_pkViewer->m_pkRoot->addChild(osgDB::readNodeFile(c_str2));
		process.setValue(20);
		m_pkViewer->m_spkViewer->setSceneData(m_pkViewer->m_pkRoot);
		m_pkViewer->m_spkPickedPointRoot = new osg::Group;
		m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());

		m_pkCaseTime->clear();
		m_pkCaseNature->clear();
		m_pkCaseAddress->clear();
		m_pkCaseRemark->clear();
		m_pkItemNum->clear();
		m_pkItemType->clear();
		m_pkItemRemark->clear();
		m_pkItemPos->clear();
		m_pkCaseShot->clear();
	}
	
	openCount += 1;
	delete_last_flag = false;


	if (connector->modelit != NULL)
	{

		itemImg.clear();
		QVector<QImage> nullImg;
		itemImg.swap(nullImg);

		iteminfo.clear();
		QVector<QVector<QString>> nulliteminfo;
		iteminfo.swap(nulliteminfo);

		osg_vertices.clear();
		QVector<QVector<QPoint>> nullosg_vertices;
		osg_vertices.swap(nullosg_vertices);

		deleteIndex.clear();
		QVector<int> nulldeleteIndex;
		deleteIndex.swap(nulldeleteIndex);

		itemPos.clear();
		QVector<QString> nullPos;
		itemPos.swap(nullPos);


		//QTextStream in_pos(&file_pos);//pos
		//in_pos.setCodec("UTF-8");

		//QTextStream in_vertex(&file_vertex);//vertex pos
		//in_vertex.setCodec("UTF-8");

		//案发时间
		m_pkCaseTime->setText(connector->modelit->qtime);

		
		//案发地点
		m_pkCaseAddress->setText(connector->modelit->qlocation);

		//案件性质
		m_pkCaseNature->setText(connector->modelit->qnature);

		process.setValue(25);
		//案件备注
		m_pkCaseRemark->setText(connector->modelit->qremarks);

		//物体个数
		currentItemNum = connector->sceneit.size();
		process.setValue(30);

		int num = currentItemNum;
		int count = 0;
		QImage* img = NULL;
		while (count < num)
		{
			m_pkItemNum->addItem(QString::number(count + 1));
			count++;
		}
		count = 0;
		process.setValue(50);
		for (set<sceneItem>::iterator iter = connector->sceneit.begin(); iter != connector->sceneit.end(); iter++)
		{
			QVector<QString> temp;
			//物体类型
			temp.push_back(iter->qtype);
			//物体备注
			temp.push_back(iter->qremarks);
			iteminfo.append(temp);

			//pos
			itemPos.push_back(iter->qposition);

			////////////////+++++ChangeHere
			QImage imgFromDB = connector->select_from_image(iter->id);
			itemImg.push_back(imgFromDB);

			//vertex
			connector->select_from_vertex(iter->id);
			QVector<osg::Vec3d> vertex_temp;
			//std::cout << connector->vertexit.size();
			for (vector<vertexItem>::iterator verit = connector->vertexit.begin(); verit != connector->vertexit.end(); verit++)
			{
				vertex_temp.push_back(osg::Vec3d(verit->x, verit->y, verit->z));
			}
			itemPickedPointsPos.push_back(vertex_temp);
			count++;
		}
		process.setValue(70);

		if (iteminfo.size() > 0)
		{
			m_pkItemType->setText(iteminfo[0][0]);
			m_pkItemRemark->setText(iteminfo[0][1]);
		}
		//pos
		if (itemPos.size() > 0)
			m_pkItemPos->setText(itemPos[0]);

		//vertex pos
		if (itemPickedPointsPos.size() > 0)
		{
			m_pkViewer->m_pkRoot->removeChild(m_pkViewer->m_spkPickedPointRoot.get());
			m_pkViewer->m_spkPickedPointRoot.release();
			m_pkViewer->m_spkPickedPointRoot = new osg::Group;
			m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());
			qDebug() << "open highlight vertex " << itemPickedPointsPos[0].size() << endl;
			m_pkViewer->PickedPointList->clear();
			for (int i = 0; i < itemPickedPointsPos[0].size(); i++)
			{
				m_pkViewer->AddPickedPoint(itemPickedPointsPos[0][i], true);//不加入顶点
			}
		}

		process.setValue(78);
		//载入图像
		/*
		for (set<sceneItem>::iterator iter = connector->sceneit.begin(); iter != connector->sceneit.end(); iter++)
		{
			QImage temp;
			QString imgname_temp = iter->qpic;
			if (temp.load(imgname_temp))
			{
				itemImg.push_back(temp);
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("打开图像失败"), QString::fromLocal8Bit("物体图像缺失,请查看!"));
			}
		}
		*/
		process.setValue(90);
		/*
		QImage* img = new QImage;
		if (!img->load(imgname))
		{
			QMessageBox::information(this, QString::fromLocal8Bit("打开图像失败"), QString::fromLocal8Bit("没有物体图像!"));
			delete img;
		}
		else
			displayImg(img);
		*/
		if(itemImg.size()>0)
			img = &(itemImg[0]);
		displayImg(img);
		process.setValue(99);
	}

	else
	{
		itemImg.clear();
		QVector<QImage> nullImg;
		itemImg.swap(nullImg);

		iteminfo.clear();
		QVector<QVector<QString>> nulliteminfo;
		iteminfo.swap(nulliteminfo);

		osg_vertices.clear();
		QVector<QVector<QPoint>> nullosg_vertices;
		osg_vertices.swap(nullosg_vertices);

		deleteIndex.clear();
		QVector<int> nulldeleteIndex;
		deleteIndex.swap(nulldeleteIndex);

		itemPos.clear();
		QVector<QString> nullPos;
		itemPos.swap(nullPos);

		currentItemNum = 0;

		qDebug() << " file not exist " << itemImg.size() << endl;
		qDebug() << " file not exist " << currentItemNum << endl;



		m_pkCaseTime->clear();
		m_pkCaseNature->clear();
		m_pkCaseAddress->clear();
		m_pkCaseRemark->clear();
		m_pkItemNum->clear();
		m_pkItemType->clear();
		m_pkItemRemark->clear();
		m_pkItemPos->clear();
		m_pkCaseShot->clear();
		QMessageBox::information(this, QString::fromLocal8Bit("打开失败"), QString::fromLocal8Bit("模型不存在!"));

	}
	process.close();
}

//------------------------------------------------------------------------------
void MainWindow::Open()
{
	objpath = QFileDialog::getOpenFileName(this, tr("Open Model"), ".", tr("Obj Files(*.obj)"));
	qDebug() << objpath << " and length is " << objpath.length() << endl;
	QByteArray ba = objpath.toLatin1();
	const char *c_str2 = ba.data();
	if (objpath.length() == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("选择模型"), QString::fromLocal8Bit("请选择模型!"));
		return;
	}
	MyProcessDialog process(this);
	process.setValue(3);
	if (openCount == 0)
	{
		m_pkViewer->m_pkRoot = new osg::Group();

		m_pkViewer->m_pkRoot->removeChildren(0,1);
		process.setValue(5);
		m_pkViewer->m_pkRoot->addChild(osgDB::readNodeFile(c_str2));
		process.setValue(20);
		m_pkViewer->m_spkViewer->setSceneData(m_pkViewer->m_pkRoot);
		m_pkViewer->m_spkPickedPointRoot = new osg::Group;

		m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());
	}
	else
	{
		m_pkViewer->m_pkRoot->removeChildren(openCount - 1, 1);
		process.setValue(5);
		m_pkViewer->m_pkRoot->addChild(osgDB::readNodeFile(c_str2));
		process.setValue(20);
		m_pkViewer->m_spkViewer->setSceneData(m_pkViewer->m_pkRoot);
		m_pkViewer->m_spkPickedPointRoot = new osg::Group;

		m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());

		m_pkCaseTime->clear();
		m_pkCaseNature->clear();
		m_pkCaseAddress->clear();
		m_pkCaseRemark->clear();
		m_pkItemNum->clear();
		m_pkItemType->clear();
		m_pkItemRemark->clear();
		m_pkItemPos->clear();
		m_pkCaseShot->clear();
	}

	QString temppath = QFileDialog::getOpenFileName(this, tr("Open text"), ".", tr("txt Files(*.txt)"));

	openCount += 1;
	delete_last_flag = false;
	//导入事先存储数据
	QString filename(temppath);
	QString imgname(temppath);
	QString path = imgname.mid(0, temppath.size() - 4);
	imgname = path + "_" + QString::number(0) + "_.png";
	QString suffix = "txt";
	filename.replace(temppath.length() - 3, 3, suffix);

	QString posname(temppath);
	posname.replace(temppath.length() - 4, 4, "_pos." + suffix);

	QString vertexname(temppath);
	vertexname.replace(temppath.length() - 4, 7, "_vertex." + suffix);

	qDebug() << filename << endl;
	qDebug() << imgname << endl;
	qDebug() << vertexname << endl;

	QFile file(filename);
	QFile file_pos(posname);//pos
	QFile file_vertex(vertexname);//vertex pos
	process.setValue(30);
	if (file.exists())
	{
		//打开多个obj文件先提前置空
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			return;
		}
		if (!file_pos.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			return;
		}
		if (!file_vertex.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			return;
		}
		itemImg.clear();
		QVector<QImage> nullImg;
		itemImg.swap(nullImg);

		iteminfo.clear();
		QVector<QVector<QString>> nulliteminfo;
		iteminfo.swap(nulliteminfo);

		osg_vertices.clear();
		QVector<QVector<QPoint>> nullosg_vertices;
		osg_vertices.swap(nullosg_vertices);

		deleteIndex.clear();
		QVector<int> nulldeleteIndex;
		deleteIndex.swap(nulldeleteIndex);

		itemPos.clear();
		QVector<QString> nullPos;
		itemPos.swap(nullPos);

		QTextStream in(&file);
		in.setCodec("UTF-8");
		QString line = in.readLine();

		QTextStream in_pos(&file_pos);//pos
		in_pos.setCodec("UTF-8");

		QTextStream in_vertex(&file_vertex);//vertex pos
		in_vertex.setCodec("UTF-8");

		process.setValue(35);
		qDebug() << "file exists" << endl;
		while (!line.isEmpty())
		{
			qDebug() << line << endl;
			if (line.indexOf(QString::fromLocal8Bit("案发时间:")) != -1)
			{
				int pos = line.indexOf(":", 0);
				QString val = line.mid(pos + 1);
				m_pkCaseTime->setText(val);
			}
			else if (line.indexOf(QString::fromLocal8Bit("案发地点:")) != -1)
			{
				int pos = line.indexOf(":", 0);
				QString val = line.mid(pos + 1);
				m_pkCaseAddress->setText(val);
			}
			else if (line.indexOf(QString::fromLocal8Bit("案件性质:")) != -1)
			{
				int pos = line.indexOf(":", 0);
				QString val = line.mid(pos + 1);
				m_pkCaseNature->setText(val);
			}
			else if (line.indexOf(QString::fromLocal8Bit("案件备注:")) != -1)
			{
				int pos = line.indexOf(":", 0);
				QString val = line.mid(pos + 1);
				m_pkCaseRemark->setText(val);
			}
			else if (line.indexOf(QString::fromLocal8Bit("物体个数:")) != -1)
			{
				int pos = line.indexOf(":", 0);
				QString val = line.mid(pos + 1);
				int num = val.toInt();
				if (num < 0)
					num = 0;
				currentItemNum = num;
				qDebug() << num << endl;
				int count = 0;
				while (count < num)
				{
					m_pkItemNum->addItem(QString::number(count + 1));
					count++;
				}
				count = 0;

				while (count < num)
				{
					line = in.readLine();
					QVector<QString> temp;
					if (line.indexOf(QString::fromLocal8Bit("物体类型:")) != -1)
					{
						int pos = line.indexOf(":", 0);
						QString val = line.mid(pos + 1);
						temp.push_back(val);
					}
					line = in.readLine();
					if (line.indexOf(QString::fromLocal8Bit("物体备注:")) != -1)
					{
						int pos = line.indexOf(":", 0);
						QString val = line.mid(pos + 1);
						temp.push_back(val);
					}
					iteminfo.append(temp);

					//pos
					QString line_pos = in_pos.readLine();
					if (!line_pos.isEmpty())
					{
						QString str = QString::fromLocal8Bit("物体") + QString::number(count + 1) + ":";
						if (line_pos.indexOf(str) != -1)
						{
							int pos = line_pos.indexOf(":", 0);
							QString val = line_pos.mid(pos + 1);
							itemPos.push_back(val);
						}
					}

					//vertex
					QString line_vertex = in_vertex.readLine();
					if (!line_vertex.isEmpty())
					{
						QString str = QString::fromLocal8Bit("物体") + QString::number(count + 1) + ":";
						if (line_vertex.indexOf(str) != -1)
						{
							int pos = line_vertex.indexOf(":", 0);
							QString val = line_vertex.mid(pos + 1);
							int vertex_num = val.toInt();
							QVector<osg::Vec3d> vertex_temp;
							qDebug() << "open vertex " << vertex_num << endl;
							for (int k = 0; k < vertex_num; k++)
							{
								line_vertex = in_vertex.readLine();
								QStringList vertex = line_vertex.split(',', QString::SkipEmptyParts);
								vertex_temp.push_back(osg::Vec3d(vertex.at(0).toDouble(), vertex.at(1).toDouble(), vertex.at(2).toDouble()));
							}
							itemPickedPointsPos.push_back(vertex_temp);
						}
					}
					count++;
				}
			}
			line = in.readLine();
		}
		
		process.setValue(80);

		if (iteminfo.size() > 0)
		{
			m_pkItemType->setText(iteminfo[0][0]);
			m_pkItemRemark->setText(iteminfo[0][1]);
		}
		//pos
		if (itemPos.size() > 0)
			m_pkItemPos->setText(itemPos[0]);

		//vertex pos
		if (itemPickedPointsPos.size() > 0)
		{
			m_pkViewer->m_pkRoot->removeChild(m_pkViewer->m_spkPickedPointRoot.get());
			m_pkViewer->m_spkPickedPointRoot.release();
			m_pkViewer->m_spkPickedPointRoot = new osg::Group;
			m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());
			qDebug() << "open highlight vertex " << itemPickedPointsPos[0].size() << endl;
			m_pkViewer->PickedPointList->clear();
			for (int i = 0; i < itemPickedPointsPos[0].size(); i++)
			{
				m_pkViewer->AddPickedPoint(itemPickedPointsPos[0][i], true);//不加入顶点
			}
		}
		//载入图像
		for (int i = 0; i < currentItemNum; i++)
		{
			QImage temp;
			///////////////
			QString imgname_temp = path + "_" + QString::number(i) + "_.png";
			if (temp.load(imgname_temp))
			{
				itemImg.push_back(temp);
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("打开图像失败"), QString::fromLocal8Bit("物体图像缺失,请查看!"));
			}
		}

		QImage* img = new QImage;
		if (!img->load(imgname))
		{
			QMessageBox::information(this, QString::fromLocal8Bit("打开图像失败"), QString::fromLocal8Bit("没有物体图像!"));
			delete img;
		}
		else
			displayImg(img);
		process.setValue(99);
	}

	else
	{
		itemImg.clear();
		QVector<QImage> nullImg;
		itemImg.swap(nullImg);

		iteminfo.clear();
		QVector<QVector<QString>> nulliteminfo;
		iteminfo.swap(nulliteminfo);

		osg_vertices.clear();
		QVector<QVector<QPoint>> nullosg_vertices;
		osg_vertices.swap(nullosg_vertices);

		deleteIndex.clear();
		QVector<int> nulldeleteIndex;
		deleteIndex.swap(nulldeleteIndex);

		itemPos.clear();
		QVector<QString> nullPos;
		itemPos.swap(nullPos);

		currentItemNum = 0;

		qDebug() << " file not exist " << itemImg.size() << endl;
		qDebug() << " file not exist " << currentItemNum << endl;



		m_pkCaseTime->clear();
		m_pkCaseNature->clear();
		m_pkCaseAddress->clear();
		m_pkCaseRemark->clear();
		m_pkItemNum->clear();
		m_pkItemType->clear();
		m_pkItemRemark->clear();
		m_pkItemPos->clear();
		m_pkCaseShot->clear();
	}
	process.close();
}
//------------------------------------------------------------------------------
void MainWindow::init()
{
	centralWidget()->resize(1280, 800);
}
//------------------------------------------------------------------------------
void MainWindow::StartPicking()
{
	m_pkStartPickAction->setDisabled(true);
	m_pkEndPickAction->setDisabled(false);
	m_pkViewer->IsPicking = true;
}
//------------------------------------------------------------------------------
void MainWindow::EndPicking()
{
	m_pkStartPickAction->setDisabled(false);
	m_pkEndPickAction->setDisabled(true);
	m_pkViewer->IsPicking = false;
	/*
	ofstream kFile;
	kFile.open( "Tmp.txt" );
	for( int i = 0; i < m_pkViewer->PickedPointList->size(); i++ )
	{
		osg::Vec3d kPos = m_pkViewer->PickedPointList->at( i );
		kFile<<kPos[0]<<' '<<kPos[1]<<' '<<kPos[2]<<endl;
	}
	kFile.close();
	*/
}
//------------------------------------------------------------------------------
void MainWindow::ComputeVolume()
{
	m_pkViewer->FitPlane();
	double dVolume = m_pkViewer->ComputeVolume();

	char acText[1024] = { 0 };
	sprintf(acText, "Compute Volume (%lf)\n", dVolume);
	m_pkComputeVolumeAction->setText(acText);
}

void MainWindow::Exporttxt()
{
	if (objpath.size() == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("保存数据"), QString::fromLocal8Bit("请先载入模型!"));
		return;
	}
	QString txtfilepath;
	txtfilepath = QFileDialog::getSaveFileName(this, tr("Save"), ".", tr("Text Files(*.txt)"));
	if (txtfilepath.isEmpty())
	{
		return;
	}
	changeItem(m_pkItemNum->currentIndex());
	QString suffix = "txt";

	MyProcessDialog process(this);

	QString posname(txtfilepath);
	posname.replace(txtfilepath.length() - 4, 4, "_pos." + suffix);

	QString vertexname(txtfilepath);
	vertexname.replace(txtfilepath.length() - 4, 4, "_vertex." + suffix);

	QFile file(txtfilepath);

	//pos
	QFile file_pos(posname);

	//vertex pos
	QFile file_vertex(vertexname);
	////////////////////////////
	process.setValue(15);

	{
		if ((m_pkCaseTime->text().size() == 0 || m_pkCaseNature->text().size() == 0 || m_pkCaseAddress->text().size() == 0 ||
			m_pkCaseRemark->document()->toPlainText().size() == 0 || m_pkItemType->text().size() == 0
			|| m_pkItemRemark->document()->toPlainText().size() == 0 || m_pkCaseShot->pixmap()->isNull()) && !delete_last_flag)
		{
			QMessageBox::information(NULL, QString::fromLocal8Bit("保存数据"), QString::fromLocal8Bit("请对所有文本框进行填写"));
		}
		else
		{
			if (!file.open(QIODevice::WriteOnly | QFile::Text))
			{
				QMessageBox::information(this, tr("打开文件失败！"), file.errorString());
				return;
			}
			if (!file_pos.open(QIODevice::WriteOnly | QFile::Text))
			{
				QMessageBox::information(this, tr("打开文件失败！"), file_pos.errorString());
				return;
			}
			if (!file_vertex.open(QIODevice::WriteOnly | QFile::Text))
			{
				QMessageBox::information(this, tr("打开文件失败！"), file_pos.errorString());
				return;
			}
			if (currentItemNum < 0)
				currentItemNum = 0;
			QTextCodec* codec = QTextCodec::codecForName("UTF-8");
			QTextStream out(&file);
			out.setCodec(codec);
			out << QString::fromLocal8Bit("案发时间:") << m_pkCaseTime->text() << "\n";
			out << QString::fromLocal8Bit("案发地点:") << m_pkCaseAddress->text() << "\n";
			out << QString::fromLocal8Bit("案件性质:") << m_pkCaseNature->text() << "\n";
			out << QString::fromLocal8Bit("案件备注:") << m_pkCaseRemark->document()->toPlainText() << "\n";
			out << QString::fromLocal8Bit("物体个数:") << currentItemNum << "\n";
			process.setValue(40);

			QFileInfo file_info = QFileInfo(txtfilepath);
			QString file_name_info = file_info.fileName();

			int pos = txtfilepath.lastIndexOf("/");
			QString dir_obj = txtfilepath.mid(0, pos);
			qDebug() << "save // pos " << pos << endl;
			qDebug() << "save // dir_obj " << dir_obj << endl;
			//删除所有_.png后缀文件,然后进行保存
			QDir dir(dir_obj);
			if (!dir.exists())
				return;
			dir.setFilter(QDir::Files | QDir::NoSymLinks);
			QFileInfoList list = dir.entryInfoList();
			QStringList string_list;
			for (int i = 0; i < list.count(); i++)
			{
				QFileInfo file_info = list.at(i);
				QString suffix = file_info.suffix();
				suffix = "_." + suffix;
				qDebug() << file_info.fileName() << " " << suffix << endl;
				if (QString::compare(suffix, QString("_.png"), Qt::CaseInsensitive) == 0)
				{
					qDebug() << "remove " << dir_obj + "//" + file_info.fileName() << endl;
					QFile::remove(dir_obj + "//" + file_info.fileName());
				}
			}

			QTextStream out_pos(&file_pos);
			out_pos.setCodec(codec);

			QTextStream out_vertex(&file_vertex);
			out_vertex.setCodec(codec);
			process.setValue(60);
			for (int i = 0; i < currentItemNum&&iteminfo.size()>0; i++)
			{
				out << QString::fromLocal8Bit("物体类型:") << iteminfo[i][0] << "\n";
				out << QString::fromLocal8Bit("物体备注:") << iteminfo[i][1] << "\n";
				QString imgname(txtfilepath);
				QString path = imgname.mid(0, txtfilepath.size() - 4);
				imgname = path + "_" + QString::number(i) + "_.png";
				itemImg[i].save(imgname);

				//pos
				QString str = QString::fromLocal8Bit("物体") + QString::number(i + 1) + ":";
				out_pos << str << itemPos[i] << "\n";
				qDebug() << itemPickedPointsPos[i].size() << endl;
				out_vertex << str << itemPickedPointsPos[i].size() << endl;

				for (int j = 0; j < itemPickedPointsPos[i].size(); j++)
				{
					out_vertex << QString::number(itemPickedPointsPos[i][j].x(), 'f', 4) << "," << QString::number(itemPickedPointsPos[i][j].y(), 'f', 4)
						<< "," << QString::number(itemPickedPointsPos[i][j].z(), 'f', 4) << endl;
				}
				std::cout << "One item save success!" << std::endl;
			}
			process.setValue(90);
			file.flush();
			file.close();

			file_pos.flush();
			file_pos.close();

			file_vertex.flush();
			file_vertex.close();

			delete_last_flag = false;
		}
	}
	process.close();
}

//------------------------------------------------------------------------------
void MainWindow::Save()
{
	if (objpath.size() == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("保存数据"), QString::fromLocal8Bit("请先载入模型!"));
		return;
	}
	MyProcessDialog process(this);
	{
		if ((m_pkCaseTime->text().size() == 0 || m_pkCaseNature->text().size() == 0 || m_pkCaseAddress->text().size() == 0 ||
			m_pkCaseRemark->document()->toPlainText().size() == 0 || m_pkItemType->text().size() == 0
			|| m_pkItemRemark->document()->toPlainText().size() == 0 || m_pkCaseShot->pixmap()->isNull()) && !delete_last_flag)
		{
			QMessageBox::information(NULL, QString::fromLocal8Bit("保存数据"), QString::fromLocal8Bit("请对所有文本框进行填写"));
		}
		else
		{
			if (currentItemNum < 0)
				currentItemNum = 0;
			changeItem(m_pkItemNum->currentIndex());
			QFileInfo file_info = QFileInfo(objpath);
			QString file_name_info = file_info.fileName();
			//先将数据库中的该模型删除，之后重新插入
			//由于设置了递归的删除规则，所以只需要删除表models中的一条即可。
			connector->delete_from_models(Qstring2QByteArray(file_name_info).data());

			//将模型信息保存到数据库
			process.setValue(10);
			connector->insert_into_models(Qstring2QByteArray(file_name_info).data(),
				Qstring2QByteArray(m_pkCaseTime->text()).data(),
				Qstring2QByteArray(m_pkCaseAddress->text()).data(),
				Qstring2QByteArray(m_pkCaseNature->text()).data(),
				Qstring2QByteArray(m_pkCaseRemark->document()->toPlainText()).data(),
				currentItemNum);
			process.setValue(20);
			int pos = objpath.lastIndexOf("/");
			QString dir_obj = objpath.mid(0, pos);
			qDebug() << "save // pos " << pos << endl;
			qDebug() << "save // dir_obj " << dir_obj << endl;
			//删除所有_.png后缀文件,然后进行保存
			/*
			QDir dir(dir_obj);
			if (!dir.exists())
				return;
			dir.setFilter(QDir::Files | QDir::NoSymLinks);
			QFileInfoList list = dir.entryInfoList();
			QStringList string_list;
			for (int i = 0; i < list.count(); i++)
			{
				QFileInfo file_info = list.at(i);
				QString suffix = file_info.suffix();
				suffix = "_." + suffix;
				qDebug() << file_info.fileName() << " " << suffix << endl;
				if (QString::compare(suffix, QString("_.png"), Qt::CaseInsensitive) == 0)
				{
					qDebug() << "remove " << dir_obj + "//" + file_info.fileName() << endl;
					QFile::remove(dir_obj + "//" + file_info.fileName());
				}
			}
			*/
			process.setValue(70);

			for (int i = 0; i < currentItemNum&&iteminfo.size()>0; i++)
			{
				
				QString imgname(objpath);
				QString path = imgname.mid(0, objpath.size() - 4);
				imgname = path + "_" + QString::number(i) + "_.png";
				//itemImg[i].save(imgname);
				////////---ChangeHere
				//保存物体信息到数据库
				
				connector->insert_into_scene(Qstring2QByteArray(imgname).data(),
					Qstring2QByteArray(iteminfo[i][0]).data(),
					Qstring2QByteArray(itemPos[i]).data(),
					Qstring2QByteArray(iteminfo[i][1]).data(),
					Qstring2QByteArray(file_name_info).data(),
					itemPickedPointsPos[i].size());
				connector->getLastInsertedId();
				connector->insert_into_image(connector->last_id, itemImg[i]);
				/////////+++ChangeHere
				connector->begin();
				for (int j = 0; j < itemPickedPointsPos[i].size(); j++)
				{
					connector->insert_into_vertex(connector->last_id,
						itemPickedPointsPos[i][j].x(),
						itemPickedPointsPos[i][j].y(),
						itemPickedPointsPos[i][j].z());
				}
				connector->commit();
				std::cout << "One item save success!" << std::endl;
			}
			process.setValue(99);
			delete_last_flag = false;
		}
	}
	process.close();
}
//------------------------------------------------------------------------------
void MainWindow::selectItem()
{
	changeItem(lastIndex);
	int currentIndex = m_pkItemNum->currentIndex();
	qDebug() << "currentIndex:" << currentIndex << endl;
	if (currentIndex >= 0)
	{
		if (iteminfo.size() > 0)
			qDebug() << "select " << iteminfo[currentIndex][0] << iteminfo[currentIndex][1] << endl;
		if (iteminfo.size() > 0)
		{
			m_pkItemType->setText(iteminfo[currentIndex][0]);
			m_pkItemRemark->setText(iteminfo[currentIndex][1]);

			//pos
			if (itemPos.size() > 0)
				m_pkItemPos->setText(itemPos[currentIndex]);

			//显示图片
			if (itemImg.size() > 0 && currentIndex < itemImg.size())
				displayImg(&itemImg[currentIndex]);
			//显示高亮
			if (itemPickedPointsPos.size() > 0)
			{
				m_pkViewer->m_pkRoot->removeChild(m_pkViewer->m_spkPickedPointRoot.get());
				m_pkViewer->m_spkPickedPointRoot.release();
				m_pkViewer->m_spkPickedPointRoot = new osg::Group;
				m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());
				qDebug() << "select vertex " << itemPickedPointsPos[currentIndex].size() << endl;
				m_pkViewer->PickedPointList->clear();
				for (int i = 0; i < itemPickedPointsPos[currentIndex].size(); i++)
				{
					m_pkViewer->AddPickedPoint(itemPickedPointsPos[currentIndex][i], true);//不加入顶点
				}
			}
		}
	}
	lastIndex = currentIndex;
}
//------------------------------------------------------------------------------
void MainWindow::addItems()
{
	if (objpath.size() == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("添加物体数据"), QString::fromLocal8Bit("请先载入模型!"));
		return;
	}
	//QString filename(objpath);
	//QString suffix = "txt";
	//filename.replace(objpath.length() - 3, 3, suffix);

	{
		if (m_pkCaseTime->text().size() == 0 || m_pkCaseNature->text().size() == 0 || m_pkCaseAddress->text().size() == 0 ||
			m_pkCaseRemark->document()->toPlainText().size() == 0 || m_pkItemType->text().size() == 0
			|| m_pkItemRemark->document()->toPlainText().size() == 0 || m_pkCaseShot->pixmap()->isNull())
			QMessageBox::information(NULL, QString::fromLocal8Bit("添加物品"), QString::fromLocal8Bit("请对所有文本框进行填写"));
		else
		{

			currentItemNum += 1;
			QVector<QString> temp;
			temp.push_back(m_pkItemType->text());
			temp.push_back(m_pkItemRemark->document()->toPlainText());
			iteminfo.append(temp);
			m_pkItemNum->addItem(QString::number(currentItemNum));

			//增加图片
			itemImg.push_back(m_pkCaseShot->pixmap()->toImage());
			qDebug() << itemImg.size() << endl;

			//增加顶点
			itemPos.push_back(m_pkItemPos->document()->toPlainText());

			//增加三维坐标
			qDebug() << "add picked point size " << m_pkViewer->PickedPointList->size() << endl;

			QVector<osg::Vec3d> points_temp;
			for (int i = 0; i < m_pkViewer->PickedPointList->size(); i++)
			{
				points_temp.push_back(m_pkViewer->PickedPointList->at(i));
			}
			itemPickedPointsPos.push_back(points_temp);
		}
	}
}

void MainWindow::copyItem()
{
	addItems();
	m_pkItemNum->setCurrentIndex(m_pkItemNum->count() - 1);
}

//------------------------------------------------------------------------------
void MainWindow::deleteItem()
{
	if (iteminfo.size() > 1)
	{
		int currentIndex = m_pkItemNum->currentIndex();
		deleteIndex.push_back(currentIndex);
		m_pkItemNum->removeItem(currentIndex);
		for (int i = 0; i < currentItemNum - 1; i++)
		{
			m_pkItemNum->setItemText(i, QString::number(i + 1));
		}
		//删除物体信息
		iteminfo.erase(iteminfo.begin() + currentIndex);
		itemImg.erase(itemImg.begin() + currentIndex);
		//删除顶点信息
		itemPos.erase(itemPos.begin() + currentIndex);
		//删除三维坐标
		itemPickedPointsPos.erase(itemPickedPointsPos.begin() + currentIndex);
		m_pkViewer->m_spkPickedPointRoot->removeChildren(currentIndex, 1);

		if (currentIndex < currentItemNum - 1)//说明删除的物品后面还有，把后续图片重命名
		{
			if (itemImg.size() > 0)
				displayImg(&itemImg[currentIndex]);
			m_pkItemType->setText(iteminfo[currentIndex][0]);
			m_pkItemRemark->setText(iteminfo[currentIndex][1]);
			m_pkItemPos->setText(itemPos[currentIndex]);

			//更改高亮
			if (itemPickedPointsPos.size() > 0)
			{
				m_pkViewer->m_pkRoot->removeChild(m_pkViewer->m_spkPickedPointRoot.get());
				m_pkViewer->m_spkPickedPointRoot.release();
				m_pkViewer->m_spkPickedPointRoot = new osg::Group;
				m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());
				qDebug() << "select vertex " << itemPickedPointsPos[currentIndex].size() << endl;
				m_pkViewer->PickedPointList->clear();
				for (int i = 0; i < itemPickedPointsPos[currentIndex].size(); i++)
				{
					m_pkViewer->AddPickedPoint(itemPickedPointsPos[currentIndex][i], true);//不加入顶点
				}
			}
		}
		currentItemNum -= 1;
	}
	else if (iteminfo.size() == 1)
	{
		deleteIndex.push_back(0);
		m_pkItemNum->removeItem(0);

		currentItemNum -= 1;
		iteminfo.erase(iteminfo.begin());
		if (itemImg.size() > 0)
			itemImg.erase(itemImg.begin());
		//删除顶点信息
		if (itemPos.size() > 0)
			itemPos.erase(itemPos.begin());

		if (itemPickedPointsPos.size() > 0)
		{
			itemPickedPointsPos.erase(itemPickedPointsPos.begin());
			m_pkViewer->m_spkPickedPointRoot->removeChildren(0, 1);
		}

		currentItemNum -= 1;
		m_pkItemType->clear();
		m_pkItemRemark->clear();
		m_pkItemPos->clear();
		m_pkCaseShot->clear();

		delete_last_flag = true;
	}
	if (currentItemNum < 0)
		currentItemNum = 0;

}
//------------------------------------------------------------------------------
void MainWindow::changeItem(int index)
{
	if (iteminfo.size() > 1)
	{
		int currentIndex = index;
		iteminfo[currentIndex][0] = m_pkItemType->text();
		iteminfo[currentIndex][1] = m_pkItemRemark->document()->toPlainText();
		itemPos[currentIndex] = m_pkItemPos->document()->toPlainText();
		itemImg[currentIndex] = m_pkCaseShot->pixmap()->toImage();

		//更改三维坐标信息
		QVector<osg::Vec3d> points_temp;
		for (int i = 0; i < m_pkViewer->PickedPointList->size(); i++)
		{
			points_temp.push_back(m_pkViewer->PickedPointList->at(i));
		}
		qDebug() << "before swap size " << itemPickedPointsPos[currentIndex].size() << endl;
		itemPickedPointsPos[currentIndex].swap(points_temp);
		qDebug() << "after swap size " << itemPickedPointsPos[currentIndex].size() << endl;

	}
	else if (iteminfo.size() == 1)
	{
		iteminfo[0][0] = m_pkItemType->text();
		iteminfo[0][1] = m_pkItemRemark->document()->toPlainText();
		itemPos[0] = m_pkItemPos->document()->toPlainText();
		itemImg[0] = m_pkCaseShot->pixmap()->toImage();


		QVector<osg::Vec3d> points_temp;
		for (int i = 0; i < m_pkViewer->PickedPointList->size(); i++)
		{
			points_temp.push_back(m_pkViewer->PickedPointList->at(i));
		}
		qDebug() << "before swap size " << itemPickedPointsPos[0].size() << endl;
		itemPickedPointsPos[0].swap(points_temp);
		qDebug() << "after swap size " << itemPickedPointsPos[0].size() << endl;

	}
}
//------------------------------------------------------------------------------
void MainWindow::onCompleteCaptureScreenshot(QImage capture_img, QRect rect)
{
	onCompleteCaptureBase(capture_img, rect);
	//std::cout << "changeitem:" << m_pkItemNum->currentIndex()<<std::endl;
	changeItem(m_pkItemNum->currentIndex());

	itemPickedPointsPos[m_pkItemNum->currentIndex()].clear();
	for (int i = 0; i < m_pkViewer->PickedPointList->size(); i++)
	{
		itemPickedPointsPos[m_pkItemNum->currentIndex()].push_back(m_pkViewer->PickedPointList->at(i));
	}
}

void MainWindow::onCompleteCaptureCreateNew(QImage capture_img, QRect rect)
{
	m_pkItemNum->setCurrentIndex(m_pkItemNum->count() - 1);
	onCompleteCaptureBase(capture_img, rect);
	changeItem(m_pkItemNum->currentIndex());

	itemPickedPointsPos[m_pkItemNum->currentIndex()].clear();
	for (int i = 0; i < m_pkViewer->PickedPointList->size(); i++)
	{
		itemPickedPointsPos[m_pkItemNum->currentIndex()].push_back(m_pkViewer->PickedPointList->at(i));
	}
}

//------------------------------------------------------------------------------
void MainWindow::onCompleteCaptureBase(QImage capture_img, QRect rect)
{
	displayImg(&capture_img);
	QImage *temp = new QImage;
	*temp = capture_img.copy();
	this->capture_img = temp;

	selectedRect = rect;
	qDebug() << "mainwindow " << selectedRect.x() << " " << selectedRect.y() << selectedRect.width() << " " << selectedRect.height() << endl;
	qDebug() << this->pos() << endl;
	QPoint p = pkCentralWidget->mapFromGlobal(QPoint(selectedRect.x(), selectedRect.y()));//pkCentralWidget坐标
	QPoint p_pkviewer = m_pkViewer->pos();//在父类中位置
	QPoint p_osgviewer(p.x() - 2 * p_pkviewer.x(), p.y() - 2 * p_pkviewer.y());//三维模型窗口位置坐标

	//新增
	m_pkViewer->m_pkRoot->removeChild(m_pkViewer->m_spkPickedPointRoot.get());
	m_pkViewer->m_spkPickedPointRoot.release();
	m_pkViewer->m_spkPickedPointRoot = new osg::Group;
	m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());
	m_pkViewer->PickedPointList.release();
	m_pkViewer->PickedPointList = new osg::Vec3Array;

	selectedRect = QRect(p_osgviewer.x(), p_osgviewer.y(), rect.width(), rect.height());

	//pos
	QVector<QPoint> p_temp;
	p_temp.push_back(QPoint(selectedRect.x(), selectedRect.y()));
	p_temp.push_back(QPoint(selectedRect.x() + selectedRect.width() - 1, selectedRect.y() + selectedRect.height() - 1));
	QString pos = QString::number(p_temp[0].x()) + "," + QString::number(p_temp[0].y()) + "," + QString::number(p_temp[1].x()) + ","
		+ QString::number(p_temp[1].y());
	m_pkItemPos->setText(pos);


	m_pkViewer->HighlightSelect(selectedRect.x(), selectedRect.y(), selectedRect.x() + rect.width(), selectedRect.y() + rect.height());
	

	/*
	qDebug() << "picked point size " << m_pkViewer->PickedPointList->size() << endl;

	qDebug() << "pkCentralWidget " << pkCentralWidget->width() << " " << pkCentralWidget->height() << endl;
	qDebug() << "m_pkViewer " << m_pkViewer->width() << " " << m_pkViewer->height() << endl;
	//	qDebug() << "p_pkcentralwid  " << p_pkcentralwid.x() << " " << p_pkcentralwid.y() << endl;
	qDebug() << m_pkViewer->parentWidget()->parentWidget()->geometry() << endl;
	qDebug() << "p_pkviewer  " << p_pkviewer.x() << " " << p_pkviewer.y() << endl;
	qDebug() << "after convert " << p.x() << " " << p.y() << endl;
	qDebug() << "after convert from parent " << p_osgviewer.x() << " " << p_osgviewer.y() << " " << selectedRect.x() + selectedRect.width() - 1 << " " << selectedRect.y() + selectedRect.height() - 1 << endl;
	*/
}
void MainWindow::ChangeScreenshot()
{
	if (objpath.size() == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("截图显示"), QString::fromLocal8Bit("请先载入模型!"));
		return;
	}
	instancec = ScreenShoot::InstanceChange();
	connect(instancec, SIGNAL(signalCompleteCature(QImage, QRect)), this, SLOT(onCompleteCaptureScreenshot(QImage, QRect)));
	instancec->show();
}



//------------------------------------------------------------------------------
void MainWindow::displayImg(QImage *img)
{
	if (img == NULL)
		return;
	int w = img->width();
	int h = img->height();
	int h_ = h, w_ = w;
	int mul;
	if (w / m_pkCaseRemark->width() >= h / m_pkCaseRemark->height())
		mul = w / m_pkCaseRemark->width();
	else
		mul = h / m_pkCaseRemark->height();
	if (mul != 0)
	{
		w_ = w / mul;
		h_ = h / mul;
	}
	QImage* scaled_img = new QImage;
	*scaled_img = img->scaled(w_, h_, Qt::KeepAspectRatio);
	m_pkCaseShot->setPixmap(QPixmap::fromImage(*scaled_img));
}

QByteArray MainWindow::Qstring2QByteArray(QString str)
{
	return str.toLocal8Bit();
}

void MainWindow::createNewItem()
{
	if (objpath.size() == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("截图显示"), QString::fromLocal8Bit("请先载入模型!"));
		return;
	}
	if (currentItemNum!=0 && (m_pkCaseTime->text().size() == 0 || m_pkCaseNature->text().size() == 0 || m_pkCaseAddress->text().size() == 0 ||
		m_pkCaseRemark->document()->toPlainText().size() == 0 || m_pkItemType->text().size() == 0
		|| m_pkItemRemark->document()->toPlainText().size() == 0 || m_pkCaseShot->pixmap()->isNull()) && !delete_last_flag)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("输出文档"), QString::fromLocal8Bit("请对所有文本框进行填写"));
		return;
	}
	QVector<QString> temp;
	temp.push_back(QString::fromLocal8Bit("请输入案件类型"));
	temp.push_back(QString::fromLocal8Bit("请输入案件评论"));
	iteminfo.append(temp);

	if (iteminfo.size() > 1)
	{
		int currentIndex = m_pkItemNum->currentIndex();
		iteminfo[currentIndex][0] = m_pkItemType->text();
		iteminfo[currentIndex][1] = m_pkItemRemark->document()->toPlainText();
		itemPos[currentIndex] = m_pkItemPos->document()->toPlainText();
		itemImg[currentIndex] = m_pkCaseShot->pixmap()->toImage();
	}

	disconnect(m_pkItemNum, SIGNAL(currentIndexChanged(int)), this, SLOT(selectItem()));
	currentItemNum += 1;
	m_pkItemNum->addItem(QString::number(currentItemNum));
	connect(m_pkItemNum, SIGNAL(currentIndexChanged(int)), this, SLOT(selectItem()));

	//增加图片
	QImage tempimg;
	//itemImg.push_back(m_pkCaseShot->pixmap()->toImage());
	itemImg.push_back(tempimg);
	//qDebug() << itemImg.size() << endl;

	//增加顶点
	QString tempstr;
	itemPos.push_back(tempstr);
	//itemPos.push_back(m_pkItemPos->document()->toPlainText());

	//增加三维坐标
	//qDebug() << "add picked point size " << m_pkViewer->PickedPointList->size() << endl;
	
	QVector<osg::Vec3d> points_temp;
	//for (int i = 0; i < m_pkViewer->PickedPointList->size(); i++)
	//{
	//	points_temp.push_back(m_pkViewer->PickedPointList->at(i));
	//}
	itemPickedPointsPos.push_back(points_temp);
	
	instancea = ScreenShoot::InstanceAdd();
	connect(instancea, SIGNAL(signalCompleteCature(QImage, QRect)), this, SLOT(onCompleteCaptureCreateNew(QImage, QRect)));
	instancea->show();
}

void MainWindow::GenerateDocument()
{

	if (objpath.size() == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("输出文档"), QString::fromLocal8Bit("请先载入模型!"));
		return;
	}
	if ((m_pkCaseTime->text().size() == 0 || m_pkCaseNature->text().size() == 0 || m_pkCaseAddress->text().size() == 0 ||
		m_pkCaseRemark->document()->toPlainText().size() == 0 || m_pkItemType->text().size() == 0
		|| m_pkItemRemark->document()->toPlainText().size() == 0 || m_pkCaseShot->pixmap()->isNull()) && !delete_last_flag)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("输出文档"), QString::fromLocal8Bit("请对所有文本框进行填写"));
		return;
	}
	QString temppath;
	generatedoc = new GenerateDoc();
	if (generatedoc->Open(docfilename, false) == false)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("打开失败"), QString::fromLocal8Bit("打开默认模版失败，请手动选择!"));
		temppath = QFileDialog::getOpenFileName(this, tr("Open"), ".", tr("Dot Files(*.dot)"));
		docfilename = temppath;
	}
	QFileInfo file_info = QFileInfo(objpath);
	QString file_name_info = file_info.fileName();
	temppath = QFileDialog::getSaveFileName(this, tr("Save Docunment"), ".", tr("Word Files(*.doc *.docx)"));
	if (temppath.isEmpty())
	{
		return;
	}
	MyProcessDialog process(this);
	generatedoc->replaceText("case_time", m_pkCaseTime->text());
	generatedoc->replaceText("case_location", m_pkCaseAddress->text());
	generatedoc->replaceText("case_nature", m_pkCaseNature->text());
	generatedoc->replaceText("case_remarks", m_pkCaseRemark->document()->toPlainText());
	generatedoc->replaceText("model_name", file_name_info);

	process.setValue(5);
	int num = currentItemNum;
	if (num <= 0)
	{
		generatedoc->replaceText("object_num", QString::number(0));
		num = 0;
		temppath = QFileDialog::getSaveFileName(this, tr("Save Docunment"), ".", tr("Word Files(*.doc *.docx)"));
		generatedoc->save(temppath);
		generatedoc->close();
		delete generatedoc;
		generatedoc = NULL;
		return;
	}
	else
	{
		generatedoc->replaceText("object_num", QString::number(num));
	}
	QStringList headList;
	headList
		<< QStringLiteral("名称")
		<< QStringLiteral("物体位置")
		<< QStringLiteral("物体类型")
		<< QStringLiteral("物体备注")
		<< QStringLiteral("图片")
		;

	QAxObject *table = generatedoc->insertTable("objects", num, headList);
	process.setValue(20);
	int interval = 80 / num;
	int sum = 20;
	for (int i = 0; i < num; i++) {
		QString str = QString::fromLocal8Bit("物体") + QString::number(i + 1);
		generatedoc->SetTableCellString(table, i * 5 + 1, 2, str);
		generatedoc->SetTableCellString(table, i * 5 + 2, 2, itemPos[i]); //物体位置
		generatedoc->SetTableCellString(table, i * 5 + 3, 2, iteminfo[i][0]);//物体类型
		generatedoc->SetTableCellString(table, i * 5 + 4, 2, iteminfo[i][1]);//物体备注
		QString imgname(objpath);
		QString path = imgname.mid(0, objpath.size() - 4);
		imgname = path + "_" + QString::number(i) + "_.png";
		generatedoc->SetTableCellPic(table, i * 5 + 5, 2, imgname);
		sum = sum + interval;
		process.setValue(sum);
	}

	generatedoc->save(temppath);
	generatedoc->close();
	delete generatedoc;
	generatedoc = NULL;
	process.setValue(100);
	process.close();
}

void MainWindow::HideDock()
{
	m_pkShowDock->setEnabled(true);
	m_pkHideDock->setEnabled(false);
	pDockWidget->setVisible(false);
}

void MainWindow::ShowDock()
{
	m_pkShowDock->setEnabled(false);
	m_pkHideDock->setEnabled(true);
	pDockWidget->setVisible(true);
}

void MainWindow::ManageMarks()
{
	std::vector<SingleMark> lines;
	lines.clear();
	MarkManager = new MarkManagerWindow(&itemImg[m_pkItemNum->currentIndex()],&lines);
	MarkManager->setWindowFlags(Qt::Widget);
	MarkManager->show();
}

void MainWindow::NewObj()
{
	objpath = QFileDialog::getOpenFileName(this, tr("Open Model"), ".", tr("Obj Files(*.obj)"));
	qDebug() << objpath << " and length is " << objpath.length() << endl;
	QByteArray ba = objpath.toLatin1();
	const char *c_str2 = ba.data();
	if (objpath.length() == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("选择模型"), QString::fromLocal8Bit("请选择模型!"));
		return;
	}
	MyProcessDialog process(this);
	process.setValue(5);
	if (openCount == 0)
	{
		m_pkViewer->m_pkRoot = new osg::Group();

		//		m_pkViewer->m_pkRoot->removeChildren(0,1);
		process.setValue(10);
		m_pkViewer->m_pkRoot->addChild(osgDB::readNodeFile(c_str2));
		process.setValue(70);
		m_pkViewer->m_spkViewer->setSceneData(m_pkViewer->m_pkRoot);
		m_pkViewer->m_spkPickedPointRoot = new osg::Group;

		m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());
	}
	else
	{
		m_pkViewer->m_pkRoot->removeChildren(openCount - 1, 1);
		process.setValue(10);
		m_pkViewer->m_pkRoot->addChild(osgDB::readNodeFile(c_str2));
		process.setValue(70);
		m_pkViewer->m_spkViewer->setSceneData(m_pkViewer->m_pkRoot);
		m_pkViewer->m_spkPickedPointRoot = new osg::Group;

		m_pkViewer->m_pkRoot->addChild(m_pkViewer->m_spkPickedPointRoot.get());

		m_pkCaseTime->clear();
		m_pkCaseNature->clear();
		m_pkCaseAddress->clear();
		m_pkCaseRemark->clear();
		m_pkItemNum->clear();
		m_pkItemType->clear();
		m_pkItemRemark->clear();
		m_pkItemPos->clear();
		m_pkCaseShot->clear();
	}
	openCount += 1;
	process.setValue(90);
	itemImg.clear();
	iteminfo.clear();
	osg_vertices.clear();
	deleteIndex.clear();
	itemPos.clear();
	QVector<QString> nullPos;
	itemPos.swap(nullPos);
	currentItemNum = 0;
	m_pkCaseTime->clear();
	m_pkCaseNature->clear();
	m_pkCaseAddress->clear();
	m_pkCaseRemark->clear();
	//m_pkItemNum->clear();
	m_pkItemType->clear();
	m_pkItemRemark->clear();
	m_pkItemPos->clear();
	m_pkCaseShot->clear();
	process.close();
	//createNewItem();
}

void MainWindow::initToolBar()
{
	//QAction* newItemToolBar = new QAction(tr("newItem"), this);
	//newItemToolBar->setIcon(QIcon(tr("icons/copy.png")));

	QLabel * labelFile = new QLabel(QString::fromLocal8Bit("文\n件"));
	QLabel * labelObject = new QLabel(QString::fromLocal8Bit("物\n体"));
	QLabel * labelLayout = new QLabel(QString::fromLocal8Bit("布\n局"));


	QToolBar *toolBar = addToolBar(tr("&File"));
	toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	toolBar->addWidget(labelFile);
	//toolBar->addAction(m_pkNewOBJ);
	//toolBar->addAction(m_pkOpenAction);
	//toolBar->addAction(m_pkOpenDBAction);
	//toolBar->addAction(m_pkGenerateDoc);
	//toolBar->addAction(m_pkExporttxtAction);
	toolBar->addAction(m_pkSaveAction);

	toolBar->addSeparator();

	toolBar->addWidget(labelObject);
	toolBar->addAction(m_pkScreenShotAction);
	toolBar->addAction(m_pkAddItemAction);
	toolBar->addAction(m_pkNewAction);
	toolBar->addAction(m_pkDeleteAction);
	toolBar->addAction(m_pkManageMark);

	toolBar->addSeparator();

	toolBar->addWidget(labelLayout);
	toolBar->addAction(m_pkHideDock);
	toolBar->addAction(m_pkShowDock);
}

void MainWindow::initMenu()
{
	m_pkScreenShotAction = new QAction(QString::fromLocal8Bit("更改截图"), this);
	connect(m_pkScreenShotAction, SIGNAL(triggered()), this, SLOT(ChangeScreenshot()));
	m_pkScreenShotAction->setIcon(QIcon("icons/quanping.png"));

	m_pkAddItemAction = new QAction(QString::fromLocal8Bit("复制"), this);
	connect(m_pkAddItemAction, SIGNAL(triggered()), this, SLOT(copyItem()));
	m_pkAddItemAction->setIcon(QIcon("icons/fuzhi.png"));

	m_pkNewAction = new QAction(QString::fromLocal8Bit("新建(ctrl+f)"), this);
	connect(m_pkNewAction, SIGNAL(triggered()), this, SLOT(createNewItem()));
	m_pkNewAction->setIcon(QIcon("icons/tianjia.png"));

	m_pkDeleteAction = new QAction(QString::fromLocal8Bit("删除(ctrl+d)"), this);
	connect(m_pkDeleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));
	m_pkDeleteAction->setIcon(QIcon("icons/lajitong.png"));

	m_pkSaveAction = new QAction(QString::fromLocal8Bit("保存(ctrl+s)"), this);
	connect(m_pkSaveAction, SIGNAL(triggered()), this, SLOT(Save()));
	m_pkSaveAction->setIcon(QIcon("icons/baocun.png"));

	m_pkNewOBJ = new QAction(QString::fromLocal8Bit("新建场景"), this);
	connect(m_pkNewOBJ, SIGNAL(triggered()), this, SLOT(NewObj()));

	m_pkExporttxtAction = new QAction(QString::fromLocal8Bit("输出文本文件(.txt)"), this);
	connect(m_pkExporttxtAction, SIGNAL(triggered()), this, SLOT(Exporttxt()));

	m_pkGenerateDoc = new QAction(QString::fromLocal8Bit("输出文档(.doc;.docx)"), this);
	connect(m_pkGenerateDoc, SIGNAL(triggered()), this, SLOT(GenerateDocument()));

	m_pkOpenAction = new QAction(QString::fromLocal8Bit("通过txt文件打开"), this);
	connect(m_pkOpenAction, &QAction::triggered, this, &MainWindow::Open);

	m_pkOpenDBAction = new QAction(QString::fromLocal8Bit("通过数据库打开"), this);
	connect(m_pkOpenDBAction, &QAction::triggered, this, &MainWindow::OpenDB);

	m_pkHideDock = new QAction(QString::fromLocal8Bit("隐藏编辑栏"), this);
	connect(m_pkHideDock, &QAction::triggered, this, &MainWindow::HideDock);
	m_pkHideDock->setIcon(QIcon("icons/yincangxianshi.png"));

	m_pkShowDock = new QAction(QString::fromLocal8Bit("显示编辑栏"), this);
	connect(m_pkShowDock, &QAction::triggered, this, &MainWindow::ShowDock);
	m_pkShowDock->setIcon(QIcon("icons/xianshi.png"));
	m_pkShowDock->setEnabled(false);

	m_pkManageMark = new QAction(QString::fromLocal8Bit("管理标注"), this);
	m_pkManageMark->setIcon(QIcon("icons/shezhi.png"));
	connect(m_pkManageMark, &QAction::triggered, this, &MainWindow::ManageMarks);

	QMenu* pkFileMenu = menuBar()->addMenu(QString::fromLocal8Bit("文件"));
	//pkFileMenu->setIcon(QIcon("icons/wenjian_2.png"));
	QMenu* pkOpenMenu = pkFileMenu->addMenu(QString::fromLocal8Bit("打开"));
	pkOpenMenu->setIcon(QIcon("icons/wenjianjia.png"));
	{
		/* 打开 */
		pkOpenMenu->addAction(m_pkNewOBJ);
		pkOpenMenu->addAction(m_pkOpenAction);
		pkOpenMenu->addAction(m_pkOpenDBAction);
	}
	QMenu* pkSaveMenu = pkFileMenu->addMenu(QString::fromLocal8Bit("输出"));
	pkSaveMenu->setIcon(QIcon("icons/dayin.png"));
	{
		/* 输出 */
		pkSaveMenu->addAction(m_pkGenerateDoc);
		pkSaveMenu->addAction(m_pkExporttxtAction);
	}
	pkFileMenu->addAction(m_pkSaveAction);

	QMenu* pkObjMenu = menuBar()->addMenu(QString::fromLocal8Bit("物体"));
	//pkObjMenu->setIcon(QIcon("icons/media.png"));
	pkObjMenu->addAction(m_pkScreenShotAction);
	pkObjMenu->addAction(m_pkAddItemAction);
	pkObjMenu->addAction(m_pkNewAction);
	pkObjMenu->addAction(m_pkDeleteAction);
	pkObjMenu->addAction(m_pkManageMark);

	QMenu* pkLayoutMenu = menuBar()->addMenu(QString::fromLocal8Bit("布局"));
	//pkLayoutMenu->setIcon(QIcon("icons/layout-two.png"));
	pkLayoutMenu->addAction(m_pkHideDock);
	pkLayoutMenu->addAction(m_pkShowDock);
}

void MainWindow::initShortcut()
{
	//快捷键
	m_pkSaveShortAction = new QAction(this);
	m_pkSaveShortAction->setShortcut(tr("ctrl+s"));//保存
	this->addAction(m_pkSaveShortAction);
	connect(m_pkSaveShortAction, SIGNAL(triggered()), this, SLOT(Save()));

	m_pkDeleteShortAction = new QAction(this);
	m_pkDeleteShortAction->setShortcut(tr("ctrl+d"));//删除
	this->addAction(m_pkDeleteShortAction);
	connect(m_pkDeleteShortAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

	m_pkChangeShortAction = new QAction(this);
	m_pkChangeShortAction->setShortcut(tr("ctrl+f"));//添加
	this->addAction(m_pkChangeShortAction);
	connect(m_pkChangeShortAction, SIGNAL(triggered()), this, SLOT(createNewItem()));
}