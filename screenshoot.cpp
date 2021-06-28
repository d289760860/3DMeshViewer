#include "screenshoot.h"


ScreenShoot* ScreenShoot::instancec = 0;
ScreenShoot* ScreenShoot::instancea = 0;

ScreenShoot::ScreenShoot(QWidget *parent)
	: QWidget(parent)
{

}
ScreenShoot::ScreenShoot()
{
	// ��ȡ��Ļ�ߴ�
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect deskRect = desktopWidget->screenGeometry();
	// ����������Ϊ��Ļ�ߴ磬ȥ��������
	g_width = deskRect.width();
	g_height = deskRect.height();
	this->resize(g_width, g_height);

	// ����setbackground() ���ñ���
	setbackground(deskRect.width(), deskRect.height());

	//��ʼ������
	g_rubber = NULL;
	origin = end = QPoint(0, 0);
	//��ͼ��ǩ
	label = new QLabel("");
	label->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}
ScreenShoot::~ScreenShoot()
{

}
void ScreenShoot::setImgName(QString objpath)
{
	imgname = objpath;
	QString img_suffix = "png";
	imgname.replace(objpath.length() - 3, 3, img_suffix);
}
void ScreenShoot::mousePressEvent(QMouseEvent *e)
{
	if (!g_rubber)
	{
		g_rubber = new QRubberBand(QRubberBand::Rectangle, this);
	}
	// ����Ƥ�����ÿɼ�
	g_rubber->show();
	// ��¼���λ��
	origin = e->pos();
	// ������Ƥ��ѡ��
	g_rubber->setGeometry(origin.x(), origin.y(), 0, 0);

}
void ScreenShoot::mouseMoveEvent(QMouseEvent *e)
{
	if (g_rubber)
	{
		// ��¼�յ�
		end = e->pos();

		//����Ҫ��ʾ������
		int w = abs(end.x() - origin.x());
		int h = abs(end.y() - origin.y());
		int x = origin.x() < end.x() ? origin.x() : end.x();
		int y = origin.y() < end.y() ? origin.y() : end.y();

		g_rubber->setGeometry(x, y, w, h);
		// ��̬��ʾѡ����С
		setLabel();
	}
}
void ScreenShoot::mouseReleaseEvent(QMouseEvent *e)
{
	if (g_rubber)
	{
		// ��¼�յ�
		end = e->pos();
		g_rubber->hide();
		// ����
		grabScreen();
		signalCompleteCature(result_pic,selectedRect);
		// ������رճ���ͱ�ǩ��
		label->close();

		// ���ʹ��close()��������������ʱ��������Ҳ��close()���������Ҫ������Ϊһ��ģ�飬ʹ��hide������close
		this->close();


	}
}
void ScreenShoot::grabScreen()
{
	// ����Ҫ��ȡ������
	int wid = abs(origin.x() - end.x());
	int height = abs(origin.y() - end.y());
	int x = origin.x() < end.x() ? origin.x() : end.x();
	int y = origin.y() < end.y() ? origin.y() : end.y();


	// ��ȫ���������н�ͼ
	selectedRect = QRect(x, y, wid, height);
	result_pic = bg->copy(x, y, wid, height);
	qDebug() << "screenshot " <<x<<" "<<y<< result_pic.width() << " " << result_pic.height() << endl;
//	result_pic.save(imgname);

	// ��ȡ����ǰ·������Ƭ��ͼ
//	QDesktopServices::openUrl(QUrl(imgname));

	//ɾ������ͼ
	QFile::remove("bg.bmp");
}
void ScreenShoot::setLabel()
{
	// ������ǩ��ʾλ��
	int wid = abs(origin.x() - end.x());
	int height = abs(origin.y() - end.y());
	int x = origin.x() < end.x() ? origin.x() : end.x();
	int y = origin.y() < end.y() ? origin.y() : end.y();

	// ���ñ�ǩ��ʾ����
	QString str = QString(" %1 x %2      ").arg(wid).arg(height);
	label->setText(str);
	// ���ñ�ǩλ��
	QRect rect(label->contentsRect());
	label->move(QPoint(x, y - rect.height()));
	label->show();

}
void ScreenShoot::keyPressEvent(QKeyEvent *e)
{
	// �������ESC�����رճ���
	if (e->key() == Qt::Key_Escape)
	{
		label->close();
		// ���ʹ��close()��������������ʱ��������Ҳ��close()���������Ҫ������Ϊһ��ģ�飬ʹ��hide������close
		this->close();
		QFile::remove("bg.bmp");
	}

}
void ScreenShoot::setbackground(int width, int height)
{
	//��ȡ��ǰ��Ļ
	QScreen *screen = QGuiApplication::primaryScreen();
	screen->grabWindow(0).save("bg.bmp", "bmp");

	//��ȡ����ͼ���ȱ�������RGBֵ��ʹ�����䰵�������ͼģʽ
	int red, green, blue;

	bg = new QImage("bg.bmp");
	QImage bg_blend(width, height, QImage::Format_RGB32);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			red = qRed(bg->pixel(x, y)) * 0.6;
			green = qGreen(bg->pixel(x, y)) * 0.6;
			blue = qBlue(bg->pixel(x, y)) * 0.6;
			bg_blend.setPixel(x, y, qRgb(red, green, blue));
		}
	}
	// ��ͼƬ����Ϊ����

	QPalette   palette;
	palette.setBrush(this->backgroundRole(), QBrush(bg_blend));
	this->setPalette(palette);

}
void ScreenShoot::show()
{
	QWidget::show();
	setbackground(g_width, g_height);
}